#pragma once
#include "..\CBasePictures.h"
class CVexirkPic : public CBasePictures
{
	CVexirkPic(CDC* pDC);
	~CVexirkPic();

	CBitmap* GetVexirkPic(int id, bool attacking);

private:
	void InitPics();

	CBitmap* m_pVexirkBack;
	CBitmap* m_pVexirkLeft;
	CBitmap* m_pVexirkRight;
	CBitmap* m_pVexirkFront;
	CBitmap* m_pVexirkAttack;
};

