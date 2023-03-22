#pragma once
#include "..\CBasePictures.h"
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

	CBitmap* GetWhiteCloth() { return m_pWhiteCloth; }
	CBitmap* GetGreenCloth() { return m_pGreenCloth; }
	CBitmap* GetLeatherBoots() { return m_pLeatherBoots; }
	CBitmap* GetLeatherCloth() { return m_pLeatherCloth; }
	CBitmap* GetSuedeBoots() { return m_pSuedeBoots; }
	CBitmap* GetSandals() { return m_pSandals; }
	CBitmap* GetBerzerkerHelm() { return  m_pBerzerkerHelm; }
		
	CBitmap* GetClub(bool inAir);
	CBitmap* GetStoneClub(bool inAir);
	CBitmap* GetSword(bool inAir);
	CBitmap* GetAxe(bool inAir);
	CBitmap* GetDagger(bool inAir);
	CBitmap* GetArrow(bool inAir);
	CBitmap* GetSlayer(bool inAir);
	CBitmap* GetThrowingStar(bool inAir);
	CBitmap* GetPoisonDart(bool inAir);
	CBitmap* GetShield(bool large) { if (large) return m_pShield[1]; else return m_pShield[0]; }

private:
	void InitBitmap();
	int rotationCnt = 1;

	CBitmap* m_pApple;
	CBitmap* m_pBread;
	CBitmap* m_pCorn;
	CBitmap* m_pCheese;
	CBitmap* m_pScreamerSlice;
	CBitmap* m_pWormRound;
	CBitmap* m_pMagicBox[2];
	CBitmap* m_pLeatherBoots;
	CBitmap* m_pLeatherCloth;
	CBitmap* m_pSuedeBoots;
	CBitmap* m_pSandals;
	CBitmap* m_pGreenCloth;
	CBitmap* m_pWhiteCloth;
	CBitmap* m_pBerzerkerHelm;

	CBitmap* m_pGoldKey;
	CBitmap* m_pIronKey;

	CBitmap* m_pWaterskin[2];
	CBitmap* m_pFlask[2];
	CBitmap* m_pChest[2];
	
	CBitmap* m_pCoin[2];
	CBitmap* m_pCompass;

	CBitmap* m_pClub[4];
	CBitmap* m_pStoneClub[4];
	CBitmap* m_pAxe[4];
	CBitmap* m_pSword[4];
	CBitmap* m_pDagger[4];
	CBitmap* m_pArrow[4];
	CBitmap* m_pSlayer[4];
	CBitmap* m_pPoisonDart[4];
	CBitmap* m_pThrowingStar[3];
	CBitmap* m_pShield[2];
	
	CBitmap* m_pTorch;
	CBitmap* m_pBoulder;
	CBitmap* m_pRock;
	CBitmap* m_pScroll;
	CBitmap* m_pDrumstick;
};

