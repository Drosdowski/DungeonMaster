#include "stdafx.h"
#include "CMiscellaneous.h"
#include "..\Pictures\Items3D\CItem3DPic.h"
#include <cassert>

CMiscellaneous::CMiscellaneous(int index, MiscItemType type, int subtype) : CItem(index, MiscItem) {
	m_type = type;
	m_subtype = subtype;
}

CMiscellaneous::~CMiscellaneous() {

}


int CMiscellaneous::GetOffsetForGroup() {
	ItemGroup group = GetGroup();
	switch (group) {
	case Key:
		return 16 - IronKey + m_type;
	case Consumable:
		if (m_type >= Apple)
			return 8 - Apple + m_type;
		else if (m_type == Water)
			if (m_subtype == 0)
				return 8;
			else
				return 9;
		else
			assert(false);
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
		if (m_type >= Apple)
			return 5;
		else
			return 0;
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


CItem::ItemGroup CMiscellaneous::GetGroup() {
	if (m_type >= 9 && m_type <= 24) return ItemGroup::Key;
	if (m_type >= 29 && m_type <= 31 || m_type == 1) return ItemGroup::Consumable;
	return ItemGroup::Other;
}