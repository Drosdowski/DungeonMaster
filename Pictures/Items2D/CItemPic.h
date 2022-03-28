#pragma once
#include "..\CBasePictures.h"
#include "..\..\Items\CMiscellaneous.h"

class CItemPic : public CBasePictures
{
#define numberPics 224
public:
	CItemPic(CDC* pDC);
	~CItemPic();

	CBitmap* GetBitmap(CMiscellaneous::ItemType type, int subType);
	CPoint GetSheetKoords(CMiscellaneous::ItemType type, int subType);

private:
	void InitItems();

	CBitmap* m_items[numberPics];
	CBitmap* m_itemSheet[7];
};

