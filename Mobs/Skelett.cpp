#include "stdafx.h"
#include "resource.h"
#include "Skelett.h"

CSkelett::CSkelett() : CMonster() {
	m_iTyp = SKELETT;
	InitValues();
}

void CSkelett::InitValues() {
	m_HP.Max = m_HP.Aktuell = 2;
	m_ST.Max = m_ST.Aktuell = 100;
	m_MA.Max = m_MA.Aktuell = 0;
	m_SpeedDelay = 8;
	m_ApproxDmg = 2;
	transCol = RGB(0, 208, 208);
}

int CSkelett::GetIDB(int index)
{
	if (index == 0) {
		if (m_attacking) {
			return IDB_SKELETON_ATTACK;
		}
		else {
			return IDB_SKELETON_FRONT;
		}
	}
	if (index == 1 || index == 3) return IDB_SKELETON_RIGHT;
	if (index == 2) {
		return IDB_SKELETON_BACK;
	}
	return 0;
}