// GrpHeld.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "DM.h"
#include "DMView.h"
#include "Rucksack.h"
#include "..\Held.h"
#include "GrpHeld.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGrpHeld

CGrpHeld::CGrpHeld(VEKTOR pos, int richt)
{
	for (int i=1; i<=4; i++)
		m_pMember[i] = NULL;
	m_posPosition = pos;
	m_posPosition = VEKTOR{ 2,7,0 };
	//m_posPosition = VEKTOR{ 7,9,1 };
	m_grpDirection = richt;
}

CGrpHeld::~CGrpHeld()
{
}

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CGrpHeld 

void CGrpHeld::InitHeld(CPictures* pPictures, const int nr)
{
	if (m_pMember[nr] == NULL) 
	{
		CString strName;
		strName.Format("Held %i",nr);
		m_pMember[nr] = new CHeld(pPictures, nr, strName);
		m_iAktiverHeld = nr;

		CHeld* pHeld = (CHeld*) m_pMember[nr];
		
		CDC* pDC = ((CDMApp*)AfxGetApp())->m_pView->GetDC();
		pHeld->HaendeZeichnen(pDC, pPictures);
		pHeld->NameZeichnen(pDC);
		pHeld->WerteZeichnen(pDC);

		// todo duplicate code here!
		bool ne, nw, sw, se;
		ne = nw = sw = se = false;
		SUBPOS_ABSOLUTE pos = MIDDLE;	// Freien Platz suchen
		for (int i = 1; i < 5; i++)
			if ((i != nr) && (m_pMember[i] != NULL))
			{
				pos = m_pMember[i]->HoleSubPosition();
				if (pos == NORTHWEST) nw = true;
				else if (pos == NORTHEAST) ne = true;
				else if (pos == SOUTHWEST) sw = true;
				else if (pos == SOUTHEAST) se = true;
			}
		if (!ne)
			pos = NORTHEAST;
		else if (!nw)
			pos = NORTHWEST;
		else if (!sw)
			pos = SOUTHWEST;
		else if (!se)
			pos = SOUTHEAST;

		m_pMember[nr]->SetzeSubPosition(pos);
		pHeld->SymbolZeichnen(pDC, pPictures);

		m_iAnzHelden++;
		if (m_iAnzHelden == 1) 
			m_iAktiverZauberer = 1;
	}
}

void CGrpHeld::Aktiviere(int n)
{
	if (m_pMember[n])
	{
		((CHeld*)m_pMember[m_iAktiverHeld])->m_bAktiv=false;
		m_iAktiverHeld = n;
		((CHeld*)m_pMember[m_iAktiverHeld])->m_bAktiv=true;
	}
}

void CGrpHeld::ChooseHeroForAction(int ID) {
	if (m_iPhase == 1)
	{
		if (m_pMember[ID]) {
			m_iPhase = 2;
			m_iHeroForAction = ID;
		}
	}
}

void CGrpHeld::PassAction() {
	if (m_iPhase == 2) {
		GetHero(m_iHeroForAction)->EndAttack();
		m_iPhase = 1;
	}

}

void CGrpHeld::DoActionForChosenHero(int ActionId, CGrpChar* pVictims) {
	if (m_iPhase == 2) {
		if (pVictims) {
			CHeld* pHero = (CHeld*)m_pMember[m_iHeroForAction];
			if (pHero) {
				if (pHero->Hp() > 0) {
					int dmg = pHero->CalcDmg(ActionId, pVictims);
					pVictims->DoDamage(dmg, HolePosition(), false); // true = Schaden an alle
					pHero->AttackModeWithDmg(dmg);
					m_iPhase = 3;
				}
			}
		}
		else {
			// kein Gegner!
			m_iPhase = 1;
		}
	}
}

CHeld* CGrpHeld::ClosestHeroTo(CMonster* monster) {
	// TODO richtig rechnen!!
	for (int i = 1; i <= 4; i++)
	{
		CHeld* pHeld = (CHeld*)m_pMember[i];

		if (m_pMember[i] != NULL)
		{
			if (m_pMember[i]->Hp() <= 0)
				return (CHeld*)m_pMember[i];
		}
	}
	return NULL;
}

void CGrpHeld::OnLButtonUp(CDC* pDC, UINT nFlags, CPoint point) 
{
	((CHeld*)m_pMember[m_iAktiverHeld])->m_pRucksack->OnLButtonUp(pDC, nFlags, point);
}

void CGrpHeld::OnLButtonDown(CDC* pDC, UINT nFlags, CPoint point) 
{
	((CHeld*)m_pMember[m_iAktiverHeld])->m_pRucksack->OnLButtonDown(pDC, nFlags, point);
}

bool CGrpHeld::SetzeModus(CDC* pDC, int iModus)
{
	int iIndex = m_iAktiverHeld;
	if (iIndex>0)
	{
		if (iModus == RUCKSACK)
			if (m_pMember[iIndex] != NULL)
			{
				((CHeld*)m_pMember[iIndex])->m_pRucksack->SetzeModusExtend(MOD_EXT_NORMAL);
				((CHeld*)m_pMember[iIndex])->RucksackZeichnen(pDC);
			}
		return true;
	}
	return false;
}

void CGrpHeld::Zeichnen(CDC * pDC, CPictures* pPictures, int iModus)
{
	for (int i=1; i<=4; i++)
	{
		CHeld* pHeld = (CHeld*) m_pMember[i];

		if (m_pMember[i] != NULL)
		{
			if (m_pMember[i]->Hp() <= 0)
				pHeld->KnochenZeichnen(pDC, pPictures);
			else
			{
				switch (iModus)
				{
					case (MOD_LAUFEN):
					{
						pHeld->HaendeZeichnen(pDC, pPictures);
						pHeld->NameZeichnen(pDC);
						pHeld->WerteZeichnen(pDC);			
						break;
					}
					case (MOD_RUCKSACK):
					{
						if (i == m_iAktiverHeld)
						{
							pHeld->BildZeichnen(pDC);
							pHeld->RucksackZeichnen(pDC);
						}
						break;
					}
				}
				pHeld->WaffeZeichnen(pDC);
				pHeld->SymbolZeichnen(pDC, pPictures);
				pHeld->SchadenZeichnen(pDC, pPictures);
			}
		}
	}
}

void CGrpHeld::UpdateRucksack(CDC* pDC, CPictures* pPictures)
{
	for (int i = 1; i<5; i++)
	{
		CHeld* pHeld = (CHeld*) m_pMember[i];
		if (m_pMember[i])
			if (m_pMember[i]->Hp()>0)
			{
				if (i==m_iAktiverHeld)
				{
					pHeld->BildZeichnen(pDC);
					pHeld->RucksackZeichnen(pDC);
				}
				else {
					pHeld->HaendeZeichnen(pDC, pPictures);
				}
				pHeld->WerteZeichnen(pDC);
			}
			else
				pHeld->KnochenZeichnen(pDC, pPictures);
	}	
}



bool CGrpHeld::Altern()
{
	bool anyoneAlive = false;
	for (int i=1; i<5; i++)
	{
		CHeld* pHeld = (CHeld*) m_pMember[i];
		if (pHeld)
		{
			bool heroAlive = pHeld->Altern();
			if (!heroAlive) {
				// nicht löschen - wiederbeleben möglich!
			}
			else {
				anyoneAlive = true;
			}
		}
	}
	if (m_iPhase == 3)
	{
		m_iPhase = 1;
	}
	return anyoneAlive;
}

CHeld* CGrpHeld::GetAttackingHero() {
	for (int i = 1; i < 5; i++)
	{
		CHeld* pHeld = (CHeld*)m_pMember[i];
		if (pHeld)
		{
			if (pHeld->isAttacking())
				return pHeld;
		}
	}
	return NULL;
}

void CGrpHeld::DrinkFountain() {
	for (int i = 1; i < 5; i++)
	{
		CHeld* pHeld = (CHeld*)m_pMember[i];
		if (pHeld)
		{
			if (pHeld->Hp() > 0)
				pHeld->Trinken(100);
		}
	}
}

bool CGrpHeld::SetActiveCaster(int ID)
{
	if (ID <= m_iAnzHelden)
	{
		m_iAktiverZauberer = ID;
		return true;
	}
	return false;
}

void CGrpHeld::TakeItemInHand(CMiscellaneous* item) 
{ 
	if (m_pItemInHand == NULL) 
		m_pItemInHand = item; 
}

void CGrpHeld::EmptyHand() {
	// kein delete, Objekt ist jetzt woanders...
	m_pItemInHand = NULL;
}
