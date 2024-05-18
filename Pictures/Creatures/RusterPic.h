#pragma once
#include "..\CBasePictures.h"
class CRusterPic : public CBasePictures
{
public:
	CRusterPic(CDC* pDC);
	~CRusterPic();

	CBitmap* GetRusterPic(int index, int flip);

private:
	void InitPics();

	CBitmap* m_pRusterFront[2];
	CBitmap* m_pRusterRight;
	CBitmap* m_pRusterLeft;
	CBitmap* m_pRusterBack;

};

