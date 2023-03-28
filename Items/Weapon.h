#pragma once
#include "Item.h"
#include <Attributes/WeaponAttributes.h>
class CWeapon : public CItem
{
public:
	CWeapon(int index, CWeaponAttributes* attribute);
	~CWeapon();

	int GetType() { return m_attribute->type; }
	int GetCharges() { return m_attribute->charges; }
	CWeaponConst  GetAttributes() { return m_attribute->fixAttributes;  }
	void reduceCharges();
	double GetWeight();

	int GetSheetForGroup();
	int GetOffsetForGroup();
	ItemGroup GetGroup();

private:
	CWeaponAttributes* m_attribute;
};

