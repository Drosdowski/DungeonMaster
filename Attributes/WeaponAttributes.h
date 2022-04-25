#pragma once
class CWeaponAttributes
{
public:
	enum WeaponType {
		Torch = 2,
		BoltBlade = 5,
		Dagger = 8,
		Falchion = 9,
		Sword = 10,
		Rapier = 11,
		Sabre = 12,
		SamuraiSword = 13,
		Delta = 14,
		DiamondEdge = 15,
		Inquisitor = 17,
		Hardcleave = 19,
		Club = 23,
		Arrow = 27
	};

	WeaponType type;
	int charges;

};

