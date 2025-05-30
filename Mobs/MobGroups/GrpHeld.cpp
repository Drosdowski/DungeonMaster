// GrpHeld.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "..\Held.h"
#include "..\Champion.h"
#include "..\..\CalculationHelper\CHelpfulValues.h"
#include "..\..\Items\Item.h"
#include "..\..\Items\Weapon.h"
#include "..\..\XMLParser\AttackInfos.h"
#include "GrpHeld.h"
#include <iostream>
#include <cassert>

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
	m_posPosition = VEKTOR{ 10,5,0 }; // bei Monster Gruppe / orig. start position
	//m_posPosition = VEKTOR{ 2,11,0 }; // viele items
	// m_posPosition = VEKTOR{ 19,11,1 }; // bei Items
	//m_posPosition = VEKTOR{ 14,8,1 }; // bei Stiefel
	//m_posPosition = VEKTOR{ 6,9,0 }; // bei 1. Pressure Pad
	//m_posPosition = VEKTOR{ 16,0,1 }; // bei 9 Pressure Pad
	//m_posPosition = VEKTOR{ 18,17,1 }; // bei UND Schalter
	//m_posPosition = VEKTOR{ 4,11,1 }; // bei Schalter f�r T�r
	//m_posPosition = VEKTOR{ 24,6,1 }; // bei Pit
	//m_posPosition = VEKTOR{ 12,29,1 }; // bei Trickwall
	// m_posPosition = VEKTOR{ 10,1,1 }; // keyhole
	//m_posPosition = VEKTOR{ 6,0,1 }; // bei Keule vor 1. Monster
	//m_posPosition = VEKTOR{ 7,14,2 }; // bei Trigger 127
	//m_posPosition = VEKTOR{ 3,28,2 }; // bei Compass
	//m_posPosition = VEKTOR{ 15,18,2 }; // 2. etage mitte
	//m_posPosition = VEKTOR{ 1,31,2 }; // 2. etage Treppe
	//m_posPosition = VEKTOR{ 15,18,3 }; // 3. Etage Teleport
	//m_posPosition = VEKTOR{ 6,24,1 }; // bei Screamer
	//m_posPosition = VEKTOR{ 2,31,1 }; // bei Chest
	//m_posPosition = VEKTOR{ 9,2,3 }; // bei Worms
	//m_posPosition = VEKTOR{ 8,5,1 }; // bei torch / key / doublet

	//m_posPosition = VEKTOR{ 7, 5, 4 }; // ca 999 Actuators
	//m_posPosition = VEKTOR{ 19, 4, 2 }; // gold key
	DrehenAbsolut(richt);
	ChangeCompass();
	m_Modus = DEFAULT;
}

CGrpHeld::~CGrpHeld()
{
	if (m_pItemInHand)
		delete m_pItemInHand;
}

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen f�r Nachrichten CGrpHeld 


void CGrpHeld::InitHeld(CChampion* champion, const int nr, int hp_akt, int st_akt, int ma_akt) {
	if (m_pMember[m_iAktiverHeld])
		((CHeld*)m_pMember[m_iAktiverHeld])->setInactive();
	if (m_pMember[nr] == NULL)
	{
		NewHero(champion, nr, hp_akt, st_akt, ma_akt);
	}
	else {
		m_iAktiverHeld = nr;
		((CHeld*)m_pMember[m_iAktiverHeld])->setActive();
	}
}

void CGrpHeld::InitHeld(const int nr)
{
	if (m_pMember[m_iAktiverHeld])
		((CHeld*)m_pMember[m_iAktiverHeld])->setInactive();
	
	if (m_pMember[nr] == NULL)
	{
		CString strName;
		strName.Format("SAMSON\n\nm\nDADADADADADADA\nDADADADADADADA\nDADADADADADADADA\n", nr);
				
		NewHero(new CChampion(strName, 1), nr, 100, 100, 100);

	}
	else {
		m_iAktiverHeld = nr;
		((CHeld*)m_pMember[m_iAktiverHeld])->setActive();
	}
}

void CGrpHeld::NewHero(CChampion* champ, int nr, int hp_akt, int st_akt, int ma_akt) {
	m_pMember[nr] = new CHeld(nr, champ, hp_akt, st_akt, ma_akt);
	m_iAktiverHeld = nr;

	CHeld* pHeld = (CHeld*)m_pMember[nr];
	pHeld->SetDirection(m_grpDirection);

	SetNewCharOnNextFreePos(nr);

	m_iAnzHelden++;
	if (m_iAnzHelden == 1)
		m_iAktiverZauberer = nr;
}

void CGrpHeld::RessurectHero(CString text, int heroId) {
	int nr = 1;
	while (m_pMember[nr] != NULL && nr < 5) {
		nr++;
	}
	if (nr < 5) {
		CChampion* champ = new CChampion(text, heroId);
		NewHero(champ, nr, champ->hp(), champ->st(), champ->ma());
	}
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
	if (m_iPhase == CHOOSE_HERO)
	{
		CHeld* pHeld = (CHeld*)m_pMember[ID];
		if (pHeld && pHeld->isAlive() && pHeld->isReady()) {
			m_iPhase = CHOOSE_ACTION;
			m_iHeroForAction = ID;
		}
	}
}

void CGrpHeld::PassAction() {
	if (m_iPhase == CHOOSE_ACTION) {
		GetHero(m_iHeroForAction)->EndAttack();
		m_iPhase = CHOOSE_HERO;
	}

}

void CGrpHeld::SetzeModus(GroupMode modus)
{
	int iIndex = m_iAktiverHeld;
	if (iIndex > 0)
	{
		if (modus == RUCKSACK)
		{
			if (m_pMember[iIndex] != NULL)
			{
				((CHeld*)m_pMember[iIndex])->SetBackpackLooking(false);
			}
		}
		m_Modus = modus;
	}
	else {
		m_Modus = DEFAULT;
	}
}

bool CGrpHeld::AsleepAndAttacked() {
	if (m_Modus == ASLEEP)
	{
		for (int i = 1; i < 5; i++)
		{
			CHeld* pHeld = (CHeld*)m_pMember[i];
			if (pHeld && pHeld->ReceivedDmg() > 0) // poison doesn't wake up
				return true;
		}
	}
	return false;
}



bool CGrpHeld::Altern()
{
	bool didHurt = false;
	for (int i = 1; i < 5; i++)
	{
		CHeld* pHeld = (CHeld*)m_pMember[i];
		if (pHeld)
		{
			didHurt = didHurt || pHeld->Altern();
		}
	}
	if (m_iPhaseDelay <= 0)
	{
		if (m_iPhase == SHOW_DAMAGE)
		{
			m_iPhase = CHOOSE_HERO;
		}
	}
	else {
		m_iPhaseDelay--;
	}
	return didHurt;
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

CHeld* CGrpHeld::GetHeroBySubPos(SUBPOS_ABSOLUTE pos) {
	for (int i = 1; i < 5; i++)
	{
		CHeld* pHeld = (CHeld*)m_pMember[i];
		if (pHeld)
		{
			if (pos == pHeld->HoleSubPosition())
				return pHeld;
		}
	}
	return NULL;
}

bool CGrpHeld::SetActiveCaster(int ID)
{
	if (ID <= m_iAnzHelden && m_iAktiverZauberer != ID)
	{
		m_iAktiverZauberer = ID;
		return true;
	}
	return false;
}


void CGrpHeld::PutGetItem(int handOfHeroId, int heroId) {

	CItem* itemInHandToPut = GetItemInHand();
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
		if (m_pMember[i] && m_pMember[i]->isAlive())
		{
			bLaufbereit &= (((CHeld*)m_pMember[i])->St().Aktuell > 0);
		}

	return bLaufbereit;
}

bool CGrpHeld::isAlive() {
	for (int i = 1; i < 5; i++)
	{
		if (m_pMember[i] && m_pMember[i]->isAlive()) {
			return true;
		}

	}
	return false;
}

void CGrpHeld::Laufen(VEKTOR WunschPos, bool teleport) {
	for (int i = 1; i <= 4; i++)
	{
		CHeld* pHero = (CHeld*)m_pMember[i];
		if (pHero && (pHero->isAlive()))
		{
			if (!teleport)
				pHero->WerteTemporaerAendern(0, -1, 0);
			pHero->MoveDone();
		}
	}
	m_posPosition = WunschPos;
	std::cout << "New Position: " << m_posPosition.x << " - " << m_posPosition.y << std::endl;

}

void CGrpHeld::TakeItemInHand(CItem* item)
{
	if (m_pItemInHand == NULL)
		m_pItemInHand = item;
	else
		assert(false); // ???
}

void CGrpHeld::EmptyHand() {
	// kein delete, Objekt ist jetzt woanders...
	m_pItemInHand = NULL;
}

void CGrpHeld::ChangeCompass() {
	for (int i = 1; i < 5; i++) {
		if (m_pMember[i] && m_pMember[i]->IsHero()) {
			CHeld* hero = (CHeld*)m_pMember[i];
			hero->ChangeCompass();
		}
	}
}
