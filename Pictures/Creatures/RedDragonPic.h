#pragma once
#include "..\CBasePictures.h"
class CRedDragonPic : public CBasePictures
{
public:
	CRedDragonPic(CDC* pDC);
	~CRedDragonPic();

	CBitmap* GetRedDragonPic(int id, bool attacking, int flip);

private:
	void InitPics();

	CBitmap* m_pRedDragonBack;
	CBitmap* m_pRedDragonLeft;
	CBitmap* m_pRedDragonRight;
	CBitmap* m_pRedDragonFront[2];
	CBitmap* m_pRedDragonAttack[2];
};

