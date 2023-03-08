#include "stdafx.h"
#include "MovingObject.h"

CMovingObject::CMovingObject() {
	m_done = false;
	m_flyForce = VEKTOR{ 0,0,0 };
}

CMovingObject::~CMovingObject() {
	m_done = true;
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

COMPASS_DIRECTION CMovingObject::GetDirection() {
	if (m_flyForce.x > 0) return EAST;
	if (m_flyForce.y > 0) return SOUTH; // todo prüfen!
	if (m_flyForce.x < 0) return WEST;
	if (m_flyForce.y < 0) return NORTH;
	return STOP;

}

void CMovingObject::SetDirection(COMPASS_DIRECTION direction) {
	int speed = abs(m_flyForce.x) + abs(m_flyForce.y);
	int z = m_flyForce.z;
	switch (direction) {
		case NORTH: m_flyForce = { 0, -speed, z }; break;
		case EAST: m_flyForce = { speed, 0, z }; break;
		case SOUTH: m_flyForce = { 0, speed, z }; break;
		case WEST: m_flyForce = { -speed, 0, z }; break;
		// default: m_flyForce = VEKTOR{ 0, 0, z };
	}
}
