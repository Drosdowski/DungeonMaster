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

IMPLEMENT_DYNCREATE(CGrpHeld, CView)

CGrpHeld::CGrpHeld()
{
	for (int i=1; i<=4; i++)
		m_pMember[i] = NULL;
	m_posPosition.x=3;
	m_posPosition.y=7;
	m_posPosition.z=0;
	m_iAktiverHeld = 1;
	m_grpDirection = 0;
}

CGrpHeld::~CGrpHeld()
{
}

BEGIN_MESSAGE_MAP(CGrpHeld, CView)
	//{{AFX_MSG_MAP(CGrpHeld)
		// HINWEIS - Der Klassen-Assistent fügt hier Zuordnungsmakros ein und entfernt diese.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Zeichnung CGrpHeld 

void CGrpHeld::OnDraw(CDC* pDC)
{
	// ZU ERLEDIGEN: Code zum Zeichnen hier einfügen
}

/////////////////////////////////////////////////////////////////////////////
// Diagnose CGrpHeld

#ifdef _DEBUG
void CGrpHeld::AssertValid() const
{
	CView::AssertValid();
}

void CGrpHeld::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

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

		bool vl,vr,hl,hr;
		vl=vr=hl=hr=false;
		SUBPOS pos;	// Freien Platz suchen
		for (int i=1; i<5; i++)
			if ((i!=nr) && (m_pMember[i]!=NULL))
			{
				pos = m_pMember[i]->HoleSubPosition();
				if (pos == RECHTSVORNE) vr = true;
				else if (pos == LINKSVORNE) vl = true;
				else if (pos == LINKSHINTEN) hl = true;
				else if (pos == RECHTSHINTEN) hr = true;
			}
		if (!vl)
			pos = LINKSVORNE;
		else if (!vr)
			pos = RECHTSVORNE;
		else if (!hl)
			pos = LINKSHINTEN;
		else
			pos = RECHTSHINTEN;

		m_pMember[nr]->SetzeSubPosition(pos);
		pHeld->SymbolZeichnen(pDC, pPictures);

		m_iAnzHelden++;
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

void CGrpHeld::DoActionForChosenHero(int ID, CGrpChar* pVictims) {
	if (m_iPhase == 2) {
		if (pVictims) {
			CHeld* pHero = (CHeld*)m_pMember[m_iHeroForAction];
			if (pHero) {
				if (pHero->Hp() > 0) {
					int dmg = pHero->CalcDmg(ID, pVictims);
					pVictims->DoDamage(dmg, false); // true = Schaden an alle
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