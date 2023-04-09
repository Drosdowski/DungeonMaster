#include "stdafx.h"
#include "Cloth.h"

CCloth::CCloth(int index, CClothAttributes attribute) : CItem(index, ClothItem) {
	m_attribute = attribute;
}

CCloth::~CCloth() {
}

int CCloth::GetOffsetForGroup() {
	switch (m_attribute.type) {
	case CClothAttributes::BezerkerHelm: return 0;
	case CClothAttributes::Helmet: return 1;
	case CClothAttributes::Basinet: return 2;
	case CClothAttributes::CasquenCoif: return 3;
	case CClothAttributes::HelmOfDarc: return 6;
	case CClothAttributes::SilkShirt: return 6;
	case CClothAttributes::ElvenDoublet: return 7;
	case CClothAttributes::LeatherJerkin: return 8;
	case CClothAttributes::Ghi: return 10;
	case CClothAttributes::Sandals: return 16;
	case CClothAttributes::SuedeBoots: return 17;
	case CClothAttributes::LeatherBoots: return 18;
	case CClothAttributes::Tabard: return 21;
	case CClothAttributes::ElvenHuke: return 23;
	case CClothAttributes::LeatherPants: return 24;
	case CClothAttributes::GhiTrousers: return 26;

	case CClothAttributes::Buckler: return 9;
	case CClothAttributes::HideShield: return 10;
	case CClothAttributes::SmallShield: return 11;
	case CClothAttributes::WoodenShield: return 12;
	case CClothAttributes::LargeShield: return 13;
	case CClothAttributes::ShieldOfLyte: return 14;
	case CClothAttributes::ShieldOfDarc: return 15;


	}
	return -1;
}

int CCloth::GetSheetForGroup() {
	if ((m_attribute.type >= CClothAttributes::Sandals && m_attribute.type <= CClothAttributes::LeatherBoots) ||
		(m_attribute.type >= CClothAttributes::BezerkerHelm && m_attribute.type <= CClothAttributes::SmallShield) ||
		(m_attribute.type == CClothAttributes::LargeShield) ||
		(m_attribute.type == CClothAttributes::ShieldOfLyte) ||
		(m_attribute.type == CClothAttributes::ShieldOfDarc))
		return 3;
	else if ((m_attribute.type >= CClothAttributes::ClothType::RobeBody && m_attribute.type <= CClothAttributes::ClothType::ElvenHuke) ||
			(m_attribute.type >= CClothAttributes::ClothType::LeatherJerkin && m_attribute.type <= CClothAttributes::ClothType::LeatherPants) ||
			(m_attribute.type >= CClothAttributes::ClothType::BluePants && m_attribute.type <= CClothAttributes::ClothType::GhiTrousers))
		return 2;
	else
		return -1;
}


CItem::ItemGroup CCloth::GetGroup() {
	switch (m_attribute.type) {
	case 23: case 24: case 25: case 26: case 27: case 38: case 48:
		return ItemGroup::Helmet;
	case 1: case 5: case 7: case 9: case 10: case 11: case 12: case 13: case 16: case 21:
		return ItemGroup::Torso;
	case 2: case 6: case 8: case 14: case 17: case 19: case 22: case 33: case 37: case 40:
		return ItemGroup::Legs;
	case 3: case 4: case 15: case 18: case 41: case 56:
		return ItemGroup::Shoes;
	case 28: case 29: case 30: case 31: case 42: case 47: case 52:
		return ItemGroup::Shield;
	}
	return ItemGroup::Other; // todo ergänzen
}


double CCloth::GetWeight() {
	return m_attribute.fixAttributes.weight[0];
}

int CCloth::GetArmorClass() {
	return m_attribute.fixAttributes.armor;
}
