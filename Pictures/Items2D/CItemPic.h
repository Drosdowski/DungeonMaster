#pragma once
#include "..\CBasePictures.h"
#include "..\..\Items\CMiscellaneous.h"

class CItemPic : public CBasePictures
{
#define numberPics 224
public:
	CItemPic(CDC* pDC);
	~CItemPic();

	CBitmap* GetBitmap(CMiscellaneous* misc);
	CPoint GetSheetKoords(CMiscellaneous* misc);

private:
	void InitItems();

	CBitmap* m_itemSheet[7];
};

