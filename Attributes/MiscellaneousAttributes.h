#pragma once
#include "..\Consts\MiscConst.h"
class CMiscellaneousAttributes
{
public:
	// http ://dmweb.free.fr/?q=node/266
	enum MiscItemType {
		Compass = 0,
		Water = 1,
		JewelSymal = 2,
		Illumulet = 3,
		Ashes = 4,
		BonesHeroes = 5,
		CopperCoin = 6,
		SilverCoin = 7,
		GoldCoin = 8,
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
		BlueGem = 26,
		OrangeGem = 27,
		GreenGem = 28,
		Apple = 29,
		Corn = 30,
		Bread = 31,
		Cheese = 32,
		ScreamerSlice = 33,
		WormRound = 34,// ???
		Drumstick = 35, // ???
		// Shank = 36, // ???
		DragonSteak = 36,
		GemOfAges = 37,
		EkkhardCross = 38, 
		Moonstone = 39, 
		TheHellion = 40,
		PendantFeral = 41,
		MagicBoxBlue = 42,
		MagicBoxGreen = 43,
		MirrorOfDawn = 44,
		Rope = 45,
		RabbitsFoot = 46,
		Corbum = 47,
		Choker = 48,
		LockPicks = 49,
		Magnifier = 50,
		ZokathraSpell = 51,
		Bones = 52,
		Potion = 68,
		Bomb = 69
		

	};

	MiscItemType type;
	int subtype; // 0 leer 3 voll
	CMiscConst fixAttributes;

};

