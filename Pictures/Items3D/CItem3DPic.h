#pragma once
#include "..\CBasePictures.h"
#include "..\..\Attributes\PotionAttributes.h"
class CItem3DPic : CBasePictures
{
public:
	CItem3DPic(CDC* pDC);
	~CItem3DPic();

	CPoint GetFloorMiddle(int x, int ebene);


	CBitmap* GetApple() { return m_pApple; }
	CBitmap* GetBread() { return m_pBread; }
	CBitmap* GetCorn() { return m_pCorn; }
	CBitmap* GetCheese() { return m_pCheese; }
	CBitmap* GetScreamerSlice() { return m_pScreamerSlice; }
	CBitmap* GetWormRound() { return m_pWormRound; }
	CBitmap* GetDrumstick() { return m_pDrumstick; }
	CBitmap* GetDragonSteak() { return m_pDragonSteak; }
	CBitmap* GetGoldKey() { return m_pGoldKey; }
	CBitmap* GetIronKey() { return m_pIronKey; }
	CBitmap* GetTorch() { return m_pTorch; }
	CBitmap* GetWaterskin(int subtype) { return m_pWaterskin[subtype]; }
	CBitmap* GetFlask(int subtype) { return m_pFlask[subtype]; }
	CBitmap* GetChest(bool centered) { return centered ? m_pChest[1] : m_pChest[0]; }
	CBitmap* GetCompass() { return m_pCompass; }
	CBitmap* GetBoulder() { return m_pBoulder; }
	CBitmap* GetRock() { return m_pRock; }
	CBitmap* GetScroll() { return m_pScroll; }
	CBitmap* GetCoin(bool silver) { if (silver) return m_pCoin[1]; else return m_pCoin[0]; }
	CBitmap* GetMagicBox(bool green) { if (green) return m_pMagicBox[1]; else return m_pMagicBox[0]; }
	CBitmap* GetBones() { return m_pBones; }

	CBitmap* GetWhiteCloth() { return m_pWhiteCloth; }
	CBitmap* GetGreenCloth() { return m_pGreenCloth; }
	CBitmap* GetLeatherBoots() { return m_pLeatherBoots; }
	CBitmap* GetLeatherCloth() { return m_pLeatherCloth; }
	CBitmap* GetSuedeBoots() { return m_pSuedeBoots; }
	CBitmap* GetSandals() { return m_pSandals; }
	CBitmap* GetBerzerkerHelm() { return  m_pBerzerkerHelm; }
	CBitmap* GetBluePants() { return m_pBluePants; }
	CBitmap* GetBootsOfSpeed() { return m_pBootsOfSpeed; }
	CBitmap* GetChoker() { return m_pChoker; }
	CBitmap* GetCrown() { return m_pCrown; }
	CBitmap* GetElvenBoots() { return m_pElvenBoots; }
	CBitmap* GetHellion() { return m_pHellion; }
	CBitmap* GetIllumunet() { return m_pIllumunet; }
	CBitmap* GetMailAketon() { return m_pMailAketon; }
	CBitmap* GetMoonstone() { return m_pMoonstone; }
	CBitmap* GetEyeOfTime() { return m_pEyeOfTime; }

	CBitmap* GetClub(bool inAir, bool flip, FlyingVektor v);
	CBitmap* GetStoneClub(bool inAir, bool flip, FlyingVektor v);
	CBitmap* GetSword(bool inAir, bool flip, FlyingVektor v);
	CBitmap* GetAxe(bool inAir, bool flip, FlyingVektor v);
	CBitmap* GetDagger(bool inAir, bool flip, FlyingVektor v);
	CBitmap* GetArrow(bool inAir, bool flip, FlyingVektor v);
	CBitmap* GetSlayer(bool inAir, bool flip, FlyingVektor v);
	CBitmap* GetThrowingStar(bool inAir, bool flip, FlyingVektor v);
	CBitmap* GetPoisonDart(bool inAir, bool flip, FlyingVektor v);
	CBitmap* GetShield(bool large) { if (large) return m_pShield[1]; else return m_pShield[0]; }
	CBitmap* GetPotionBitmap(CPotionAttributes::PotionType potionType);
	CBitmap* GetClothBitmap(int clothType, bool inAir);
	CBitmap* GetMiscBitmap(int miscType, int subType);
	CBitmap* GetWeaponBitmap(int weaponType, bool inAir, bool flip, FlyingVektor v);
	CBitmap* GetScrollBitmap();
	CBitmap* GetContainerBitmap(bool center);
	CBitmap* GetGemBitmap(char color);

private:
	void InitBitmap();
	int rotationCnt = 1;

	CBitmap* m_pApple;
	CBitmap* m_pBread;
	CBitmap* m_pCorn;
	CBitmap* m_pCheese;
	CBitmap* m_pScreamerSlice;
	CBitmap* m_pWormRound;
	CBitmap* m_pDrumstick;
	CBitmap* m_pDragonSteak;
	CBitmap* m_pMagicBox[2];
	CBitmap* m_pLeatherBoots;
	CBitmap* m_pLeatherCloth;
	CBitmap* m_pSuedeBoots;
	CBitmap* m_pSandals;
	CBitmap* m_pGreenCloth;
	CBitmap* m_pWhiteCloth;
	CBitmap* m_pBerzerkerHelm;
	CBitmap* m_pBluePants;
	CBitmap* m_pBootsOfSpeed;
	CBitmap* m_pChoker;
	CBitmap* m_pCrown;
	CBitmap* m_pElvenBoots;
	CBitmap* m_pHellion;
	CBitmap* m_pIllumunet;
	CBitmap* m_pMailAketon;
	CBitmap* m_pMoonstone;
	CBitmap* m_pEyeOfTime;

	CBitmap* m_pGoldKey;
	CBitmap* m_pIronKey;

	CBitmap* m_pWaterskin[2];
	CBitmap* m_pFlask[2];
	CBitmap* m_pChest[3];
	
	CBitmap* m_pCoin[2];
	CBitmap* m_pCompass;

	CBitmap* m_pMorningstar;
	CBitmap* m_pVorpalBlade;
	CBitmap* m_pFirestaff;
	CBitmap* m_pFireStaffComplete;
	CBitmap* m_pSceptreOfLyf;
	CBitmap* m_pStick;
	CBitmap* m_pCrossbow;
	CBitmap* m_pBow;
	CBitmap* m_pStaff;
	CBitmap* m_pMace;
	CBitmap* m_pFlamitt;
	CBitmap* m_pWand;
	CBitmap* m_pConduit;
	CBitmap* m_pClub[4][2];
	CBitmap* m_pStoneClub[4][2];
	CBitmap* m_pAxe[4][2];
	CBitmap* m_pSword[4][2];
	CBitmap* m_pDagger[4][2];
	CBitmap* m_pArrow[4][2];
	CBitmap* m_pSlayer[4][2];
	CBitmap* m_pPoisonDart[4][2];
	CBitmap* m_pThrowingStar[4][2];
	CBitmap* m_pShield[2];
	
	CBitmap* m_pTorch;
	CBitmap* m_pBoulder;
	CBitmap* m_pRock;
	CBitmap* m_pScroll;
	CBitmap* m_pGem[3];
	CBitmap* m_pBones;

	CBitmap* m_pRabbitsFoot;
	CBitmap* m_pCorbamite;
	CBitmap* m_pAshes;
	CBitmap* m_pDragonspit;
	CBitmap* m_pPotion;
	CBitmap* m_pBomb;
	CBitmap* m_pRope;
	CBitmap* m_pHornOfFear;
	CBitmap* m_pMirror;
	CBitmap* m_pLockpicks;
	CBitmap* m_pMagnifier;
	CBitmap* m_pHalter;
};

