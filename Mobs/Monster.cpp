// Monster.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "resource.h"
#include "Monster.h"
#include "CalculationHelper/CHelpfulValues.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMonster

CMonster::CMonster(CCreatureAttributes attributes, int subId): CCharacter(false)
{
	m_iReady = 0;
	m_attributes = attributes;
	m_HP.Max = m_HP.Aktuell = attributes.hitPoints[subId];
	transCol = TRANS_BLU;
}


CMonster::~CMonster()
{
	DeleteDC(pCdc);
}


/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CMonster 

bool CMonster::Altern()
{
	bool alive = CCharacter::Altern();

	if (m_iReady > 0) {
		m_iReady--;
	}

	// erstmal konstant, später abhängig 
	// von max-Werten 
	if (alive)
	{
		if (m_iReceivedDmg > 0) {
			// damage
			alive = ReceiveDamage(m_iReceivedDmg);
			m_iReceivedDmg = 0;
		}
		else {
			// restore
			//  WerteTemporaerAendern(1, 1, 1);
		}
		if (m_attacking) {
			EndAttack();
		}
	}
	return alive;
}

int CMonster::GetIDB(int index) {
	return 0;
}

bool CMonster::TurnTo(COMPASS_DIRECTION iDirection) {
	if (m_chrDirection == CHelpfulValues::OppositeDirection(iDirection))
	{
		m_chrDirection = (COMPASS_DIRECTION)((m_chrDirection + 1) % 4);
		return false; // nicht angekommen
	} else {
		m_chrDirection = iDirection;
		return true; // angekommen
	}
}

int CMonster::CalcDmg(int ID) {
	// TODO Heldenwerte!
	return rand() % m_attributes.monsterInfo.attack_power;
}




