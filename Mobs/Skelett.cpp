#include "stdafx.h"
#include "resource.h"
#include "Skelett.h"

CSkelett::CSkelett() : CMonster() {
	m_iTyp = SKELETT;
	InitValues();
}

void CSkelett::InitValues() {
	m_HP.Max = m_HP.Aktuell = 2;
	m_SpeedDelay = 8;
	m_ApproxDmg = 2;
	transCol = TRANS_BLU;
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