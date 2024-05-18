#pragma once
#include "..\CBasePictures.h"
class CVexirkPic : public CBasePictures
{
public:
	CVexirkPic(CDC* pDC);
	~CVexirkPic();

	CBitmap* GetVexirkPic(int id, bool attacking, int flip);

private:
	void InitPics();

	CBitmap* m_pVexirkBack;
	CBitmap* m_pVexirkLeft;
	CBitmap* m_pVexirkRight;
	CBitmap* m_pVexirkFront[2];
	CBitmap* m_pVexirkAttack[2];
};

