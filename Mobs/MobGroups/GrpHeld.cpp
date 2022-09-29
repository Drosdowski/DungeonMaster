// GrpHeld.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Rucksack.h"
#include "..\Held.h"
#include "..\..\CalculationHelper\CHelpfulValues.h"
#include "..\..\Items\Item.h"
#include "..\..\Items\Weapon.h"
#include "..\..\XMLParser\AttackInfos.h"
#include "..\..\XMLParser\MonsterInfos.h"
#include "GrpHeld.h"
#include "GrpMonster.h"
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
	for (int i = 1; i <= 4; i++)
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
	//m_posPosition = VEKTOR{ 6,0,1 }; // bei Keule vor 1. Monster
	//m_posPosition = VEKTOR{ 3,28,2 }; // bei Compass
	//m_posPosition = VEKTOR{ 15,18,2 }; // 2. etage mitte
	//m_posPosition = VEKTOR{ 1,31,2 }; // 2. etage Treppe
	//m_posPosition = VEKTOR{ 15,18,3 }; // 3. Etage Teleport
	//m_posPosition = VEKTOR{ 1,12,3 }; // bei Screamer
	m_posPosition = VEKTOR{ 9,2,3 }; // bei Worms
	DrehenAbsolut(richt);
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
		strName.Format("Held %i", nr);

		if (m_pMember[m_iAktiverHeld])
			((CHeld*)m_pMember[m_iAktiverHeld])->setInactive();

		m_pMember[nr] = new CHeld(nr, strName);
		m_iAktiverHeld = nr;

		CHeld* pHeld = (CHeld*)m_pMember[nr];
		pHeld->SetDirection(m_grpDirection);

		SetNewCharOnNextFreePos(nr);

		m_iAnzHelden++;
		if (m_iAnzHelden == 1)
			m_iAktiverZauberer = nr;

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
		if (m_pMember[ID] && m_pMember[ID]->isAlive()) {
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

void CGrpHeld::DoActionForChosenHero(int ActionId, CGrpMonster* pVictims, CAttackInfos* attackInfos, CMonsterInfos* monsterInfos, int diff) {
	if (m_iPhase == 2) {
		if (pVictims) {
			CHeld* pHero = (CHeld*)m_pMember[m_iHeroForAction];
			if (pHero) {
				if (pHero->isAlive()) {
					CItem* item = pHero->GetItemCarrying(1);
					VEKTOR myPos = GetVector();
					CWeapon* weapon = NULL;
					CString attackType;
					if (item && item->getItemType() == CItem::ItemType::WeaponItem) {
						weapon = (CWeapon*)item;
						attackType = weapon->GetAttributes().style[ActionId-1].type;
					}
					else {
						/*CWeaponAttributes att;
						att.fixAttributes.damage = 1;
						weapon = new CWeapon(HANDINDEX, att);*/
						attackType = "N"; // Punch / Kick / Warcry
					}
					CAttackConst ac = attackInfos->GetAttack(attackType);
					CMonsterConst mc = monsterInfos->GetMonsterInfo(pVictims->GetType());

					int dmg = pHero->CalcDmg(weapon, ac, mc, pVictims, diff); // todo doof so, besser in CMonster die MOnsterInfo rein
					if (dmg > 0) {
						pVictims->DoDamage(dmg, myPos, false); // true = Schaden an alle
						pHero->AttackModeWithDmg(dmg);
						m_iPhase = 3;
						m_iPhaseDelay = 2;
					}
					/*
					int itemIndex = -1;
					if (item && item->getItemType() == CItem::ItemType::WeaponItem) {
						itemIndex = item->getIndex();
					}
					else if (item == NULL) {
						itemIndex = HANDINDEX;
					}
					if (itemIndex >= 0) {
						CAttackConst ac = attackInfos->GetAttack(itemIndex);
						int dmg = pHero->CalcDmg(ac, pVictims, myPos.z);
						pVictims->DoDamage(dmg, myPos, false); // true = Schaden an alle
						pHero->AttackModeWithDmg(dmg);
						m_iPhase = 3;
						m_iPhaseDelay = 2;
					}*/
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
	// TODO richtig rechnen!! - obsolet??
	for (int i = 1; i <= 4; i++)
	{
		CHeld* pHeld = (CHeld*)m_pMember[i];

		if (m_pMember[i] != NULL)
		{
			if (m_pMember[i]->isAlive())
				return (CHeld*)m_pMember[i];
		}
	}
	return NULL;
}


bool CGrpHeld::SetzeModus(CDC* pDC, int iModus)
{
	int iIndex = m_iAktiverHeld;
	if (iIndex > 0)
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


bool CGrpHeld::Altern(CField* field)
{
	bool anyoneAlive = false;
	for (int i = 1; i < 5; i++)
	{
		CHeld* pHeld = (CHeld*)m_pMember[i];
		if (pHeld)
		{
			bool heroAlive = pHeld->Altern(field);
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
		if (m_iPhaseDelay <= 0)
			m_iPhase = 1;
		else
			m_iPhaseDelay--;
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

	CItem* itemInHandToPut = GetActiveHero()->GetItemInHand();
	CItem* newItemInHandToGet = NULL;

	if (itemInHandToPut) {
		// Item tauschen oder ablegen
		newItemInHandToGet = GetHero(heroId)->SwitchItemAt(handOfHeroId, itemInHandToPut);
	}
	else {
		// item holen (Hand leer)
		newItemInHandToGet = GetHero(heroId)->GetItemCarrying(handOfHeroId);
	}
	EmptyHand();
	if (newItemInHandToGet == NULL) {
		// ablegen - passt.
	}
	else {
		// tauschen		
		TakeItemInHand(newItemInHandToGet);
		if (!itemInHandToPut)
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
		if (pHero && (pHero->isAlive()))
		{
			pHero->WerteTemporaerAendern(0, -1, 0);
			pHero->MoveDone();
		}
	}
	m_posPosition = WunschPos;
	std::cout << "New Position: " << m_posPosition.x << " - " << m_posPosition.y << std::endl;

}