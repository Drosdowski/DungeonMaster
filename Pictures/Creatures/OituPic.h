#pragma once
#include "..\CBasePictures.h"
class COituPic : public CBasePictures
{
public:
	COituPic(CDC* pDC);
	~COituPic();

	CBitmap* GetOituPic(int id, bool attacking, int flip);

private:
	void InitPics();

	CBitmap* m_pOituBack;
	CBitmap* m_pOituLeft;
	CBitmap* m_pOituRight;
	CBitmap* m_pOituFront[2];
	CBitmap* m_pOituAttack[2];
};

