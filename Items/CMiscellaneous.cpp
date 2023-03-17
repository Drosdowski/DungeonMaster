#include "stdafx.h"
#include "CMiscellaneous.h"
#include "..\Pictures\Items3D\CItem3DPic.h"
#include <cassert>

CMiscellaneous::CMiscellaneous(int index, CMiscellaneousAttributes att) : CItem(index, MiscItem) {
	m_attribute = att;
}

CMiscellaneous::~CMiscellaneous() {

}


int CMiscellaneous::GetOffsetForGroup() {
	ItemGroup group = GetGroup();
	switch (group) {
	case Key:
		return 16 - CMiscellaneousAttributes::MiscItemType::IronKey + m_attribute.type;
	case Consumable:
		if (m_attribute.type >= CMiscellaneousAttributes::MiscItemType::Apple)
			return 8 - CMiscellaneousAttributes::MiscItemType::Apple + m_attribute.type;
		else if (m_attribute.type == CMiscellaneousAttributes::MiscItemType::Water)
			if (m_attribute.subtype == 0)
				return 8;
			else
				return 9;
		else
			assert(false);
	case Other:
		switch (m_attribute.type) {
			case CMiscellaneousAttributes::Compass: return m_attribute.subtype; // N W S E
			case CMiscellaneousAttributes::Boulder: return 0;
			case CMiscellaneousAttributes::CopperCoin: return 29;
			case CMiscellaneousAttributes::SilverCoin: return 30;
			case CMiscellaneousAttributes::GoldCoin: return 31;
		}
		
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
		if (m_attribute.type >= CMiscellaneousAttributes::MiscItemType::Apple)
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
	case Other:
		if (m_attribute.type == CMiscellaneousAttributes::MiscItemType::Compass)
			return 0;
		if (m_attribute.type == CMiscellaneousAttributes::MiscItemType::Boulder)
			return 4;
		if (m_attribute.type >= CMiscellaneousAttributes::MiscItemType::CopperCoin && m_attribute.type <= CMiscellaneousAttributes::MiscItemType::GoldCoin)
			return 3;
		assert(false); // todo !!
	}
	return -1;
}


CItem::ItemGroup CMiscellaneous::GetGroup() {
	if (m_attribute.type >= 9 && m_attribute.type <= 24) return ItemGroup::Key;
	if (m_attribute.type >= 29 && m_attribute.type <= 32 || m_attribute.type == 1) return ItemGroup::Consumable;
	return ItemGroup::Other;
}

double CMiscellaneous::GetWeight() {
	return m_attribute.fixAttributes.weight[0];
}