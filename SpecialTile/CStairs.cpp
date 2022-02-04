#include "stdafx.h"
#include "CStairs.h"


CStairs::CStairs(StairType type, bool eastWest) {
	m_Type = type;
	m_eastWest = eastWest;
}

CStairs::~CStairs() {
}

bool CStairs::Visible(int heroRicht) {
	return (m_eastWest != (heroRicht % 2 != 0));
}