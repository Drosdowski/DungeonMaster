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
	CBitmap* GetGoldKey() { return m_pGoldKey; }
	CBitmap* GetIronKey() { return m_pIronKey; }
	CBitmap* GetWaterskin(int subtype) { return m_pWaterskin[subtype]; }

private:
	void InitBitmap();

	CBitmap* m_pApple;
	CBitmap* m_pBread;
	CBitmap* m_pGoldKey;
	CBitmap* m_pIronKey;
	CBitmap* m_pWaterskin[1];
};

