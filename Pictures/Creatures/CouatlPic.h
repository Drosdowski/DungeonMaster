#pragma once
#include "..\CBasePictures.h"
class CCouatlPic : public CBasePictures
{
public:
	CCouatlPic(CDC* pDC);
	~CCouatlPic();

	CBitmap* GetCouatlPic(int id, bool attacking, int flip);

private:
	void InitPics();

	CBitmap* m_pCouatlBack;
	CBitmap* m_pCouatlLeft;
	CBitmap* m_pCouatlRight;
	CBitmap* m_pCouatlFront[2];
	CBitmap* m_pCouatlAttack[2];
};

