#pragma once
#include "..\CBasePictures.h"
#include "..\..\Items\Item.h"

class CItemPic : public CBasePictures
{
#define numberPics 224
public:
	CItemPic(CDC* pDC);
	~CItemPic();

	CBitmap* GetBitmapSheet(CItem* misc);
	CPoint GetSheetKoords(CItem* misc);

private:
	void InitItems();

	CBitmap* m_itemSheet[7];
};

