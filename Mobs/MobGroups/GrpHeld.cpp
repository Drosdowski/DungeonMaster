// GrpHeld.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Rucksack.h"
#include "..\Held.h"
#include "..\..\CHelpfulValues.h"
#include "..\..\Items\Item.h"
#include "GrpHeld.h"
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGrpHeld

CGrpHeld::CGrpHeld(VEKTOR pos, COMPASS_DIRECTION richt)
{
	for (int i=1; i<=4; i++)
		m_pMember[i] = NULL;
	//m_posPosition = pos;
	//m_posPosition = VEKTOR{ 2,7,0 }; // bei Monster Gruppe / orig. start position
	//m_posPosition = VEKTOR{ 2,11,0 }; // viele items
	//m_posPosition = VEKTOR{ 7,9,1 }; // bei Items
	//m_posPosition = VEKTOR{ 14,8,1 }; // bei Stiefel
	//m_posPosition = VEKTOR{ 6,9,0 }; // bei 1. Pressure Pad
	//m_posPosition = VEKTOR{ 16,0,1 }; // bei 9 Pressure Pad
	//m_posPosition = VEKTOR{ 18,17,1 }; // bei UND Schalter
	//m_posPosition = VEKTOR{ 4,11,1 }; // bei Schalter für Tür
	//m_posPosition = VEKTOR{ 24,6,1 }; // bei Pit
	//m_posPosition = VEKTOR{ 12,29,1 }; // bei Trickwall
	m_posPosition = VEKTOR{ 6,3,1 }; // bei Schwert in Alcove
	m_grpDirection = richt;
}

CGrpHeld::~CGrpHeld()
{
}

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CGrpHeld 

CHeld* CGrpHeld::InitHeld(const int nr)
{
	if (m_pMember[nr] == NULL) 
	{
		CString strName;
		strName.Format("Held %i",nr);

		if (m_pMember[m_iAktiverHeld])
			((CHeld*)m_pMember[m_iAktiverHeld])->setInactive();

		m_pMember[nr] = new CHeld(nr, strName);
		m_iAktiverHeld = nr;

		CHeld* pHeld = (CHeld*) m_pMember[nr];
		
		SetNewCharOnNextFreePos(nr);
		
		m_iAnzHelden++;
		if (m_iAnzHelden == 1) 
			m_iAktiverZauberer = 1;

		return pHeld;
	}
	return NULL;
}

void CGrpHeld::Aktiviere(int n)
{
	if (m_pMember[n])
	{
		((CHeld*)m_pMember[m_iAktiverHeld])->setInactive();
		m_iAktiverHeld = n;
		((CHeld*)m_pMember[m_iAktiverHeld])->setActive();
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
				if (pHero->Hp().Aktuell > 0) {
					int dmg = pHero->CalcDmg(ActionId, pVictims);
					pVictims->DoDamage(dmg, GetVector(), false); // true = Schaden an alle
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
			if (m_pMember[i]->Hp().Aktuell <= 0)
				return (CHeld*)m_pMember[i];
		}
	}
	return NULL;
}


bool CGrpHeld::SetzeModus(CDC* pDC, int iModus)
{
	int iIndex = m_iAktiverHeld;
	if (iIndex>0)
	{
		if (iModus == RUCKSACK)
			if (m_pMember[iIndex] != NULL)
			{
				((CHeld*)m_pMember[iIndex])->GetRucksack()->SetzeModusExtend(MOD_EXT_NORMAL);
			}
		return true;
	}
	return false;
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
			if (pHeld->Hp().Aktuell > 0)
				pHeld->Trinken(100);
		}
	}
}

bool CGrpHeld::SetActiveCaster(int ID)
{
	if (ID <= m_iAnzHelden && m_iAktiverZauberer != ID)
	{
		CItem* itemInHand = GetHero(ID)->GetItemInHand();
		GetHero(m_iAktiverZauberer)->TakeItemInHand(itemInHand);
		GetHero(ID)->EmptyHand();
		m_iAktiverZauberer = ID;
		return true;
	}
	return false;
}

CItem* CGrpHeld::GetItemInHand() {
	CHeld* held = GetActiveHero();
	if (held)
		return held->GetItemInHand();
	else
		return NULL;
}

void CGrpHeld::PutGetItem(int handOfHeroId, int heroId) {

	CItem* itemInHand = GetActiveHero()->GetItemInHand();
	CItem* itemCarryingAtPos = GetHero(heroId)->GetItemCarrying(handOfHeroId);
	CItem* newItemInHand = NULL;

	if (itemInHand) {
		// Item tauschen oder ablegen
		newItemInHand = GetHero(heroId)->SwitchItemAt(handOfHeroId, itemInHand);
	}
	else {
		// item holen (Hand leer)
		newItemInHand = itemCarryingAtPos;
	}
	if (newItemInHand == NULL) {
		EmptyHand();
	}
	else {
		TakeItemInHand(newItemInHand);
		GetHero(heroId)->RemoveItemCarrying(handOfHeroId);
	}
}

bool CGrpHeld::Laufbereit()
{
	bool bLaufbereit = true;
	for (int i = 1; i < 5; i++)
		if (m_pMember[i])
		{
			bLaufbereit &= (((CHeld*)m_pMember[i])->St().Aktuell > 0);
		}

	return bLaufbereit;
}

void CGrpHeld::Laufen(VEKTOR WunschPos) {
	for (int i = 1; i <= 4; i++)
	{
		CHeld* pHero = (CHeld*)m_pMember[i];
		if (pHero && (pHero->Hp().Aktuell > 0))
		{
			pHero->WerteTemporaerAendern(0, -1, 0);
			pHero->ActionDone();
		}
	}
	m_posPosition = WunschPos;
	std::cout << "New Position: " << m_posPosition.x << " - " << m_posPosition.y << std::endl;

}