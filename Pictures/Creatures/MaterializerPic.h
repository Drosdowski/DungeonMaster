#pragma once
#include "..\CBasePictures.h"
class CMaterializerPic : public CBasePictures
{
public:
	CMaterializerPic(CDC* pDC);
	~CMaterializerPic();

	CBitmap* GetMaterializerPic(bool attacking, int flip);

private:
	void InitPics();

	CBitmap* m_pMaterializerFront[3][2];
	CBitmap* m_pMaterializerAttack[2];

	int m_iPhase;
};

