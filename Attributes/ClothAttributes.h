#pragma once
#include "..\Consts\ClothConst.h"
class CClothAttributes
{
public:
	enum ClothType {
		CloakOfNight = 1,
		BarbarianHide = 2,
		Sandals = 3,
		LeatherBoots = 4,
		RobeBody = 5,
		RobeLegs = 6,
		FineRobeBody = 7,
		FineRobeLegs = 8,
		Kirtle = 9,
		SilkShirt = 10,
		Tabard = 11,
		Gunna = 12,
		ElvenDoublet = 13,
		ElvenHuke = 14,
		ElvenBoots = 15,
		LeatherJerkin = 16,
		LeatherPants = 17,
		SuedeBoots = 18,
		BluePants = 19,
		Tunic = 20,
		Ghi = 21,
		GhiTrousers = 22,
		Calista = 23,
		CrownOfNerra = 24,
		BezerkerHelm = 25,
		Helmet = 26,
		Basinet = 27,
		Buckler = 28,
		HideShield = 29,
		WoodenShield = 30,
		SmallShield = 31,
		MailAketon = 32,
		LegMail = 33,
		MithralAketon = 34,
		MithralMail = 35,
		CasquenCoif = 36,
		Hosen = 37,
		Armet = 38,
		TorsoPlate = 39,
		LegPlate = 40,
		FootPlate = 41,
		LargeShield = 42,
		HelmOfLyte = 43,
		PlateOfLyte = 44,
		PoleynOfLyte = 45,
		GreaveOfLyte = 46,
		ShieldOfLyte = 47,
		HelmOfDarc = 48,
		PlateOfDarc = 49,
		PoleynOfDarc = 50,
		GreaveOfDarc = 51,
		ShieldOfDarc = 52,
		Flamebain = 54,  // Rüstung
		BootsOfSpeed = 56,
		Halter = 57
	};

	ClothType type;
	CClothConst fixAttributes;
};

