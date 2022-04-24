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
	CBitmap* GetGoldKey() { return m_pGoldKey; }
	CBitmap* GetIronKey() { return m_pIronKey; }
	CBitmap* GetWaterskin(int subtype) { return m_pWaterskin[subtype]; }
	CBitmap* GetClub(bool inAir);
	CBitmap* GetSword(bool inAir);
	CBitmap* GetDagger(bool inAir);

private:
	void InitBitmap();
	int rotationCnt = 1;

	CBitmap* m_pApple;
	CBitmap* m_pBread;
	CBitmap* m_pCorn;
	CBitmap* m_pGoldKey;
	CBitmap* m_pIronKey;
	CBitmap* m_pWaterskin[2];
	CBitmap* m_pClub[4];
	CBitmap* m_pSword[4];
	CBitmap* m_pDagger[4];
};

