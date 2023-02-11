#pragma once
#include "..\Consts\MiscConst.h"
class CMiscellaneousAttributes
{
public:
	enum MiscItemType {
		Compass = 0,
		Water = 1,
		IronKey = 9,
		KeyOfB = 10,
		SolidKey = 11,
		SquareKey = 12,
		TurquoiseKey = 13,
		CrossKey = 14,
		SkeletonKey = 16,
		GoldKey = 17,
		WingedKey = 18,
		TopazKey = 19,
		EmeraldKey = 21,
		RubyKey = 22,
		RaKey = 23,
		MasterKey = 24,
		Boulder = 25,
		Apple = 29,
		Corn = 30,
		Bread = 31,
		Cheese = 32,
		ScreamerSlice = 33,
		WormRound = 34
	};

	MiscItemType type;
	int subtype; // 0 leer 3 voll
	CMiscConst fixAttributes;

};

