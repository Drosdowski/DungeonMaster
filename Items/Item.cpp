#include "stdafx.h"
#include "Item.h"

CItem::CItem(int index, ItemType type) {
	m_index = index;
	m_done = false;
	m_flyForce = VEKTOR{ 0,0,0 };
	m_itemType = type;
}


bool CItem::IsFlying()
{
	return (m_flyForce.x != 0 || m_flyForce.y != 0);
}

void CItem::ReduceSpeed() {
	if (m_flyForce.x > 0) m_flyForce.x--;
	if (m_flyForce.y > 0) m_flyForce.y--;
	if (m_flyForce.x < 0) m_flyForce.x++;
	if (m_flyForce.y < 0) m_flyForce.y++;
	m_done = true;
}

bool CItem::HasMovedThisTick() {
	return m_done;
}

void CItem::ResethasMoved() {
	m_done = false;
}

bool CItem::CheckGroup(int slotId, int type) {
	if (slotId == 2) return (GetGroup(type) == Helmet);
	if (slotId == 3) return (GetGroup(type) == Amulet);
	if (slotId == 4) return (GetGroup(type) == Torso);
	if (slotId == 5) return (GetGroup(type) == Legs);
	if (slotId == 6) return (GetGroup(type) == Shoes);
	if (slotId >= 8 && slotId <= 11) return (GetGroup(type) == Throwable);

	return true;
}


CItem::ItemGroup CItem::GetGroup(int type) {
	if (type >= 9 && type <= 24) return ItemGroup::Key;
	if (type >= 29 && type <= 31 || type == 1) return ItemGroup::Consumable;
	return ItemGroup::Other;
}
