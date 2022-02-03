#pragma once
#include "CBasePictures.h"
class CLeverPic : CBasePictures
{
public:
	CLeverPic(CDC* pDC);
	~CLeverPic();
	
	CBitmap* GetLeverFront(int state);
	CBitmap* GetLeverSide(int state, bool left);


private:
	void InitLevers();

	CBitmap* m_pLeverUpFront;
	CBitmap* m_pLeverUpRight;
	CBitmap* m_pLeverUpLeft;
	CBitmap* m_pLeverDownFront;
	CBitmap* m_pLeverDownRight;
	CBitmap* m_pLeverDownLeft;
};

