#include "stdafx.h"
#include "..\..\resource.h"
#include "CItem3DPic.h"

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
	delete m_pCompass;
	delete m_pWhiteCloth;
	delete m_pGreenCloth;
	delete m_pLeatherBoots;
	delete m_pLeatherCloth;
	delete m_pSuedeBoots;
	delete m_pSandals;
	delete m_pBerzerkerHelm;
	delete m_pGoldKey;
	delete m_pIronKey;
	delete m_pTorch;
	delete m_pRock;
	delete m_pBoulder;
	delete m_pScroll;
	delete m_pDrumstick;
	for (int w = 0; w < 4; w++)
	{
		delete m_pClub[w];
		delete m_pStoneClub[w];
		delete m_pAxe[w];
		delete m_pSword[w];
		delete m_pDagger[w];
		delete m_pArrow[w];
		delete m_pSlayer[w];
		delete m_pPoisonDart[w];
		if (w < 3) {
			delete m_pThrowingStar[w];
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
	LoadPic(m_pWormRound, IDB_ITEM3D_WORMROUND);
	LoadPic(m_pCompass, IDB_ITEM3D_COMPASS);
	LoadPic(m_pWhiteCloth, IDB_ITEM3D_FINEROBE);
	LoadPic(m_pGreenCloth, IDB_ITEM3D_ELVENDOUBLET);
	LoadPic(m_pLeatherBoots, IDB_ITEM3D_LEATHERBOOTS);
	LoadPic(m_pLeatherCloth, IDB_ITEM3D_LEATHERCLOTH);
	LoadPic(m_pSuedeBoots, IDB_ITEM3D_SUEDEBOOTS);
	LoadPic(m_pSandals, IDB_ITEM3D_SANDALS);
	LoadPic(m_pBerzerkerHelm, IDB_ITEM3D_BERZERKERHELM);
	LoadPic(m_pGoldKey, IDB_ITEM3D_GOLDKEY);
	LoadPic(m_pIronKey, IDB_ITEM3D_IRONKEY);
	LoadPic(m_pTorch, IDB_ITEM3D_TORCH);
	LoadPic(m_pMagicBox[0], IDB_ITEM3D_MAGICBOX_B);
	LoadPic(m_pMagicBox[1], IDB_ITEM3D_MAGICBOX_G);
	LoadPic(m_pWaterskin[0], IDB_ITEM3D_WATERSKIN_E);
	LoadPic(m_pWaterskin[1], IDB_ITEM3D_WATERSKIN_F);
	LoadPic(m_pFlask[0], IDB_ITEM3D_FLASK_EMPTY);
	LoadPic(m_pFlask[1], IDB_ITEM3D_FLASK_FULL);
	LoadPic(m_pCoin[0], IDB_ITEM3D_COIN_GOLD);
	LoadPic(m_pCoin[1], IDB_ITEM3D_COIN_SILVER);
	LoadPic(m_pClub[0], IDB_ITEM3D_CLUB);
	LoadPic(m_pClub[1], IDB_MISSILE_CLUB_B);
	LoadPic(m_pClub[2], IDB_MISSILE_CLUB_F);
	LoadPic(m_pClub[3], IDB_MISSILE_CLUB_S);
	LoadPic(m_pStoneClub[0], IDB_ITEM3D_STONECLUB);
	LoadPic(m_pStoneClub[1], IDB_MISSILE_STONECLUB_B);
	LoadPic(m_pStoneClub[2], IDB_MISSILE_STONECLUB_F);
	LoadPic(m_pStoneClub[3], IDB_MISSILE_STONECLUB_S);
	LoadPic(m_pAxe[0], IDB_ITEM3D_AXE);
	LoadPic(m_pAxe[1], IDB_MISSILE_AXE_B);
	LoadPic(m_pAxe[2], IDB_MISSILE_AXE_F);
	LoadPic(m_pAxe[3], IDB_MISSILE_AXE_S);
	LoadPic(m_pSword[0], IDB_ITEM3D_SWORD);
	LoadPic(m_pSword[1], IDB_MISSILE_SWORD_B);
	LoadPic(m_pSword[2], IDB_MISSILE_SWORD_F);
	LoadPic(m_pSword[3], IDB_MISSILE_SWORD_S);
	LoadPic(m_pDagger[0], IDB_ITEM3D_DAGGER);
	LoadPic(m_pDagger[1], IDB_MISSILE_DAGGER_B);
	LoadPic(m_pDagger[2], IDB_MISSILE_DAGGER_F);
	LoadPic(m_pDagger[3], IDB_MISSILE_DAGGER_S);
	LoadPic(m_pArrow[0], IDB_ITEM3D_ARROW);
	LoadPic(m_pArrow[1], IDB_MISSILE_ARROW_B);
	LoadPic(m_pArrow[2], IDB_MISSILE_ARROW_F);
	LoadPic(m_pArrow[3], IDB_MISSILE_ARROW_S);
	LoadPic(m_pSlayer[0], IDB_ITEM3D_SLAYER);
	LoadPic(m_pSlayer[1], IDB_MISSILE_SLAYER_B);
	LoadPic(m_pSlayer[2], IDB_MISSILE_SLAYER_F);
	LoadPic(m_pSlayer[3], IDB_MISSILE_SLAYER_S);
	LoadPic(m_pThrowingStar[0], IDB_ITEM3D_THROWINGSTAR);
	LoadPic(m_pThrowingStar[1], IDB_MISSILE_THROWINGSTAR_F);
	LoadPic(m_pThrowingStar[2], IDB_MISSILE_THROWINGSTAR_S);
	LoadPic(m_pShield[0], IDB_ITEM3D_SHIELD_S);
	LoadPic(m_pShield[1], IDB_ITEM3D_SHIELD_L);
	LoadPic(m_pPoisonDart[0], IDB_ITEM3D_POISONDART);
	LoadPic(m_pPoisonDart[1], IDB_MISSILE_POISONDART_B);
	LoadPic(m_pPoisonDart[2], IDB_MISSILE_POISONDART_F);
	LoadPic(m_pPoisonDart[3], IDB_MISSILE_POISONDART_S);
	LoadPic(m_pBoulder, IDB_ITEM3D_BOULDER);
	LoadPic(m_pRock, IDB_ITEM3D_ROCK);
	LoadPic(m_pScroll, IDB_ITEM3D_SCROLL);
	LoadPic(m_pDrumstick, IDB_ITEM3D_DRUMSTICK);
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

CBitmap* CItem3DPic::GetClub(bool inAir) {
	if (inAir) {
		rotationCnt = (rotationCnt % 3) + 1;
		return m_pClub[rotationCnt];
	}
	else {
		return m_pClub[0];
	}
}

CBitmap* CItem3DPic::GetStoneClub(bool inAir) {
	if (inAir) {
		rotationCnt = (rotationCnt % 3) + 1;
		return m_pStoneClub[rotationCnt];
	}
	else {
		return m_pStoneClub[0];
	}
}

CBitmap* CItem3DPic::GetAxe(bool inAir) {
	if (inAir) {
		rotationCnt = (rotationCnt % 3) + 1;
		return m_pAxe[rotationCnt];
	}
	else {
		return m_pAxe[0];
	}
}

CBitmap* CItem3DPic::GetSword(bool inAir) {
	if (inAir) {
		return m_pSword[1]; // todo !!	
	}
	else {
		return m_pSword[0];
	}
}

CBitmap* CItem3DPic::GetDagger(bool inAir) {
	if (inAir) {
		return m_pDagger[1]; // todo !!	
	}
	else {
		return m_pDagger[0];
	}
}

CBitmap* CItem3DPic::GetArrow(bool inAir) {
	if (inAir) {
		return m_pArrow[1]; // todo !!	
	}
	else {
		return m_pArrow[0];
	}
}

CBitmap* CItem3DPic::GetSlayer(bool inAir) {
	if (inAir) {
		return m_pSlayer[1]; // todo !!	
	}
	else {
		return m_pSlayer[0];
	}
}

CBitmap* CItem3DPic::GetThrowingStar(bool inAir) {
	if (inAir) {
		return m_pThrowingStar[1]; // todo !!	
	}
	else {
		return m_pThrowingStar[0];
	}
}

CBitmap* CItem3DPic::GetPoisonDart(bool inAir) {
	if (inAir) {
		return m_pPoisonDart[1]; // todo !!	
	}
	else {
		return m_pPoisonDart[0];
	}
}