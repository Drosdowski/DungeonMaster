#pragma once
#include "..\CBasePictures.h"
class CGhostPic : public CBasePictures
{
public:
	CGhostPic(CDC* pDC);
	~CGhostPic();

	CBitmap* GetGhostPic(bool attacking, int flip);

private:
	void InitPics();

	CBitmap* m_pGhostFront[2];
	CBitmap* m_pGhostAttack[2];

};

