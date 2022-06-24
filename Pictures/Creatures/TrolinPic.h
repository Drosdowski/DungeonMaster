#pragma once
#include "..\CBasePictures.h"
class CTrolinPic : public CBasePictures
{
public:
	CTrolinPic(CDC* pDC);
	~CTrolinPic();

	CBitmap* GetTrolinPic(int index, bool attacking);

private:
	void InitPics();

	CBitmap* m_pTrolinFront;
	CBitmap* m_pTrolinAttack;
	CBitmap* m_pTrolinLeft;
	CBitmap* m_pTrolinRight;
	CBitmap* m_pTrolinBack;

};

