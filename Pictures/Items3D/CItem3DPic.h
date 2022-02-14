#pragma once
#include "..\CBasePictures.h"
class CItem3DPic : CBasePictures
{
public:
	CItem3DPic(CDC* pDC);
	~CItem3DPic();

	CPoint GetFloorMiddle(int x, int ebene);


	CBitmap* GetApple() { return m_pApple; }


private:
	void InitBitmap();

	CBitmap* m_pApple;
};

