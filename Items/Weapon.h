#pragma once
#include "Item.h"
#include <SpecialTile/WeaponAttributes.h>
class CWeapon : public CItem
{
public:
	CWeapon(int index, CWeaponAttributes attribute);
	~CWeapon();

	int GetType() { return m_attribute.type; }
	int GetCharges() { return m_attribute.charges; }
	void reduceCharges();

	int GetSheetForGroup();
	int GetOffsetForGroup();
	ItemGroup GetGroup();

private:
	CWeaponAttributes m_attribute;
};

