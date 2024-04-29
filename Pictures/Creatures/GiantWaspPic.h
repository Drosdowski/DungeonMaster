#pragma once
#include "..\CBasePictures.h"
class CGiantWaspPic : public CBasePictures
{
public:
	CGiantWaspPic(CDC* pDC);
	~CGiantWaspPic();

	CBitmap* GetGiantWaspPic(int id, bool attacking);

private:
	void InitPics();

	CBitmap* m_pGiantWaspBack;
	CBitmap* m_pGiantWaspLeft;
	CBitmap* m_pGiantWaspRight;
	CBitmap* m_pGiantWaspFront;
	CBitmap* m_pGiantWaspAttack;
};

