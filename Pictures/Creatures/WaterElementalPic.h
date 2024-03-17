#pragma once
#include "..\CBasePictures.h"
class CWaterElementalPic : public CBasePictures
{
public:
	CWaterElementalPic(CDC* pDC);
	~CWaterElementalPic();

	CBitmap* GetWaterElementalPic(bool attacking);

private:
	void InitPics();

	CBitmap* m_pWaterElementalFront;
	CBitmap* m_pWaterElementalAttack;

};

