#include "stdafx.h"
#include "..\..\resource.h"
#include "..\..\Items\Item.h"
#include "..\CBasePictures.h"
#include "CItemPic.h"


CItemPic::CItemPic(CDC* pDC) : CBasePictures(pDC)
{
	InitItems();
}
CItemPic::~CItemPic() {
	for (int i = 0; i < 7; i++) {
		delete m_itemSheet[i];
	}
}

CBitmap* CItemPic::GetBitmapSheet(CItem* item) {
	int sheet = item->GetSheetForGroup();
	return m_itemSheet[sheet];
}

void CItemPic::InitItems() {
	for (int sheet = 0; sheet < 7; sheet++) {
		LoadPic(m_itemSheet[sheet], IDB_ITEMS_42 + sheet);
	}
}

CPoint CItemPic::GetSheetKoords(CItem* item) {
	int pos = item->GetOffsetForGroup();
	int x = pos % 16;
	int y = int(pos / 16);

	return CPoint(x * 16, y * 16);
}
