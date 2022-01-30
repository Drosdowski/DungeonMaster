#include "stdafx.h"
#include "CBasePictures.h"

CBasePictures::CBasePictures(CDC* pDC) {
	m_pDC = pDC;
}

void CBasePictures::LoadPic(CBitmap*& mPic, int ID) {
	mPic = new CBitmap();
	mPic->LoadBitmap(ID);
}

void CBasePictures::LoadPicAndFlip(CDC* pDC, CBitmap*& mPic, int ID) {
	CDC flipDC;
	flipDC.CreateCompatibleDC(pDC);
	LoadPic(mPic, ID);
	flipDC.SelectObject(mPic);
	BITMAP bmpInfo;
	mPic->GetBitmap(&bmpInfo);
	flipDC.StretchBlt(0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, &flipDC, bmpInfo.bmWidth, 0, -bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);
	DeleteDC(flipDC);
}