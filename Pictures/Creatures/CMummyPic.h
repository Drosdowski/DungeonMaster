#pragma once
#include "..\CBasePictures.h"
class CMummyPic : public CBasePictures
{
public:
	CMummyPic(CDC* pDC);
	~CMummyPic();

	CBitmap* GetMummyPic(int id, bool attacking);

private:
	void InitPics();

	CBitmap* m_pMummyBack;
	CBitmap* m_pMummyLeft;
	CBitmap* m_pMummyRight;
	CBitmap* m_pMummyFront;
	CBitmap* m_pMummyAttack;

};

