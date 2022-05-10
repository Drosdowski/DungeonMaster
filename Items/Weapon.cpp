#include "stdafx.h"
#include "Weapon.h"
#include <cassert>

CWeapon::CWeapon(int index, CWeaponAttributes attribute) : CItem(index, WeaponItem ) {
	m_attribute = attribute;
}

CWeapon::~CWeapon() {

}

void CWeapon::reduceCharges() {
	m_attribute.charges = max(0, m_attribute.charges - 1);
}

int CWeapon::GetOffsetForGroup() {
	if (m_attribute.type == CWeaponAttributes::WeaponType::Torch) { 
		return 4 + (int)(m_attribute.charges / 4);
	}
	else if (m_attribute.type == CWeaponAttributes::WeaponType::BoltBlade) 
	{
		if (m_attribute.charges > 0)
			return 25;
		else
			return 24;
	} else if (m_attribute.type >= 8 && m_attribute.type <= 23) {
		return m_attribute.type - 8;
	}
}

int CWeapon::GetSheetForGroup() {
	if (m_attribute.type < 8)
		return 0;
	else if (m_attribute.type < 33)
		return 1;
	else
		assert(false); // todo !!
	return -1;
}

CItem::ItemGroup CWeapon::GetGroup() {
	return ItemGroup::Weapon;
}

double CWeapon::GetWeight() {
	return m_attribute.fixAttributes.weight[0]; // todo sub berücksichtigen!
}