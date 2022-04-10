// Held.cpp : implementation file
//

#include "stdafx.h"
#include "Rucksack.h"
#include "..\CHelpfulValues.h"
#include "..\Items\CMiscellaneous.h"
#include "Monster.h"
#include "Held.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHeld

CHeld::CHeld(int iIndex, CString strName): CCharacter()
{
	m_HP.Max = 100;
	m_MA.Max = 100;
	m_ST.Max = 100;
	
	m_HP.Aktuell = m_HP.Max;
	m_ST.Aktuell = m_ST.Max;
	m_MA.Aktuell = m_MA.Max;
	m_bAktiv = true;
	m_strName = strName;
	m_iIndex = iIndex;
	m_iFood = maxFood;
	m_iWater = maxWater;
	for (int i = 1; i<5; i++)
		m_sExp[i] = 200;
	switch (iIndex)
	{
	case 1:
		m_Farbe[1] = HELLGRUEN; break;
	case 2:
		m_Farbe[2] = GELB; break;
	case 3:
		m_Farbe[3] = ROT; break;
	case 4:
		m_Farbe[4] = BLAU; break;
	}

	for (int i = 0; i < 30; i++) {
		m_itemCarrying[i] = NULL;
	}

	m_pRucksack = new CRucksack(this);
}


CHeld::~CHeld()
{
	for (int i = 0; i < 30; i++) {
		if (m_itemCarrying[i])
			delete m_itemCarrying[i];
	}
	delete m_pRucksack;
}


/////////////////////////////////////////////////////////////////////////////
// CHeld message handlers



/////////////////////////////////////////////////////////////////////////////
/////////////////////////////// Hilfsfunktionen /////////////////////////////
/////////////////////////////////////////////////////////////////////////////

bool CHeld::Altern()
{
	bool alive = CCharacter::Altern();
	if (m_dealingDmg > 0)
	{
		m_dealingDmg = 0;
		// phase
	}

	// erstmal konstant, später hp & st abhängig 
	// von VIT, ma von WIS sowie von FOOD & WATER
	if (alive)
	{
		WerteTemporaerAendern(1, 1, 1);
		//m_iFood--;
		//m_iWater--;
		if (m_iFood < 50)
			WerteTemporaerAendern(0, -1, 0);
		if (m_iWater < 50)
			WerteTemporaerAendern(0, -1, 0);
		if (m_iFood < 15)
			WerteTemporaerAendern(0, -2, 0);
		if (m_iWater < 15)
			WerteTemporaerAendern(0, -2, 0);
		if (m_ST.Aktuell <= 0)
		{
			m_HP.Aktuell = 0;	// zu Tode erschöpft
			return false;
		}
	}
	return alive;
}

void CHeld::WerteTemporaerAendern(int hp, int st, int ma)
{
	m_HP.Aktuell = min(max(hp + m_HP.Aktuell, 0), m_HP.Max);
	m_ST.Aktuell = min(max(st + m_ST.Aktuell, 0), m_ST.Max);
	m_MA.Aktuell = min(max(ma + m_MA.Aktuell, 0), m_MA.Max);
}

int CHeld::CalcDmg(int ID, CGrpChar* pOpponents) {
	// CHeld* hero = pHeroes->ClosestHeroTo(pMonster); // Todo berechnen, welcher Held am nahesten steht!
	// TODO temporär; Waffe 1 = 1 Schaden, ...
	return ID;
}

void CHeld::Essen(int amount) {
	m_iFood = min(maxFood, m_iFood + amount);
}

void CHeld::Trinken(int amount) {
	m_iWater = min(maxWater, m_iWater + amount);
}

void CHeld::TakeItemInHand(CMiscellaneous* item)
{
	if (m_pItemInHand == NULL)
		m_pItemInHand = item;
}

void CHeld::EmptyHand() {
	// kein delete, Objekt ist jetzt woanders...
	m_pItemInHand = NULL;
}

CMiscellaneous* CHeld::SwitchItemAt(int index, CMiscellaneous* item)
{
	CMiscellaneous* carryingBefore = m_itemCarrying[index];
	m_itemCarrying[index] = item;
	return carryingBefore;
}
