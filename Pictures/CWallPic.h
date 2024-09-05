#pragma once
#include "CBasePictures.h"
class CFloorDecoration;
class CWallPic : public CBasePictures
{
public:
	CWallPic(CDC* pDC);
	~CWallPic();

	CPoint GetWallPos(int x, int ebene);

	CPoint GetCenterFromFrontWall(int x, int ebene, bool ofSecondStone);
	CPoint GetCenterFromSideWall(int x, int ebene, bool ofSecondStone);
	CPoint GetBottomCenterFromFrontWall(int x, int ebene);
	CPoint GetBottomCenterFromSideWall(int x, int ebene);
	CBitmap* GetWallPic(int x, int ebene, bool bMirror);

private:
	void InitWalls();

	CBitmap* m_pWallFarLeft[4];
	CBitmap* m_pWallFarRight[4];
	CBitmap* m_pWallLeft[4];
	CBitmap* m_pWallLeftF[4];
	CBitmap* m_pWallRight[4];
	CBitmap* m_pWallRightF[4];
	CBitmap* m_pWallFront[4]; // Front 0 ex. nicht.!
	CBitmap* m_pWallFrontF[4];
};

