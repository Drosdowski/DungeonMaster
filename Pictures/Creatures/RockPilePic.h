#pragma once
#include "..\CBasePictures.h"
class CRockPilePic : public CBasePictures
{
public:
	CRockPilePic(CDC* pDC);
	~CRockPilePic();

	CBitmap* GetRockPilePic(bool attacking);

private:
	void InitPics();

	CBitmap* m_pRockPileFront;
	CBitmap* m_pRockPileAttack;

};

