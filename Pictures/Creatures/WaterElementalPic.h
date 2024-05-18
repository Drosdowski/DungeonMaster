#pragma once
#include "..\CBasePictures.h"
class CWaterElementalPic : public CBasePictures
{
public:
	CWaterElementalPic(CDC* pDC);
	~CWaterElementalPic();

	CBitmap* GetWaterElementalPic(bool attacking, int flip);

private:
	void InitPics();

	CBitmap* m_pWaterElementalFront[2];
	CBitmap* m_pWaterElementalAttack[2];

};

