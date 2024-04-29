#pragma once
#include "..\CBasePictures.h"
class CGiantScorpionPic : public CBasePictures
{
public:
	CGiantScorpionPic(CDC* pDC);
	~CGiantScorpionPic();

	CBitmap* GetGiantScorpionPic(int id, bool attacking);

private:
	void InitPics();

	CBitmap* m_pGiantScorpionBack;
	CBitmap* m_pGiantScorpionLeft;
	CBitmap* m_pGiantScorpionRight;
	CBitmap* m_pGiantScorpionFront;
	CBitmap* m_pGiantScorpionAttack;
};

