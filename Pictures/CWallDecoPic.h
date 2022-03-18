#pragma once
#include "CBasePictures.h"
class CWallDecoPic : public CBasePictures
{
public:
	CWallDecoPic(CDC* pDC);
	~CWallDecoPic();

	CBitmap* GetPicFront(WallDecorationType index);
	CBitmap* GetPicSide(WallDecorationType index, bool left);

private:
	void InitPics();

	CBitmap* m_pFountainFront;
	CBitmap* m_pFountainRight;
	CBitmap* m_pFountainLeft;

	CBitmap* m_pLeverUpFront;
	CBitmap* m_pLeverUpRight;
	CBitmap* m_pLeverUpLeft;
	CBitmap* m_pLeverDownFront;
	CBitmap* m_pLeverDownRight;
	CBitmap* m_pLeverDownLeft;

};

