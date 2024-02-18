#pragma once
#include <Consts/WeaponConst.h>
class CWeaponAttributes
{
public:
	enum WeaponType {
		EyeOfTime = 0, 
		Stormring = 1,
		Torch = 2,
		Flamitt = 3,
		StaffOfClaws = 4,
		BoltBlade = 5,
		Fury = 6,
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
		Axe = 18,
		Hardcleave = 19,
		Mace = 20,
		MaceOfOrder = 21,
		Morningstar = 22,
		Club = 23,
		StoneClub = 24,
		Bow = 25,
		Crossbow = 26,
		Arrow = 27,
		Slayer = 28,
		Sling = 29,
		Rock = 30,
		PoisonDart = 31,
		ThrowingStar = 32,
		Stick = 33, 
		Staff = 34, 
		Wand = 35, 
		Teowand = 36, 
		YewStaff = 37, 
		StaffOfIrra = 38, 
		CrossOfNeta = 39, // miss
		SerpentStaff = 40,
		DragonSpit = 41, 
		SceptreOfLyf = 42, 
		HornOfFear = 43, 
		SpeedBow = 44, 
		FireStaffComplete = 45, 
		Conduit = 52
	};

	WeaponType type;
	int charges;
	CWeaponConst fixAttributes;

};

