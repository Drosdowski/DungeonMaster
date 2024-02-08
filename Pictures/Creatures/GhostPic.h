#pragma once
#include "..\CBasePictures.h"
class CGhostPic : public CBasePictures
{
public:
	CGhostPic(CDC* pDC);
	~CGhostPic();

	CBitmap* GetGhostPic(bool attacking);

private:
	void InitPics();

	CBitmap* m_pGhostFront;
	CBitmap* m_pGhostAttack;

};

