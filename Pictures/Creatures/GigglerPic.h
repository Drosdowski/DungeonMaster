#pragma once
#include "..\CBasePictures.h"
class CGigglerPic: public CBasePictures
{
public:
	CGigglerPic(CDC* pDC);
	~CGigglerPic();

	CBitmap* GetGigglerPic(int id, bool attacking);

private:
	void InitPics();

	CBitmap* m_pGigglerBack;
	CBitmap* m_pGigglerLeft;
	CBitmap* m_pGigglerRight;
	CBitmap* m_pGigglerFront;
	CBitmap* m_pGigglerAttack;
};

