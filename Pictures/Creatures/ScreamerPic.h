#pragma once
#include "..\CBasePictures.h"
class CScreamerPic : public CBasePictures
{
public:
	CScreamerPic(CDC* pDC);
	~CScreamerPic();

	CBitmap* GetScreamerPic(bool attacking, int flip);

private:
	void InitPics();

	CBitmap* m_pScreamerFront[2];
	CBitmap* m_pScreamerAttack[2];

};

