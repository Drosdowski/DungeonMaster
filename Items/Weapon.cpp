#include "stdafx.h"
#include "Weapon.h"
#include <cassert>

CWeapon::CWeapon(int index, WeaponType type, int charges) : CItem(index, WeaponItem ) {
	m_type = type;
	m_charges = charges;
}

CWeapon::~CWeapon() {

}

void CWeapon::reduceCharges() {
	m_charges = max(0, m_charges - 1);
}

int CWeapon::GetOffsetForGroup() {
	if (m_type == 2) { // Torch
		return 4 + (int)(m_charges / 4);
	}
	else if (m_type == 5) // Bolt blade
	{
		if (m_charges > 0)
			return 25;
		else
			return 24;
	} else if (m_type >= 9 && m_type <= 23) {
		return m_type - 8;
	}
}

int CWeapon::GetSheetForGroup() {
	if (m_type < 9)
		return 0;
	else if (m_type < 24)
		return 1;
	else
		assert(false); // todo !!
	return -1;
}

CItem::ItemGroup CWeapon::GetGroup() {
	return ItemGroup::Weapon;
}