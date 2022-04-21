#pragma once
#include "Item.h"
class CWeapon : public CItem
{
public:
	enum WeaponType {
		Torch = 2,
		BoltBlade = 5,
		Falchion = 9,
		Sword = 10,
		Rapier = 11,
		Sabre = 12,
		SamuraiSword = 13,
		Delta = 14,
		DiamondEdge = 15,
		Inquisitor = 17,
		Hardcleave = 19,
		Club = 23
	};


	CWeapon(int index, WeaponType type, int charges);
	~CWeapon();

	int GetType() { return m_type; }
	int GetCharges() { return m_charges; }
	void reduceCharges();

	int GetSheetForGroup();
	int GetOffsetForGroup();

private:
	WeaponType m_type;
	int m_charges;
};

