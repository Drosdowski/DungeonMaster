#pragma once
#include "..\CBasePictures.h"
class CMagentaWormPic : public CBasePictures
{
public:
	CMagentaWormPic(CDC* pDC);
	~CMagentaWormPic();

	CBitmap* GetMagentaWormPic(bool attacking, int flip);

private:
	void InitPics();

	CBitmap* m_pMagentaWormFront[2];
	CBitmap* m_pMagentaWormAttack[2];

};

