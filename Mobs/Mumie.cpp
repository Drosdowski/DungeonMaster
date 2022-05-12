#include "stdafx.h"
#include "resource.h"
#include "Mumie.h"

CMumie::CMumie(int hp): CMonster() {
	m_HP.Max = m_HP.Aktuell = hp;
	m_iTyp = MUMMY;
	InitValues();
}

void CMumie::InitValues() {
	m_SpeedDelay = 6;
	m_ApproxDmg = 5;
	transCol = TRANS_BLU;
}

