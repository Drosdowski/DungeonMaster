#pragma once
#include "CBasePictures.h"
class CPressurePadPic : public CBasePictures
{
public:
	CPressurePadPic(CDC* pDC);
	~CPressurePadPic();

private:
	void InitPressurePads();

	CBitmap* m_pPressurePadLeft[4];
	CBitmap* m_pPressurePadRight[4];
	CBitmap* m_pPressurePadFront[4];

};