#pragma once
#include "CBasePictures.h"
class CStairsPic : public CBasePictures
{
public:
	CStairsPic(CDC* pDC);
	~CStairsPic();

	CBitmap* GetStairUpFrontPic(int xx, int ebene);
	CBitmap* GetStairDownFrontPic(int xx, int ebene);

	CBitmap* GetStairUpSidePic(int xx, int ebene);
	CBitmap* GetStairDownSidePic(int xx, int ebene);


	CPoint GetStairsUpFrontPos(int xx, int ebene, CPoint wallPos);
	CPoint GetStairsDownFrontPos(int xx, int ebene, CPoint wallPos);

	CPoint GetStairsUpSidePos(int xx, int ebene, CPoint wallPos);
	CPoint GetStairsDownSidePos(int xx, int ebene, CPoint wallPos);

private:
	void InitStairs();

	CBitmap* m_pStairsDownRight[4];
	CBitmap* m_pStairsDownLeft[4];
	CBitmap* m_pStairsDownFront[4];
	CBitmap* m_pStairsUpRight[4];
	CBitmap* m_pStairsUpLeft[4];
	CBitmap* m_pStairsUpFront[4];

	CBitmap* m_pStairsDownSideLeft[4];
	CBitmap* m_pStairsUpSideLeft[4];
	CBitmap* m_pStairsDownSideRight[4];
	CBitmap* m_pStairsUpSideRight[4];

};

