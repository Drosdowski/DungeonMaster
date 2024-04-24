#pragma once
#include "..\CBasePictures.h"
class CBlackFlamePic : public CBasePictures
{
public:
	CBlackFlamePic(CDC* pDC);
	~CBlackFlamePic();

	CBitmap* GetBlackFlamePic(bool attacking);

private:
	void InitPics();

	CBitmap* m_pBlackFlameFront;
	CBitmap* m_pBlackFlameAttack;
};

