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

bool CItem::CheckGroup(int slotId, ItemGroup group) {
	if (slotId == 2) return (group == Helmet);
	if (slotId == 3) return (group == Amulet);
	if (slotId == 4) return (group == Torso);
	if (slotId == 5) return (group == Legs);
	if (slotId == 6) return (group == Shoes);
	if (slotId >= 8 && slotId <= 11) return (group == Throwable);

	return true;
}



