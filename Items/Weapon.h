#pragma once
#include "Item.h"
#include <Attributes/WeaponAttributes.h>
class CWeapon : public CItem
{
public:
	CWeapon(int index, CWeaponAttributes attribute);
	~CWeapon();

	CWeaponAttributes::WeaponType GetType() { return m_attribute.type; }
	int GetCharges() { return m_attribute.charges; }
	CWeaponConst  GetAttributes() { return m_attribute.fixAttributes;  }
	void reduceCharges();
	double GetWeight();
	CString GetName();

	int GetSheetForGroup();
	int GetOffsetForGroup(bool active);
	ItemGroup GetGroup();

private:
	CWeaponAttributes m_attribute;
};

