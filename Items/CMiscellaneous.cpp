#include "stdafx.h"
#include "CMiscellaneous.h"


CMiscellaneous::CMiscellaneous(int index, int type, int subtype) {
	m_index = index;
	m_type = type;
	m_subtype = subtype;
	m_flyForce = VEKTOR{ 0,0,0 };
}

CMiscellaneous::~CMiscellaneous() {

}

bool CMiscellaneous::IsFlying()
{
	return (m_flyForce.x > 0 || m_flyForce.y > 0);
}

