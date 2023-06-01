#include "stdafx.h"
#include "Item.h"
#include <cassert>

CItem::CItem(int index, ItemType type) : CMovingObject() {
	m_index = index;
	m_itemType = type;
	for (int i = 0; i < 8; i++)
		ClearSubitems(i);
}



bool CItem::CheckGroup(int slotId, ItemGroup group) {
	if (slotId == 2) return (group == Helmet);
	if (slotId == 3) return (group == Amulet);
	if (slotId == 4) return (group == Torso);
	if (slotId == 5) return (group == Legs);
	if (slotId == 6) return (group == Shoes);
	if (slotId >= 8 && slotId <= 11) return (group == Throwable || (group == Weapon && GetWeight() < 1));

	return true;
}

char* CItem::getItemTypeString() {
	switch (m_itemType) {
	case WeaponItem: return "weapon";
	case MiscItem: return "misc";
	case ClothItem: return "cloth";
	case PotionItem: return "potion";
	case ScrollItem: return "scroll";
	case ContainerItem: return "container";
	default: assert(false);
	}
}

