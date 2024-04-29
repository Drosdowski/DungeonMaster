#pragma once
#include "..\CBasePictures.h"
class CAnimatedArmourPic : public CBasePictures
{
public:
	CAnimatedArmourPic(CDC* pDC);
	~CAnimatedArmourPic();

	CBitmap* GetAnimatedArmourPic(int id, bool attacking);

private:
	void InitPics();

	CBitmap* m_pAnimatedArmourBack;
	CBitmap* m_pAnimatedArmourLeft;
	CBitmap* m_pAnimatedArmourRight;
	CBitmap* m_pAnimatedArmourFront;
	CBitmap* m_pAnimatedArmourAttack;
};

