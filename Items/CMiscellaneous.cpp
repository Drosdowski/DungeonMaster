#include "stdafx.h"
#include "CMiscellaneous.h"


CMiscellaneous::CMiscellaneous(int index, int type, int subtype) {
	m_index = index;
	m_type = type;
	m_subtype = subtype;
	m_flyForce = VEKTOR{ 0,0,0 };
	m_done = false;
}

CMiscellaneous::~CMiscellaneous() {

}

bool CMiscellaneous::IsFlying()
{
	return (m_flyForce.x != 0 || m_flyForce.y != 0);
}

void CMiscellaneous::ReduceSpeed() {
	if (m_flyForce.x > 0) m_flyForce.x--;
	if (m_flyForce.y > 0) m_flyForce.y--;
	if (m_flyForce.x < 0) m_flyForce.x++;
	if (m_flyForce.y < 0) m_flyForce.y++;
	m_done = true;
}

bool CMiscellaneous::HasMovedThisTick() {
	return m_done;
}

void CMiscellaneous::ResethasMoved() {
	m_done = false;
}
