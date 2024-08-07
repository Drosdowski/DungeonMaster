#pragma once
#include "..\CBasePictures.h"
class CMummyPic : public CBasePictures
{
public:
	CMummyPic(CDC* pDC);
	~CMummyPic();

	CBitmap* GetMummyPic(int id, bool attacking, int flip);

private:
	void InitPics();

	CBitmap* m_pMummyBack;
	CBitmap* m_pMummyLeft;
	CBitmap* m_pMummyRight;
	CBitmap* m_pMummyFront[2];
	CBitmap* m_pMummyAttack[2];
};

