#include "stdafx.h"
#include "..\..\resource.h"
#include "..\..\Items\CMiscellaneous.h"
#include "..\CBasePictures.h"
#include "CItemPic.h"


CItemPic::CItemPic(CDC* pDC) : CBasePictures(pDC)
{
	InitItems();
}
CItemPic::~CItemPic() {
	for (int i = 0; i < 7; i++) {
		DeleteObject(m_itemSheet);
	}
}

CBitmap* CItemPic::GetBitmap(CMiscellaneous::ItemType type, int subType) {
	// todo subtype in item pics
	int sheet = (int)(type / 32);
	return m_itemSheet[sheet];
}

void CItemPic::InitItems() {
	for (int sheet = 0; sheet < 7; sheet++) {
		LoadPic(m_itemSheet[sheet], IDB_ITEMS_42 + sheet);
	}
}

CPoint CItemPic::GetSheetKoords(CMiscellaneous::ItemType type, int subType) {
	int x = type % 16;
	int y = int(type / 16);

	return CPoint(x * 16, y * 16);
}
