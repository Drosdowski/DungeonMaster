#pragma once
#include "..\CBasePictures.h"
class CSwampSlimePic : public CBasePictures
{
public:
	CSwampSlimePic(CDC* pDC);
	~CSwampSlimePic();

	CBitmap* GetSwampSlimePic(bool attacking, int flip);

private:
	void InitPics();

	CBitmap* m_pSwampSlimeFront[2];
	CBitmap* m_pSwampSlimeAttack[2];

};