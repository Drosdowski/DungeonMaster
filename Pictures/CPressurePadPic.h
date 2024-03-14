#pragma once
#include "CBasePictures.h"
class CPressurePadPic : public CBasePictures
{
public:
	CPressurePadPic(CDC* pDC);
	~CPressurePadPic();

	CBitmap* GetPressurePadPic(int ebene, int xx, boolean isRound, boolean isTiny);
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

	CBitmap* m_pTinyPressurePadLeft[4];
	CBitmap* m_pTinyPressurePadRight[4];
	CBitmap* m_pTinyPressurePadFront[4];
};