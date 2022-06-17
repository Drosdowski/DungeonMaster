#pragma once
#include "..\CBasePictures.h"
class CMagentaWormPic : public CBasePictures
{
public:
	CMagentaWormPic(CDC* pDC);
	~CMagentaWormPic();

	CBitmap* GetMagentaWormPic(bool attacking);

private:
	void InitPics();

	CBitmap* m_pMagentaWormFront;
	CBitmap* m_pMagentaWormAttack;

};

