#include "stdafx.h"
#include "CStairs.h"


CStairs::CStairs(StairType type, COMPASS_DIRECTION stairExit) {
	m_Type = type;
	m_stairExit = stairExit;
}

CStairs::~CStairs() {
}

bool CStairs::Visible(int heroRicht) {
	return (m_eastWest != (heroRicht % 2 != 0));
}