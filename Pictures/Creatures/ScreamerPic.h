#pragma once
#include "..\CBasePictures.h"
class CScreamerPic : public CBasePictures
{
public:
	CScreamerPic(CDC* pDC);
	~CScreamerPic();

	CBitmap* GetScreamerPic(bool attacking);

private:
	void InitPics();

	CBitmap* m_pScreamerFront;
	CBitmap* m_pScreamerAttack;

};

