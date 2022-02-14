#pragma once
#include "..\CBasePictures.h"
class CItemPic : public CBasePictures
{
#define numberPics 224
public:
	CItemPic(CDC* pDC);
	~CItemPic();

	CBitmap* GetBitmap(int type, int subType);

private:
	void InitItems();

	CBitmap* m_items[numberPics];
};

