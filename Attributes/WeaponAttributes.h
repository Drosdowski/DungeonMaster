#pragma once
#include <Consts/WeaponConst.h>
class CWeaponAttributes
{
public:
	enum WeaponType {
		EyeOfTime = 0, 
		Stormring = 1,// miss
		Torch = 2,
		Flamitt = 3,
		StaffOfClaws = 4,// miss
		BoltBlade = 5, // Storm ?
		Fury = 6,// miss
		TheFirestaff = 7,
		Dagger = 8,
		Falchion = 9,
		Sword = 10,
		Rapier = 11,
		Sabre = 12,
		SamuraiSword = 13,
		Delta = 14,
		DiamondEdge = 15,
		VorpalBlade = 16,
		TheInquisitor = 17,
		Axe = 18,// miss
		Hardcleave = 19,
		Mace = 20,
		MaceOfOrder = 21,
		Morningstar = 22,
		Club = 23,
		StoneClub = 24,// miss
		Bow = 25,// miss
		Crossbow = 26,
		Arrow = 27,
		Slayer = 28,// miss
		Sling = 29,// miss
		Rock = 30,
		PoisonDart = 31,
		ThrowingStar = 32,
		Stick = 33, 
		Staff = 34, // miss
		Wand = 35, 
		Teowand = 36, 
		YewStaff = 37, // miss
		StaffOfIrra = 38, // miss
		CrossOfNeta = 39, // miss
		SerpentStaff = 40, // miss
		DragonSpit = 41, // miss
		SceptreOfLyf = 42, 
		HornOfFear = 43, 
		SpeedBow = 44, // miss
		FireStaffComplete = 45, 
		Conduit = 52
	};

	WeaponType type;
	int charges;
	CWeaponConst fixAttributes;

};

