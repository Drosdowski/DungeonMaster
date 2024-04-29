#pragma once
#include "..\CBasePictures.h"
class COituPic : public CBasePictures
{
public:
	COituPic(CDC* pDC);
	~COituPic();

	CBitmap* GetOituPic(int id, bool attacking);

private:
	void InitPics();

	CBitmap* m_pOituBack;
	CBitmap* m_pOituLeft;
	CBitmap* m_pOituRight;
	CBitmap* m_pOituFront;
	CBitmap* m_pOituAttack;
};

