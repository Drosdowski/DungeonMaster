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
		return 16 - CMiscellaneousAttributes::IronKey + m_attribute.type;
	case Consumable:
		if (m_attribute.type >= CMiscellaneousAttributes::Apple)
			return 8 - CMiscellaneousAttributes::Apple + m_attribute.type;
		else if (m_attribute.type == CMiscellaneousAttributes::Water)
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
			case CMiscellaneousAttributes::MagicBoxBlue: return 4;
			case CMiscellaneousAttributes::MagicBoxGreen: return 5;
			case CMiscellaneousAttributes::CopperCoin: return 29;
			case CMiscellaneousAttributes::SilverCoin: return 30;
			case CMiscellaneousAttributes::GoldCoin: return 31;
			case CMiscellaneousAttributes::MirrorOfDawn: return 6;
			case CMiscellaneousAttributes::BlueGem: return 1;
			case CMiscellaneousAttributes::OrangeGem: return 2;
			case CMiscellaneousAttributes::GreenGem: return 3;
			case CMiscellaneousAttributes::Bones: return 19;
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
		if (m_attribute.type >= CMiscellaneousAttributes::Apple)
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
		if (m_attribute.type == CMiscellaneousAttributes::Compass)
			return 0;
		if (m_attribute.type >= CMiscellaneousAttributes::Boulder)
			return 4;
		if (m_attribute.type >= CMiscellaneousAttributes::CopperCoin && m_attribute.type <= CMiscellaneousAttributes::GoldCoin)
			return 3;
		assert(false); // todo !!
	}
	return -1;
}


CItem::ItemGroup CMiscellaneous::GetGroup() {
	if (m_attribute.type >= 9 && m_attribute.type <= 24) return ItemGroup::Key;
	if (m_attribute.type >= 29 && m_attribute.type <= 35 || m_attribute.type == 1) return ItemGroup::Consumable;
	if (m_attribute.type == CMiscellaneousAttributes::Boulder || m_attribute.type == CMiscellaneousAttributes::Potion || m_attribute.type == CMiscellaneousAttributes::Bomb) return ItemGroup::Throwable;
	if (m_attribute.type == CMiscellaneousAttributes::Rope) return ItemGroup::Climb;
	return ItemGroup::Other;
}

double CMiscellaneous::GetWeight() {
	return m_attribute.fixAttributes.weight[0];
}