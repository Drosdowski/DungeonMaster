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
	case Throwable:
		if (m_attribute.type == CMiscellaneousAttributes::Boulder) {
			return 0;
		}
		else {
			assert(false); // todo !!
		}
	case Climb:
		return 8;
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
			default: assert(false); // todo !!
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
	case Throwable:
		if (m_attribute.type >= CMiscellaneousAttributes::Boulder)
			return 4;
	case Other:
		if (m_attribute.type == CMiscellaneousAttributes::Compass)
			return 0;
		if (m_attribute.type >= CMiscellaneousAttributes::CopperCoin && m_attribute.type <= CMiscellaneousAttributes::GoldCoin)
			return 3;
		if (m_attribute.type == CMiscellaneousAttributes::Bones)
			return 4;
	}
	assert(false); // todo !!
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
	if (m_attribute.type == CMiscellaneousAttributes::MiscItemType::Water) {
		// 3 = voll = subtype 0
		// 2 = 60% voll = sub type 1
		// 1 = 30% voll = sub type 1
		// 0 = Leer = sub type 2
		double weightEmpty = m_attribute.fixAttributes.weight[2];
		double weightWater = m_attribute.fixAttributes.weight[0] - weightEmpty;

		return weightEmpty + weightWater * m_attribute.subtype / 3;
	}
	else {
		return m_attribute.fixAttributes.weight[0];
	}
}

CString CMiscellaneous::GetName() {
	switch (m_attribute.type) {
	case CMiscellaneousAttributes::Compass: return "Compass";
	case CMiscellaneousAttributes::Water: return "Water";
	case CMiscellaneousAttributes::JewelSymal: return "Jewel Symal";
	case CMiscellaneousAttributes::Illumulet: return "Illumulet";
	case CMiscellaneousAttributes::Ashes: return "Ashes";
	case CMiscellaneousAttributes::BonesHeroes: return "Bones"; // todo
	case CMiscellaneousAttributes::CopperCoin: return "Copper Coin";
	case CMiscellaneousAttributes::SilverCoin: return "Silver Coin";
	case CMiscellaneousAttributes::GoldCoin: return "Gold Coin";
	case CMiscellaneousAttributes::IronKey: return "Iron Key";
	case CMiscellaneousAttributes::KeyOfB: return "Key Of B";
	case CMiscellaneousAttributes::SolidKey: return "Solid Key";
	case CMiscellaneousAttributes::SquareKey: return "Square Key";
	case CMiscellaneousAttributes::TurquoiseKey: return "Turquoise Key";
	case CMiscellaneousAttributes::CrossKey: return "Cross Key";
	case CMiscellaneousAttributes::SkeletonKey: return "Skeleton Key";
	case CMiscellaneousAttributes::GoldKey: return "Gold Key";
	case CMiscellaneousAttributes::WingedKey: return "Winged Key";
	case CMiscellaneousAttributes::TopazKey: return "Topaz Key";
	case CMiscellaneousAttributes::EmeraldKey: return "Emerald Key";
	case CMiscellaneousAttributes::RubyKey: return "Ruby Key";
	case CMiscellaneousAttributes::RaKey: return "Ra Key";
	case CMiscellaneousAttributes::MasterKey: return "Master Key";
	case CMiscellaneousAttributes::Boulder: return "Boulder";
	case CMiscellaneousAttributes::BlueGem: return "Blue Gem";
	case CMiscellaneousAttributes::OrangeGem: return "Orange Gem";
	case CMiscellaneousAttributes::GreenGem: return "Green Gem";
	case CMiscellaneousAttributes::Apple: return "Apple";
	case CMiscellaneousAttributes::Corn: return "Corn";
	case CMiscellaneousAttributes::Bread: return "Bread";
	case CMiscellaneousAttributes::Cheese: return "Cheese";
	case CMiscellaneousAttributes::ScreamerSlice: return "Screamer Slice";
	case CMiscellaneousAttributes::WormRound: return "Worm Round";
	case CMiscellaneousAttributes::Drumstick: return "Drumstick";
	// case CMiscellaneousAttributes::Shank: return "Shank";
	case CMiscellaneousAttributes::DragonSteak: return "Dragon Steak";
	case CMiscellaneousAttributes::GemOfAges: return "Gem Of Ages";
	case CMiscellaneousAttributes::EkkhardCross: return "Ekkhard Cross";
	case CMiscellaneousAttributes::Moonstone: return "Moonstone";
	case CMiscellaneousAttributes::TheHellion: return "The Hellion";
	case CMiscellaneousAttributes::PendantFeral: return "Pendant Feral";
	case CMiscellaneousAttributes::MagicBoxBlue: return "Magic Box Blue";
	case CMiscellaneousAttributes::MagicBoxGreen: return "Magic Box Green";
	case CMiscellaneousAttributes::MirrorOfDawn: return "Mirror Of Dawn";
	case CMiscellaneousAttributes::Rope: return "Rope";
	case CMiscellaneousAttributes::RabbitsFoot: return "Rabbits Foot";
	case CMiscellaneousAttributes::Corbum: return "Corbum";
	case CMiscellaneousAttributes::Choker: return "Choker";
	case CMiscellaneousAttributes::LockPicks: return "Lock Picks";
	case CMiscellaneousAttributes::Magnifier: return "Magnifier";
	case CMiscellaneousAttributes::ZokathraSpell: return "Zokathra Spell";
	case CMiscellaneousAttributes::Bones: return "Bones";
	case CMiscellaneousAttributes::Potion: return "Potion";
	case CMiscellaneousAttributes::Bomb: return "Bomb";
	}
}