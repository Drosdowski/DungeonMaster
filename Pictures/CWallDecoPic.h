#pragma once
#include "CBasePictures.h"
const int maxAnz = 60;
class CWallDecoPic : public CBasePictures
{
public:
	CWallDecoPic(CDC* pDC);
	~CWallDecoPic();

	CBitmap* GetPicFront(WallDecorationType index);
	CBitmap* GetPicSide(WallDecorationType index, bool left);
	bool DrawNearFloor(WallDecorationType index);

private:
	void InitPics();
	CBitmap* m_pDecoFront[maxAnz];
	CBitmap* m_pDecoRight[maxAnz];
	CBitmap* m_pDecoLeft[maxAnz];

};

