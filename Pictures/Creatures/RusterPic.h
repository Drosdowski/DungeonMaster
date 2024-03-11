#pragma once
#include "..\CBasePictures.h"
class CRusterPic : public CBasePictures
{
public:
	CRusterPic(CDC* pDC);
	~CRusterPic();

	CBitmap* GetRusterPic(int index);

private:
	void InitPics();

	CBitmap* m_pRusterFront;
	CBitmap* m_pRusterRight;
	CBitmap* m_pRusterLeft;
	CBitmap* m_pRusterBack;

};

