#pragma once
#include "..\CBasePictures.h"
class CSkeletonPic : public CBasePictures
{
public:
	CSkeletonPic(CDC* pDC);
	~CSkeletonPic();

	CBitmap* GetSkeletonPic(int id, bool attacking);

private:
	void InitPics();

	CBitmap* m_pSkeletonBack;
	CBitmap* m_pSkeletonLeft;
	CBitmap* m_pSkeletonRight;
	CBitmap* m_pSkeletonFront;
	CBitmap* m_pSkeletonAttack;

};

