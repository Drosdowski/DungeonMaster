#pragma once
#include "..\CBasePictures.h"
class CTrolinPic : public CBasePictures
{
public:
	CTrolinPic(CDC* pDC);
	~CTrolinPic();

	CBitmap* GetTrolinPic(int index, bool attacking, int flip);

private:
	void InitPics();

	CBitmap* m_pTrolinFront[2];
	CBitmap* m_pTrolinAttack[2];
	CBitmap* m_pTrolinLeft;
	CBitmap* m_pTrolinRight;
	CBitmap* m_pTrolinBack;

};

