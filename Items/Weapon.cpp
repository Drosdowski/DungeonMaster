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
	CItem::ItemGroup group = GetGroup(m_type);
	switch (group) {	
	case Other:
		assert(false); // todo !!
	}
	return -1;
}

int CWeapon::GetSheetForGroup() {
	CItem::ItemGroup group = GetGroup(m_type);
	switch (group) {
	case Shield:
	case Throwable:
		return 1;
	case Other:
		assert(false); // todo !!
	}
	return -1;
}