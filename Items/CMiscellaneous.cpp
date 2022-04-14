#include "stdafx.h"
#include "CMiscellaneous.h"
#include "..\Pictures\Items3D\CItem3DPic.h"
#include <cassert>

CMiscellaneous::CMiscellaneous(int index, ItemType type, int subtype) {
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

int CMiscellaneous::GetOffsetForGroup() {
	ItemGroup group = GetGroup();
	switch (group) {
	case Key:
		return 16 - IronKey + m_type;
	case Consumable:
		return 8 - Apple + m_type;
	case Other:
		assert(false); // todo !!
	}
	return -1;
}

int CMiscellaneous::GetSheetForGroup() {
	ItemGroup group = GetGroup();
	switch (group) {
	case Key:
		return 5;
	case Consumable:
		return 5;
	case Helmet:
	case Shield:
	case Shoes:
	case Amulet:
		return 3;
	case Torso:
	case Legs:
		return 2;
	case Throwable:
		return 1;
	case Other:
		assert(false); // todo !!
	}
	return -1;
}

bool CMiscellaneous::CheckGroup(int slotId) {
	if (slotId == 2) return (GetGroup() == Helmet);
	if (slotId == 3) return (GetGroup() == Amulet);
	if (slotId == 4) return (GetGroup() == Torso);
	if (slotId == 5) return (GetGroup() == Legs);
	if (slotId == 6) return (GetGroup() == Shoes);
	if (slotId >= 8 && slotId <=11) return (GetGroup() == Throwable);
	
	return true;
}
