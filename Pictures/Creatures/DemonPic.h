#pragma once
#include "..\CBasePictures.h"
class CDemonPic : public CBasePictures
{
public:
	CDemonPic(CDC* pDC);
	~CDemonPic();

	CBitmap* GetDemonPic(int id, bool attacking);

private:
	void InitPics();

	CBitmap* m_pDemonBack;
	CBitmap* m_pDemonLeft;
	CBitmap* m_pDemonRight;
	CBitmap* m_pDemonFront;
	CBitmap* m_pDemonAttack;
};

