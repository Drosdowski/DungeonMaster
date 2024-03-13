// Monster.cpp: Implementierungsdatei
//

#include "stdafx.h"
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
	m_iReady = attributes.ready[subId];
	m_attributes = attributes;
	m_HP.Max = m_HP.Aktuell = attributes.hitPoints[subId];
	transCol = attributes.transCol;
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

void CMonster::RestoreFromSaveGame(SUBPOS_ABSOLUTE subPos, int hp, int ready) {
	m_HP.Aktuell = hp;
	m_iReady = ready;
	m_subPosition = subPos;
}

bool CMonster::IsLeftForPlayer(VEKTOR monPos, VEKTOR heroPos) {
	bool horizontalCheck = monPos.y == heroPos.y;
	bool verticalCheck = monPos.x == heroPos.x;
	if (horizontalCheck) {
		if (monPos.x < heroPos.x) {
			return (m_subPosition == SOUTHEAST || m_subPosition == SOUTHWEST);
		}
		else {
			return (m_subPosition == NORTHEAST || m_subPosition == NORTHWEST);
		}
	}
	else if (verticalCheck) {
		if (monPos.y < heroPos.y) {
			return (m_subPosition == NORTHWEST || m_subPosition == SOUTHWEST);
		}
		else {
			return (m_subPosition == NORTHEAST || m_subPosition == SOUTHEAST);
		}
	}
	else {
		return false;
	}
}




