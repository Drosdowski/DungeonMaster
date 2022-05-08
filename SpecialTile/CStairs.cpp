#include "stdafx.h"
#include "CStairs.h"
#include "..\CalculationHelper\CHelpfulValues.h"

CStairs::CStairs(StairType type, COMPASS_DIRECTION stairExit) {
	m_Type = type;
	m_stairExit = stairExit;
}

CStairs::~CStairs() {
}

bool CStairs::Visible(COMPASS_DIRECTION heroRicht) {
	return (heroRicht == m_stairExit || heroRicht == CHelpfulValues::OppositeDirection(m_stairExit));
}