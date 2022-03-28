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
	for (int i = 0; i < numberPics; i++) {
		DeleteObject( m_items[i]);
	}
}

CBitmap* CItemPic::GetBitmap(CMiscellaneous::ItemType type, int subType) {
	// todo subtype in item pics
	return m_items[type];
}

void CItemPic::InitItems() {
	CDC sourceDC, targetDC;
	sourceDC.CreateCompatibleDC(GetMyDC());
	targetDC.CreateCompatibleDC(GetMyDC());

	CBitmap* tempPic;

	for (int sheet = 0; sheet < 7; sheet++) {
		LoadPic(tempPic, IDB_ITEMS_42 + sheet);
		sourceDC.SelectObject(tempPic);

		
		for (int pic = 0; pic < 32; pic++) {
			int x = pic % 16;
			int y = int(pic / 16);
			int index = pic + sheet * 32;
			CBitmap newBitmap;
			newBitmap.CreateCompatibleBitmap(&targetDC, 16, 16);
			targetDC.StretchBlt(0, 0, 16, 16, &sourceDC, x, y, 16, 16, SRCCOPY);
			DeleteObject(newBitmap);

			m_items[index] = &newBitmap;
		}
		delete tempPic;
	}
	DeleteObject(sourceDC);
	DeleteObject(targetDC);

}