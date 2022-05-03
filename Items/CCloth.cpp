#include "stdafx.h"
#include "Cloth.h"

CCloth::CCloth(int index, CClothAttributes attribute) : CItem(index, ClothItem) {
	m_attribute = attribute;
}

CCloth::~CCloth() {

}

int CCloth::GetOffsetForGroup() {
	if (m_attribute.type == CClothAttributes::LeatherBoots) { 
		return 18;
	}
	else if (m_attribute.type == CClothAttributes::ElvenDoublet)
	{
		return 7;
	}
	else if (m_attribute.type == CClothAttributes::ElvenHuke)
	{
		return 23;
	}
	else if (m_attribute.type == CClothAttributes::Ghi)
	{
		return 10;
	}
	else if (m_attribute.type == CClothAttributes::GhiTrousers)
	{
		return 26;
	}
	else if (m_attribute.type == CClothAttributes::SilkShirt)
	{
		return 6;
	}
	else if (m_attribute.type == CClothAttributes::Tabard)
	{
		return 21;
	}
	return -1;
}

int CCloth::GetSheetForGroup() {
	if (m_attribute.type >= CClothAttributes::ClothType::Sandals || 
		m_attribute.type <= CClothAttributes::ClothType::LeatherBoots)
		return 3;
	else if ((m_attribute.type >= 4 && m_attribute.type <= 14) ||
			(m_attribute.type >= 16 && m_attribute.type <= 17) ||
			(m_attribute.type >= 19 && m_attribute.type <= 22))
		return 1;
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