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

CMonster::CMonster(): CCharacter(false)
{
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
	// erstmal konstant, später abhängig 
	// von max-Werten 
	if (alive)
	{
		if (m_iReceivedDmg > 0) {
			// damage
			ReceiveDamage(m_iReceivedDmg);
			m_iReceivedDmg = 0;
			if (Hp().Aktuell <= 0) return false; // tot!
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
		m_chrDirection = (m_chrDirection + 1) % 4;
		return false; // nicht angekommen
	} else {
		m_chrDirection = iDirection;
		return true; // angekommen
	}
}

int CMonster::CalcDmg(int ID) {
	// TODO 1. Waffe
	// TODO 2. Gegnerrüstung
	// TODO 3. Random	
	return m_ApproxDmg;
}

