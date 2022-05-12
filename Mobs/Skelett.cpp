#include "stdafx.h"
#include "resource.h"
#include "Skelett.h"

CSkelett::CSkelett(int hp) : CMonster() {
	m_iTyp = SKELETON;
	m_HP.Max = m_HP.Aktuell = hp;
	InitValues();
}

void CSkelett::InitValues() {
	m_SpeedDelay = 8;
	m_ApproxDmg = 2;
	transCol = TRANS_BLU;
}
