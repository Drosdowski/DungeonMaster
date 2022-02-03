#pragma once
#include "CBasePictures.h"
class CStairsPic : public CBasePictures
{
public:
	CStairsPic(CDC* pDC);
	~CStairsPic();

	CBitmap* GetStairUpFrontPic(int ebene, int xx);
	CBitmap* GetStairDownFrontPic(int ebene, int xx);

	CPoint GetStairsUpFrontPos(int ebene, int xx, CPoint wallPos);
	CPoint GetStairsDownFrontPos(int ebene, int xx, CPoint wallPos);

private:
	void InitStairs();

	CBitmap* m_pStairsDownRight[4];
	CBitmap* m_pStairsDownLeft[4];
	CBitmap* m_pStairsDownFront[4];
	CBitmap* m_pStairsUpRight[4];
	CBitmap* m_pStairsUpLeft[4];
	CBitmap* m_pStairsUpFront[4];

};

