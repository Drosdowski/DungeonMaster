#include "stdafx.h"
#include "resource.h"
#include "Mumie.h"

CMumie::CMumie(): CMonster() {	
	m_iTyp = MUMIE;
	InitValues();
}

void CMumie::InitValues() {
	m_HP.Max = m_HP.Aktuell = 50;
	m_ST.Max = m_ST.Aktuell = 100;
	m_MA.Max = m_MA.Aktuell = 0;
	m_SpeedDelay = 6;
	m_ApproxDmg = 5;
	transCol = RGB(0, 208, 208);
}

int CMumie::GetIDB(int index) {
	if (index == 0) return IDB_MUMMY_BACK;
	if (index == 1 || index == 3) return IDB_MUMMY_RIGHT;
	if (index == 2) {
		if (m_attacking) {
			return IDB_MUMMY_ATTACK;
		}
		else {
			return IDB_MUMMY_FRONT;
		}
	}
	return 0;
}
