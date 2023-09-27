#pragma once
#include <Consts/WeaponConst.h>
class CWeaponAttributes
{
public:
	enum WeaponType {
		EyeOfTime = 0, // miss
		Stormring = 1,// miss
		Torch = 2,
		Flamitt = 3,// miss
		StaffOfClaws = 4,// miss
		BoltBlade = 5, // Storm ?
		Fury = 6,// miss
		TheFirestaff = 7,// miss
		Dagger = 8,
		Falchion = 9,
		Sword = 10,
		Rapier = 11,
		Sabre = 12,
		SamuraiSword = 13,
		Delta = 14,
		DiamondEdge = 15,
		VorpalBlade = 16,// miss
		TheInquisitor = 17,
		Axe = 18,// miss
		Hardcleave = 19,
		Mace = 20,// miss
		MaceOfOrder = 21,// miss
		Morningstar = 22,
		Club = 23,
		StoneClub = 24,// miss
		Bow = 25,// miss
		Crossbow = 26,// miss
		Arrow = 27,
		Slayer = 28,// miss
		Sling = 29,// miss
		Rock = 30,
		PoisonDart = 31,// miss
		ThrowingStar = 32,
		Stick = 33, // miss
		Staff = 34, // miss
		Wand = 35, // miss
		Teowand = 36, // miss
		YewStaff = 37, // miss
		StaffOfIrra = 38, // miss
		CrossOfNeta = 39, // miss
		SerpentStaff = 40, // miss
		DragonSpit = 41, // miss
		SceptreOfLyf = 42, // miss
		HornOfFear = 43, // miss
		SpeedBow = 44, // miss
		FireStaffComplete = 45 // miss
	};

	WeaponType type;
	int charges;
	CWeaponConst fixAttributes;

};

