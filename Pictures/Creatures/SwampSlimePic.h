#pragma once
#include "..\CBasePictures.h"
class CSwampSlimePic : public CBasePictures
{
public:
	CSwampSlimePic(CDC* pDC);
	~CSwampSlimePic();

	CBitmap* GetSwampSlimePic(bool attacking);

private:
	void InitPics();

	CBitmap* m_pSwampSlimeFront;
	CBitmap* m_pSwampSlimeAttack;

};