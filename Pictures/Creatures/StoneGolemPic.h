#pragma once
#include "..\CBasePictures.h"
class CStoneGolemPic : public CBasePictures
{
public:
	CStoneGolemPic(CDC* pDC);
	~CStoneGolemPic();

	CBitmap* GetStoneGolemPic(int id, bool attacking);

private:
	void InitPics();

	CBitmap* m_pStoneGolemBack;
	CBitmap* m_pStoneGolemLeft;
	CBitmap* m_pStoneGolemRight;
	CBitmap* m_pStoneGolemFront;
	CBitmap* m_pStoneGolemAttack;
};

