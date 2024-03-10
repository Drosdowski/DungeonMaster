#pragma once
#include "CBasePictures.h"
class CPressurePadPic : public CBasePictures
{
public:
	CPressurePadPic(CDC* pDC);
	~CPressurePadPic();

	CBitmap* GetPressurePadPic(int ebene, int xx, boolean isRound);
	CPoint GetPos(int x, int ebene);
	CPoint GetCeilingPos(int x, int ebene);

private:
	void InitPressurePads();

	CBitmap* m_pSquarePressurePadLeft[4];
	CBitmap* m_pSquarePressurePadRight[4];
	CBitmap* m_pSquarePressurePadFront[4];

	CBitmap* m_pRoundPressurePadLeft[4];
	CBitmap* m_pRoundPressurePadRight[4];
	CBitmap* m_pRoundPressurePadFront[4];

};