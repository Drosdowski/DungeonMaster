#pragma once
#include "..\CBasePictures.h"
class CAnimatedArmourPic : public CBasePictures
{
public:
	CAnimatedArmourPic(CDC* pDC);
	~CAnimatedArmourPic();

	CBitmap* GetAnimatedArmourPic(int id, bool attacking, int flip);

private:
	void InitPics();

	CBitmap* m_pAnimatedArmourBack;
	CBitmap* m_pAnimatedArmourLeft;
	CBitmap* m_pAnimatedArmourRight;
	CBitmap* m_pAnimatedArmourFront[2];
	CBitmap* m_pAnimatedArmourAttack[2];
};

