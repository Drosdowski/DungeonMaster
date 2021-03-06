#include "stdafx.h"
#include "Item.h"

CItem::CItem(int index, ItemType type) : CMovingObject() {
	m_index = index;
	m_itemType = type;
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



