#include "stdafx.h"
#include "MovingObject.h"

CMovingObject::CMovingObject() {
	m_done = false;
	m_flyForce = VEKTOR{ 0,0,0 };
}

bool CMovingObject::IsFlying()
{
	return (m_flyForce.x != 0 || m_flyForce.y != 0);
}


void CMovingObject::ReduceSpeed() {
	if (m_flyForce.x > 0) m_flyForce.x--;
	if (m_flyForce.y > 0) m_flyForce.y--;
	if (m_flyForce.x < 0) m_flyForce.x++;
	if (m_flyForce.y < 0) m_flyForce.y++;
	m_done = true;
}

bool CMovingObject::HasMovedThisTick() {
	return m_done;
}

void CMovingObject::ResethasMoved() {
	m_done = false;
}