#include "stdafx.h"
#include "Cloth.h"

CCloth::CCloth(int index, CClothAttributes attribute) : CItem(index, ClothItem) {
	m_attribute = attribute;
}

CCloth::~CCloth() {

}

int CCloth::GetOffsetForGroup() {
	switch (m_attribute.type) {
	case CClothAttributes::LeatherBoots: return 18;
	case CClothAttributes::ElvenDoublet: return 7;
	case CClothAttributes::ElvenHuke: return 23;
	case CClothAttributes::Ghi: return 10;
	case CClothAttributes::GhiTrousers: return 26;
	case CClothAttributes::SilkShirt: return 6;
	case CClothAttributes::Tabard: return 21;
	case CClothAttributes::LeatherPants: return 24;
	}
	return -1;
}

int CCloth::GetSheetForGroup() {
	if (m_attribute.type >= CClothAttributes::ClothType::Sandals && 
		m_attribute.type <= CClothAttributes::ClothType::LeatherBoots)
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
	}
	return ItemGroup::Other; // todo ergänzen
}


double CCloth::GetWeight() {
	return m_attribute.fixAttributes.weight[0];
}

int CCloth::GetArmorClass() {
	return m_attribute.fixAttributes.armor;
}
