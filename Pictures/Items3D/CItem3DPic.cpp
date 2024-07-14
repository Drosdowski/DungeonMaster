#include "stdafx.h"
#include "..\..\resource.h"
#include "CItem3DPic.h"
#include "..\..\Attributes\PotionAttributes.h"
#include "..\..\Attributes\ClothAttributes.h"
#include "..\..\Attributes\MiscellaneousAttributes.h"
#include "..\..\Attributes\WeaponAttributes.h"


CItem3DPic::CItem3DPic(CDC* pDC) : CBasePictures(pDC)
{
	InitBitmap();
}

CItem3DPic ::~CItem3DPic() {
	delete m_pApple;
	delete m_pBread;
	delete m_pCorn;
	delete m_pCheese;
	delete m_pScreamerSlice;
	delete m_pWormRound;
	delete m_pDragonSteak;
	delete m_pCompass;
	delete m_pWhiteCloth;
	delete m_pGreenCloth;
	delete m_pLeatherBoots;
	delete m_pLeatherCloth;
	delete m_pSuedeBoots;
	delete m_pSandals;
	delete m_pBerzerkerHelm;
	delete m_pBluePants;
	delete m_pBootsOfSpeed;
	delete m_pChoker;
	delete m_pCrown;
	delete m_pElvenBoots;
	delete m_pHellion;
	delete m_pIllumunet;
	delete m_pMailAketon;
	delete m_pMoonstone;
	delete m_pGoldKey;
	delete m_pIronKey;
	delete m_pTorch;
	delete m_pRock;
	delete m_pBoulder;
	delete m_pScroll;
	delete m_pDrumstick;
	delete m_pBones;
	delete m_pFirestaff;
	delete m_pWand;
	delete m_pRabbitsFoot;
	delete m_pConduit;
	delete m_pCorbamite;
	delete m_pEyeOfTime;
	delete m_pSceptreOfLyf;
	delete m_pAshes;
	delete m_pVorpalBlade;
	delete m_pStick;
	delete m_pCrossbow;
	delete m_pBow;
	delete m_pMace;
	delete m_pStaff;
	delete m_pDragonspit;
	delete m_pMorningstar;
	delete m_pFlamitt;
	delete m_pPotion;
	delete m_pBomb;
	delete m_pRope;
	delete m_pHornOfFear;
	delete m_pMirror;
	delete m_pLockpicks;
	delete m_pFireStaffComplete;
	delete m_pMagnifier;
	delete m_pHalter;
	for (int w = 0; w < 4; w++)
	{
		for (int flip = 0; flip < 2; flip++)
		{
			delete m_pClub[w][flip];
			delete m_pStoneClub[w][flip];
			delete m_pAxe[w][flip];
			delete m_pSword[w][flip];
			delete m_pDagger[w][flip];
			delete m_pArrow[w][flip];
			delete m_pSlayer[w][flip];
			delete m_pPoisonDart[w][flip];
			if (w < 3) {
				delete m_pThrowingStar[w][flip];
			}
		}
		if (w < 3) {
			delete m_pGem[w];
			delete m_pChest[w];
			if (w < 2) {
				delete m_pWaterskin[w];
				delete m_pFlask[w];
				delete m_pCoin[w];
				delete m_pMagicBox[w];
				delete m_pShield[w];
			}
		}
	}
}
	

void CItem3DPic::InitBitmap() {
	LoadPic(m_pApple, IDB_ITEM3D_APPLE);
	LoadPic(m_pBread, IDB_ITEM3D_BREAD);
	LoadPic(m_pCorn, IDB_ITEM3D_CORN);
	LoadPic(m_pCheese, IDB_ITEM3D_CHEESE);
	LoadPic(m_pScreamerSlice, IDB_ITEM3D_SCREAMERSLICE);
	LoadPic(m_pDrumstick, IDB_ITEM3D_DRUMSTICK);
	LoadPic(m_pWormRound, IDB_ITEM3D_WORMROUND);

	LoadPic(m_pCompass, IDB_ITEM3D_COMPASS);

	LoadPic(m_pLeatherBoots, IDB_ITEM3D_LEATHERBOOTS);
	LoadPic(m_pGreenCloth, IDB_ITEM3D_ELVENDOUBLET);
	LoadPic(m_pWhiteCloth, IDB_ITEM3D_FINEROBE);
	LoadPic(m_pLeatherCloth, IDB_ITEM3D_LEATHERCLOTH);
	LoadPic(m_pSuedeBoots, IDB_ITEM3D_SUEDEBOOTS);
	LoadPic(m_pSandals, IDB_ITEM3D_SANDALS);
	LoadPic(m_pBerzerkerHelm, IDB_ITEM3D_BERZERKERHELM);
	LoadPic(m_pBluePants, IDB_ITEM3D_BLUE_PANTS);
	LoadPic(m_pBootsOfSpeed, IDB_ITEM3D_BOOTS_OF_SPEED);
	LoadPic(m_pChoker, IDB_ITEM3D_CHOKER);
	LoadPic(m_pCrown, IDB_ITEM3D_CROWN);
	LoadPic(m_pElvenBoots, IDB_ITEM3D_ELVEN_BOOTS);
	LoadPic(m_pHellion, IDB_ITEM3D_HELLION);
	LoadPic(m_pIllumunet, IDB_ITEM3D_ILLUMUNET);
	LoadPic(m_pMailAketon, IDB_ITEM3D_MAIL_AKETON);
	LoadPic(m_pMoonstone, IDB_ITEM3D_MOONSTONE);
	LoadPic(m_pGoldKey, IDB_ITEM3D_GOLDKEY);
	LoadPic(m_pIronKey, IDB_ITEM3D_IRONKEY);
	LoadPic(m_pTorch, IDB_ITEM3D_TORCH);

	LoadPic(m_pFirestaff, IDB_ITEM3D_FIRESTAFF);
	LoadPic(m_pWand, IDB_ITEM3D_WAND);
	LoadPic(m_pRabbitsFoot, IDB_ITEM3D_RABBITS_FOOT);
	LoadPic(m_pConduit, IDB_ITEM3D_CONDUIT);
	LoadPic(m_pCorbamite, IDB_ITEM3D_CORBAMITE);
	LoadPic(m_pEyeOfTime, IDB_ITEM3D_EYE_OF_TIME);
	LoadPic(m_pSceptreOfLyf, IDB_ITEM3D_SCEPTRE_OF_LYF);
	LoadPic(m_pAshes, IDB_ITEM3D_ASHES);
	LoadPic(m_pVorpalBlade, IDB_ITEM3D_VORPAL_BLADE);
	LoadPic(m_pStick, IDB_ITEM3D_STICK);
	LoadPic(m_pCrossbow, IDB_ITEM3D_CROSSBOW);
	LoadPic(m_pBow, IDB_ITEM3D_BOW);
	LoadPic(m_pMace, IDB_ITEM3D_MACE);
	LoadPic(m_pStaff, IDB_ITEM3D_STAFF);
	LoadPic(m_pDragonspit, IDB_ITEM3D_DRAGONSPIT);
	LoadPic(m_pMorningstar, IDB_ITEM3D_MORNINGSTAR);
	LoadPic(m_pFlamitt, IDB_ITEM3D_FLAMITT);
	LoadPic(m_pPotion, IDB_ITEM3D_POTION);
	LoadPic(m_pBomb, IDB_ITEM3D_BOMB);
	LoadPic(m_pRope, IDB_ITEM3D_ROPE);
	LoadPic(m_pDragonSteak, IDB_ITEM3D_DRAGON_STEAK);
	LoadPic(m_pHornOfFear, IDB_ITEM3D_HORN_OF_FEAR);
	LoadPic(m_pMirror, IDB_ITEM3D_MIRROR);
	LoadPic(m_pLockpicks, IDB_ITEM3D_LOCKPICKS);
	LoadPic(m_pFireStaffComplete, IDB_ITEM3D_FIRESTAFF_COMPLETE);
	LoadPic(m_pMagnifier, IDB_ITEM3D_MAGNIFIER);
	LoadPic(m_pHalter, IDB_ITEM3D_HALTER);
	LoadPic(m_pClub[0][0], IDB_ITEM3D_CLUB);
	LoadPic(m_pClub[1][0], IDB_MISSILE_CLUB_B);
	LoadPic(m_pClub[2][0], IDB_MISSILE_CLUB_F);
	LoadPic(m_pClub[3][0], IDB_MISSILE_CLUB_S);
	LoadPicAndFlip(m_pClub[0][1], IDB_ITEM3D_CLUB);
	LoadPicAndFlip(m_pClub[1][1], IDB_MISSILE_CLUB_B);
	LoadPicAndFlip(m_pClub[2][1], IDB_MISSILE_CLUB_F);
	LoadPicAndFlip(m_pClub[3][1], IDB_MISSILE_CLUB_S);
	LoadPic(m_pStoneClub[0][0], IDB_ITEM3D_STONECLUB);
	LoadPic(m_pStoneClub[1][0], IDB_MISSILE_STONECLUB_B);
	LoadPic(m_pStoneClub[2][0], IDB_MISSILE_STONECLUB_F);
	LoadPic(m_pStoneClub[3][0], IDB_MISSILE_STONECLUB_S);
	LoadPicAndFlip(m_pStoneClub[0][1], IDB_ITEM3D_STONECLUB);
	LoadPicAndFlip(m_pStoneClub[1][1], IDB_MISSILE_STONECLUB_B);
	LoadPicAndFlip(m_pStoneClub[2][1], IDB_MISSILE_STONECLUB_F);
	LoadPicAndFlip(m_pStoneClub[3][1], IDB_MISSILE_STONECLUB_S);
	LoadPic(m_pAxe[0][0], IDB_ITEM3D_AXE);
	LoadPic(m_pAxe[1][0], IDB_MISSILE_AXE_B);
	LoadPic(m_pAxe[2][0], IDB_MISSILE_AXE_F);
	LoadPic(m_pAxe[3][0], IDB_MISSILE_AXE_S);
	LoadPicAndFlip(m_pAxe[0][1], IDB_ITEM3D_AXE);
	LoadPicAndFlip(m_pAxe[1][1], IDB_MISSILE_AXE_B);
	LoadPicAndFlip(m_pAxe[2][1], IDB_MISSILE_AXE_F);
	LoadPicAndFlip(m_pAxe[3][1], IDB_MISSILE_AXE_S);
	LoadPic(m_pSword[0][0], IDB_ITEM3D_SWORD);
	LoadPic(m_pSword[1][0], IDB_MISSILE_SWORD_B);
	LoadPic(m_pSword[2][0], IDB_MISSILE_SWORD_F);
	LoadPic(m_pSword[3][0], IDB_MISSILE_SWORD_S);
	LoadPicAndFlip(m_pSword[0][1], IDB_ITEM3D_SWORD);
	LoadPicAndFlip(m_pSword[1][1], IDB_MISSILE_SWORD_B);
	LoadPicAndFlip(m_pSword[2][1], IDB_MISSILE_SWORD_F);
	LoadPicAndFlip(m_pSword[3][1], IDB_MISSILE_SWORD_S);
	LoadPic(m_pDagger[0][0], IDB_ITEM3D_DAGGER);
	LoadPic(m_pDagger[1][0], IDB_MISSILE_DAGGER_B);
	LoadPic(m_pDagger[2][0], IDB_MISSILE_DAGGER_F);
	LoadPic(m_pDagger[3][0], IDB_MISSILE_DAGGER_S);
	LoadPicAndFlip(m_pDagger[0][1], IDB_ITEM3D_DAGGER);
	LoadPicAndFlip(m_pDagger[1][1], IDB_MISSILE_DAGGER_B);
	LoadPicAndFlip(m_pDagger[2][1], IDB_MISSILE_DAGGER_F);
	LoadPicAndFlip(m_pDagger[3][1], IDB_MISSILE_DAGGER_S);
	LoadPic(m_pArrow[0][0], IDB_ITEM3D_ARROW);
	LoadPic(m_pArrow[1][0], IDB_MISSILE_ARROW_B);
	LoadPic(m_pArrow[2][0], IDB_MISSILE_ARROW_F);
	LoadPic(m_pArrow[3][0], IDB_MISSILE_ARROW_S);
	LoadPicAndFlip(m_pArrow[0][1], IDB_ITEM3D_ARROW);
	LoadPicAndFlip(m_pArrow[1][1], IDB_MISSILE_ARROW_B);
	LoadPicAndFlip(m_pArrow[2][1], IDB_MISSILE_ARROW_F);
	LoadPicAndFlip(m_pArrow[3][1], IDB_MISSILE_ARROW_S);
	LoadPic(m_pSlayer[0][0], IDB_ITEM3D_SLAYER);
	LoadPic(m_pSlayer[1][0], IDB_MISSILE_SLAYER_B);
	LoadPic(m_pSlayer[2][0], IDB_MISSILE_SLAYER_F);
	LoadPic(m_pSlayer[3][0], IDB_MISSILE_SLAYER_S);
	LoadPicAndFlip(m_pSlayer[0][1], IDB_ITEM3D_SLAYER);
	LoadPicAndFlip(m_pSlayer[1][1], IDB_MISSILE_SLAYER_B);
	LoadPicAndFlip(m_pSlayer[2][1], IDB_MISSILE_SLAYER_F);
	LoadPicAndFlip(m_pSlayer[3][1], IDB_MISSILE_SLAYER_S);
	LoadPic(m_pThrowingStar[0][0], IDB_ITEM3D_THROWINGSTAR);
	LoadPic(m_pThrowingStar[1][0], IDB_MISSILE_THROWINGSTAR_F);
	LoadPic(m_pThrowingStar[2][0], IDB_MISSILE_THROWINGSTAR_S);
	LoadPicAndFlip(m_pThrowingStar[0][1], IDB_ITEM3D_THROWINGSTAR);
	LoadPicAndFlip(m_pThrowingStar[1][1], IDB_MISSILE_THROWINGSTAR_F);
	LoadPicAndFlip(m_pThrowingStar[2][1], IDB_MISSILE_THROWINGSTAR_S);
	LoadPic(m_pShield[0], IDB_ITEM3D_SHIELD_S);
	LoadPic(m_pShield[1], IDB_ITEM3D_SHIELD_L);
	LoadPic(m_pPoisonDart[0][0], IDB_ITEM3D_POISONDART);
	LoadPic(m_pPoisonDart[1][0], IDB_MISSILE_POISONDART_B);
	LoadPic(m_pPoisonDart[2][0], IDB_MISSILE_POISONDART_F);
	LoadPic(m_pPoisonDart[3][0], IDB_MISSILE_POISONDART_S);
	LoadPicAndFlip(m_pPoisonDart[0][1], IDB_ITEM3D_POISONDART);
	LoadPicAndFlip(m_pPoisonDart[1][1], IDB_MISSILE_POISONDART_B);
	LoadPicAndFlip(m_pPoisonDart[2][1], IDB_MISSILE_POISONDART_F);
	LoadPicAndFlip(m_pPoisonDart[3][1], IDB_MISSILE_POISONDART_S);

	LoadPic(m_pWaterskin[0], IDB_ITEM3D_WATERSKIN_E);
	LoadPic(m_pWaterskin[1], IDB_ITEM3D_WATERSKIN_F);
	LoadPic(m_pFlask[0], IDB_ITEM3D_FLASK_EMPTY);
	LoadPic(m_pFlask[1], IDB_ITEM3D_FLASK_FULL);
	LoadPic(m_pChest[0], IDB_ITEM3D_CHEST_C); // Centered
	LoadPic(m_pChest[1], IDB_ITEM3D_CHEST); // Side
	LoadPicAndFlip(m_pChest[2], IDB_ITEM3D_CHEST); // Side
	LoadPic(m_pCoin[0], IDB_ITEM3D_COIN_GOLD);
	LoadPic(m_pCoin[1], IDB_ITEM3D_COIN_SILVER);
	LoadPic(m_pMagicBox[0], IDB_ITEM3D_MAGICBOX_B);
	LoadPic(m_pMagicBox[1], IDB_ITEM3D_MAGICBOX_G);

	LoadPic(m_pBoulder, IDB_ITEM3D_BOULDER);
	LoadPic(m_pRock, IDB_ITEM3D_ROCK);

	LoadPic(m_pScroll, IDB_ITEM3D_SCROLL);
	LoadPic(m_pBones, IDB_ITEM3D_BONES);
	LoadPic(m_pGem[0], IDB_ITEM3D_GEM_BLUE);
	LoadPic(m_pGem[1], IDB_ITEM3D_GEM_ORANGE);
	LoadPic(m_pGem[2], IDB_ITEM3D_GEM_GREEN);
}

CPoint CItem3DPic::GetFloorMiddle(int x, int ebene) {
	CPoint middle;
	switch (x) {
	case 2: 
		if (ebene == 1) middle.x = 20;
		if (ebene == 2) middle.x = 90;
		break;
	case 3:
		if (ebene == 1) middle.x = 418; // tuned for pressure plate
		if (ebene == 2) middle.x = 360;
		break;
	case 4: 
		middle.x = 225; 
		break;
	}
	if (middle.x != 0) {
		switch (ebene) {
		case 0:
			// nur oben links / rechts
			middle.y = 325; break;
		case 1:
			middle.y = 260; break;
		case 2:
			middle.y = 225;	break;
		case 3:
			middle.y = 200; break;
		}
	}

	return middle;
}

CBitmap* CItem3DPic::GetClub(bool inAir, bool flip, FlyingVektor v) {
	if (inAir) {
		rotationCnt = (rotationCnt % 2) + 1;
		return m_pClub[rotationCnt][flip];
	}
	else {
		return m_pClub[0][flip];
	}
}

CBitmap* CItem3DPic::GetStoneClub(bool inAir, bool flip, FlyingVektor v) {
	if (inAir) {
		rotationCnt = (rotationCnt % 3) + 1;
		if (v == Backside) {
			return m_pStoneClub[1][flip];
		}
		else if (v == Frontside) {
			return m_pStoneClub[2][flip];
		}
		else {
			return m_pStoneClub[3][flip];
		}
	}
	else {
		return m_pStoneClub[0][flip];
	}
}

CBitmap* CItem3DPic::GetAxe(bool inAir, bool flip, FlyingVektor v) {
	if (inAir) {
		rotationCnt = (rotationCnt % 2) + 1;
		return m_pAxe[rotationCnt][flip];
	}
	else {
		return m_pAxe[0][flip];
	}
}

CBitmap* CItem3DPic::GetSword(bool inAir, bool flip, FlyingVektor v) {
	if (inAir) {
		if (v == Backside) {
			return m_pSword[1][flip];
		}
		else if (v == Frontside) {
			return m_pSword[2][flip];
		}
		else {
			return m_pSword[3][flip];
		}
	}
	else {
		return m_pSword[0][flip];
	}
}

CBitmap* CItem3DPic::GetDagger(bool inAir, bool flip, FlyingVektor v) {
	if (inAir) {
		// B - F - S
		if (v == Backside) {
			return m_pDagger[1][flip];
		}
		else if (v == Frontside) {
			return m_pDagger[2][flip];
		}
		else {
			return m_pDagger[3][flip];
		}
	}
	else {
		return m_pDagger[0][flip];
	}
}

CBitmap* CItem3DPic::GetArrow(bool inAir, bool flip, FlyingVektor v) {
	if (inAir) {
		if (v == Backside) {
			return m_pArrow[1][flip];
		}
		else if (v == Frontside) {
			return m_pArrow[2][flip];
		}
		else {
			return m_pArrow[3][flip];
		}
	}
	else {
		return m_pArrow[0][flip];
	}
}

CBitmap* CItem3DPic::GetSlayer(bool inAir, bool flip, FlyingVektor v) {
	if (inAir) {
		if (v == Backside) {
			return m_pSlayer[1][flip];
		}
		else if (v == Frontside) {
			return m_pSlayer[2][flip];
		}
		else {
			return m_pSlayer[3][flip];
		}
	}
	else {
		return m_pSlayer[0][flip];
	}
}

CBitmap* CItem3DPic::GetThrowingStar(bool inAir, bool flip, FlyingVektor v) {
	if (inAir) {
		if (v == Backside) {
			return m_pThrowingStar[1][flip];
		}
		else if (v == Frontside) {
			return m_pThrowingStar[2][flip];
		}
		else {
			return m_pThrowingStar[3][flip];
		}
	}
	else {
		return m_pThrowingStar[0][flip];
	}
}

CBitmap* CItem3DPic::GetPoisonDart(bool inAir, bool flip, FlyingVektor v) {
	if (inAir) {
		if (v == Backside) {
			return m_pPoisonDart[1][flip];
		}
		else if (v == Frontside) {
			return m_pPoisonDart[2][flip];
		}
		else {
			return m_pPoisonDart[3][flip];
		}
	}
	else {
		return m_pPoisonDart[0][flip];
	}
}

CBitmap* CItem3DPic::GetPotionBitmap(int potionType) {
	CBitmap* bmp;
	if (potionType == CPotionAttributes::Empty)
		bmp = GetFlask(0);
	else
		bmp = GetFlask(1);
	return bmp;
}

CBitmap* CItem3DPic::GetClothBitmap(int clothType, bool inAir) {
	CBitmap* bmp;
	switch (clothType) {
	case CClothAttributes::Sandals:
		bmp = GetSandals(); break;
	case CClothAttributes::SuedeBoots:
		bmp = GetSuedeBoots(); break;
	case CClothAttributes::LeatherBoots:
		bmp = GetLeatherBoots(); break;
	case CClothAttributes::ElvenBoots:
		bmp = GetElvenBoots(); break;
	case CClothAttributes::BootsOfSpeed:
		bmp = GetBootsOfSpeed(); break;
	case CClothAttributes::LeatherJerkin:
	case CClothAttributes::LeatherPants:
		bmp = GetLeatherCloth(); break;
	case CClothAttributes::ElvenDoublet:
	case CClothAttributes::ElvenHuke:
		bmp = GetGreenCloth(); break;
	case CClothAttributes::FineRobeBody:
	case CClothAttributes::FineRobeLegs:
	case CClothAttributes::Ghi:
	case CClothAttributes::GhiTrousers:
		bmp = GetWhiteCloth(); break;
	case CClothAttributes::BluePants:
	case CClothAttributes::Gunna:
	case CClothAttributes::Kirtle:
	case CClothAttributes::Tunic:
		bmp = GetBluePants(); break;

	case CClothAttributes::Flamebain:
	case CClothAttributes::Hosen:
	case CClothAttributes::LegMail:
	case CClothAttributes::MailAketon:
	case CClothAttributes::MithralAketon:
	case CClothAttributes::MithralMail:
		bmp = GetMailAketon(); break;

	case CClothAttributes::BezerkerHelm:
	case CClothAttributes::Basinet:
	case CClothAttributes::CasquenCoif:
	case CClothAttributes::HelmOfDarc:
	case CClothAttributes::Helmet:
		bmp = GetBerzerkerHelm(); break;
	case CClothAttributes::Calista:
	case CClothAttributes::CrownOfNerra:
		bmp = GetCrown(); break;

	case CClothAttributes::Buckler:
	case CClothAttributes::SmallShield:
	case CClothAttributes::HideShield:
		bmp = GetShield(false); break;
	case CClothAttributes::LargeShield:
	case CClothAttributes::WoodenShield:
	case CClothAttributes::ShieldOfDarc:
	case CClothAttributes::ShieldOfLyte:
		bmp = GetShield(true); break;
	case CClothAttributes::Halter:
		bmp = m_pHalter; break;
	default:
		bmp = NULL;
	}

	return bmp;
}


CBitmap* CItem3DPic::GetScrollBitmap() {
	return GetScroll();
}

CBitmap* CItem3DPic::GetContainerBitmap(bool center) {
	return GetChest(center);
}

CBitmap* CItem3DPic::GetGemBitmap(char color) {
	switch (color) {
	case 'B': return m_pGem[0];
	case 'O': return m_pGem[1];
	case 'G': return m_pGem[2];
	default: ASSERT(false); return NULL;
	}
}

CBitmap* CItem3DPic::GetMiscBitmap(int miscType, int subType) {
	CBitmap* bmp;
	if (miscType == CMiscellaneousAttributes::Apple)
		bmp = GetApple();
	else if (miscType == CMiscellaneousAttributes::Bread)
		bmp = GetBread();
	else if (miscType == CMiscellaneousAttributes::Corn)
		bmp = GetCorn();
	else if (miscType == CMiscellaneousAttributes::Cheese)
		bmp = GetCheese();
	else if (miscType == CMiscellaneousAttributes::Compass)
		bmp = GetCompass();
	else if (miscType >= CMiscellaneousAttributes::IronKey &&
		miscType <= CMiscellaneousAttributes::SkeletonKey)
		bmp = GetIronKey();
	else if (miscType >= CMiscellaneousAttributes::GoldKey &&
		miscType <= CMiscellaneousAttributes::MasterKey)
		bmp = GetGoldKey();
	else if (miscType == CMiscellaneousAttributes::Water)
		if (subType > 0)
			bmp = GetWaterskin(1);
		else
			bmp = GetWaterskin(0);

	else if (miscType == CMiscellaneousAttributes::ScreamerSlice)
		bmp = GetScreamerSlice();
	else if (miscType == CMiscellaneousAttributes::WormRound)
		bmp = GetWormRound();
	else if (miscType == CMiscellaneousAttributes::Drumstick)
		bmp = GetDrumstick();
	else if (miscType == CMiscellaneousAttributes::DragonSteak)
		bmp = GetDragonSteak();
	else if (miscType == CMiscellaneousAttributes::Boulder)
		bmp = GetBoulder();
	else if (miscType == CMiscellaneousAttributes::SilverCoin)
		bmp = GetCoin(1);
	else if (miscType == CMiscellaneousAttributes::CopperCoin || miscType == CMiscellaneousAttributes::GoldCoin)
		bmp = GetCoin(0);
	else if (miscType == CMiscellaneousAttributes::MagicBoxBlue)
		bmp = GetMagicBox(false);
	else if (miscType == CMiscellaneousAttributes::MagicBoxGreen)
		bmp = GetMagicBox(true);
	else if (miscType == CMiscellaneousAttributes::BlueGem)
		bmp = GetGemBitmap('B');
	else if (miscType == CMiscellaneousAttributes::OrangeGem)
		bmp = GetGemBitmap('O');
	else if (miscType == CMiscellaneousAttributes::GreenGem)
		bmp = GetGemBitmap('G');
	else if (miscType == CMiscellaneousAttributes::Bones)
		bmp = GetBones();
	else if (miscType == CMiscellaneousAttributes::Ashes)
		bmp = m_pAshes;
	else if (miscType == CMiscellaneousAttributes::MirrorOfDawn)
		bmp = m_pMirror;
	else if (miscType == CMiscellaneousAttributes::Magnifier)
		bmp = m_pMagnifier;
	else if (miscType == CMiscellaneousAttributes::Corbum || miscType == CMiscellaneousAttributes::ZokathraSpell)
		bmp = m_pCorbamite;
	else if (miscType == CMiscellaneousAttributes::RabbitsFoot)
		bmp = m_pRabbitsFoot;
	else if (miscType == CMiscellaneousAttributes::Bomb)
		bmp = m_pBomb;
	else if (miscType == CMiscellaneousAttributes::Potion)
		bmp = m_pPotion;

	else if (miscType == CMiscellaneousAttributes::Choker)
		bmp = GetChoker();
	else if (miscType == CMiscellaneousAttributes::PendantFeral || miscType == CMiscellaneousAttributes::TheHellion)
		bmp = GetHellion();
	else if (miscType == CMiscellaneousAttributes::Moonstone)
		bmp = GetMoonstone();
	else if (miscType == CMiscellaneousAttributes::EkkhardCross || miscType == CMiscellaneousAttributes::GemOfAges || miscType == CMiscellaneousAttributes::Illumulet || miscType == CMiscellaneousAttributes::JewelSymal)
		bmp = GetIllumunet();
	
	else
		bmp = NULL;

	return bmp;
}

CBitmap* CItem3DPic::GetWeaponBitmap(int weaponType, bool inAir, bool flip, FlyingVektor v) {
	CBitmap* bmp;
	if (weaponType >= CWeaponAttributes::Falchion &&
		weaponType <= CWeaponAttributes::DiamondEdge ||
		weaponType == CWeaponAttributes::BoltBlade ||
		weaponType == CWeaponAttributes::Fury ||
		weaponType == CWeaponAttributes::TheInquisitor)
		bmp = GetSword(inAir, flip, v);
	else if (weaponType == CWeaponAttributes::Axe ||
		weaponType == CWeaponAttributes::Hardcleave)
		bmp = GetAxe(inAir, flip, v);
	else if (weaponType == CWeaponAttributes::Dagger)
		bmp = GetDagger(inAir, flip, v);
	else if (weaponType == CWeaponAttributes::Club)
		bmp = GetClub(inAir, flip, v);
	else if (weaponType == CWeaponAttributes::StoneClub)
		bmp = GetStoneClub(inAir, flip, v);
	else if (weaponType == CWeaponAttributes::Arrow)
		bmp = GetArrow(inAir, flip, v);
	else if (weaponType == CWeaponAttributes::Slayer)
		bmp = GetSlayer(inAir, flip, v);
	else if (weaponType == CWeaponAttributes::ThrowingStar)
		bmp = GetThrowingStar(inAir, flip, v);
	else if (weaponType == CWeaponAttributes::PoisonDart)
		bmp = GetPoisonDart(inAir, flip, v);
	else if (weaponType == CWeaponAttributes::Torch)
		bmp = GetTorch();
	else if (weaponType == CWeaponAttributes::Rock)
		bmp = GetRock();
	else if (weaponType == CWeaponAttributes::Conduit)
		bmp = m_pConduit;
	else if (weaponType == CWeaponAttributes::TheFirestaff)
		bmp = m_pFirestaff;
	else if (weaponType == CWeaponAttributes::FireStaffComplete)
		bmp = m_pFireStaffComplete;
	else if (weaponType == CWeaponAttributes::SceptreOfLyf)
		bmp = m_pSceptreOfLyf;
	else if (weaponType == CWeaponAttributes::VorpalBlade)
		bmp = m_pVorpalBlade;
	else if (weaponType == CWeaponAttributes::Morningstar)
		bmp = m_pMorningstar;
	else if (weaponType == CWeaponAttributes::Stick)
		bmp = m_pStick;
	else if (weaponType == CWeaponAttributes::Crossbow)
		bmp = m_pCrossbow;
	else if (weaponType == CWeaponAttributes::Bow || weaponType == CWeaponAttributes::SpeedBow)
		bmp = m_pBow;
	else if (weaponType == CWeaponAttributes::Flamitt)
		bmp = m_pFlamitt;
	else if (weaponType == CWeaponAttributes::EyeOfTime || weaponType == CWeaponAttributes::Stormring)
		bmp = m_pEyeOfTime;
	else if (weaponType == CWeaponAttributes::DragonSpit)
		bmp = m_pDragonspit;
	else if (weaponType == CWeaponAttributes::HornOfFear)
		bmp = m_pHornOfFear;
	else if (weaponType == CWeaponAttributes::Wand || weaponType == CWeaponAttributes::Teowand)
		bmp = m_pWand;
	else if (weaponType == CWeaponAttributes::MaceOfOrder || weaponType == CWeaponAttributes::Mace)
		bmp = m_pMace;
	else if (weaponType == CWeaponAttributes::StaffOfClaws || weaponType == CWeaponAttributes::YewStaff ||
			weaponType == CWeaponAttributes::StaffOfIrra || weaponType == CWeaponAttributes::SerpentStaff ||
			weaponType == CWeaponAttributes::Staff || weaponType == CWeaponAttributes::Sling)
		bmp = m_pStaff;
	else
		bmp = NULL;

	return bmp;
}
