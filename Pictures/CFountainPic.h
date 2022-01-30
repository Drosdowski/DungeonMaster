#pragma once
#include "CBasePictures.h"
class CFountainPic : public CBasePictures
{
public:
	CFountainPic(CDC* pDC);
	~CFountainPic();

	CBitmap* GetFountainFront();
	CBitmap* GetFountainSide(bool left);

private:
	void InitFountain();

	CBitmap* m_pFountainFront;
	CBitmap* m_pFountainRight;
	CBitmap* m_pFountainLeft;

};

