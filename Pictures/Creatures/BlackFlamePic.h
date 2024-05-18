#pragma once
#include "..\CBasePictures.h"
class CBlackFlamePic : public CBasePictures
{
public:
	CBlackFlamePic(CDC* pDC);
	~CBlackFlamePic();

	CBitmap* GetBlackFlamePic(bool attacking, int flip);

private:
	void InitPics();

	CBitmap* m_pBlackFlameFront[2];
	CBitmap* m_pBlackFlameAttack[2];
};

