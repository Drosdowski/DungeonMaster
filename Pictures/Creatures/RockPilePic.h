#pragma once
#include "..\CBasePictures.h"
class CRockPilePic : public CBasePictures
{
public:
	CRockPilePic(CDC* pDC);
	~CRockPilePic();

	CBitmap* GetRockPilePic(bool attacking, int flip);

private:
	void InitPics();

	CBitmap* m_pRockPileFront[2];
	CBitmap* m_pRockPileAttack[2];

};

