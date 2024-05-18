#pragma once
#include "..\CBasePictures.h"
class CSkeletonPic : public CBasePictures
{
public:
	CSkeletonPic(CDC* pDC);
	~CSkeletonPic();

	CBitmap* GetSkeletonPic(int id, bool attacking, int flip);

private:
	void InitPics();

	CBitmap* m_pSkeletonBack;
	CBitmap* m_pSkeletonLeft;
	CBitmap* m_pSkeletonRight;
	CBitmap* m_pSkeletonFront[2];
	CBitmap* m_pSkeletonAttack[2];

};

