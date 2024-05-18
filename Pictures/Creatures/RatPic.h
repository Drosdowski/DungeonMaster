#pragma once
#include "..\CBasePictures.h"
class CPainRatPic : public CBasePictures
{
public:
	CPainRatPic(CDC* pDC);
	~CPainRatPic();

	CBitmap* GetPainRatPic(int richt, bool attacking, int flip);

private:
	void InitPics();

	CBitmap* m_pPainRatFront[2];
	CBitmap* m_pPainRatLeft;
	CBitmap* m_pPainRatRight;
	CBitmap* m_pPainRatBack;
	CBitmap* m_pPainRatAttack[2];

};

