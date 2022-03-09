#pragma once
#include "CBasePictures.h"
class CPitPic : public CBasePictures
{
public:
	CPitPic(CDC* pDC);
	~CPitPic();

	CBitmap* GetPitPic(int ebene, int xx);
	CBitmap* GetInvPitPic(int ebene, int xx);
	CBitmap* GetPitCeilingPic(int ebene, int xx);

private:
	void InitPitPics();

	CBitmap* m_pPitLeft[4];
	CBitmap* m_pPitRight[4];
	CBitmap* m_pPitFront[4];

	CBitmap* m_pPitInvLeft[4];
	CBitmap* m_pPitInvRight[4];
	CBitmap* m_pPitInvFront[4];

	CBitmap* m_pPitCeilingLeft[4];
	CBitmap* m_pPitCeilingRight[4];
	CBitmap* m_pPitCeilingFront[4];

};

