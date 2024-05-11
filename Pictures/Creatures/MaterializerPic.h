#pragma once
#include "..\CBasePictures.h"
class CMaterializerPic : public CBasePictures
{
public:
	CMaterializerPic(CDC* pDC);
	~CMaterializerPic();

	CBitmap* GetMaterializerPic(bool attacking);

private:
	void InitPics();

	CBitmap* m_pMaterializerFront[3];
	CBitmap* m_pMaterializerAttack;

	int m_iPhase;
};

