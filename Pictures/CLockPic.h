#pragma once
#include "CBasePictures.h"
class CLockPic : public CBasePictures
{
public:
	CLockPic(CDC* pDC);
	~CLockPic();

	CBitmap* GetLockFront(int index);
	CBitmap* GetLockSide(int index, bool left);

private:
	void InitPics();
};

