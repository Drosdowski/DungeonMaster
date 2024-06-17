#include "stdafx.h"
#include "CBasePictures.h"

CBasePictures::CBasePictures(CDC* pDC) {
	m_pDC = pDC;
}

void CBasePictures::LoadPic(CBitmap*& mPic, int ID) {
	mPic = new CBitmap();
	mPic->LoadBitmap(ID);
}

void CBasePictures::LoadPicAndFlip(CBitmap*& mPic, int ID) {
	CDC flipDC;
	flipDC.CreateCompatibleDC(m_pDC);
	LoadPic(mPic, ID);
	flipDC.SelectObject(mPic);
	BITMAP bmpInfo;
	mPic->GetBitmap(&bmpInfo);
	flipDC.StretchBlt(0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, &flipDC, bmpInfo.bmWidth-1, 0, -bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);
	DeleteDC(flipDC);
}

void CBasePictures::LoadPicAndScale(CBitmap*& mPic, int ID, bool maximum) {
	// false: Scale for medium size; true: scale for small size
	// medium: 2/3
	// small: 1/2
	CDC sourceDC;
	CDC targetDC;
	sourceDC.CreateCompatibleDC(m_pDC);
	targetDC.CreateCompatibleDC(m_pDC);

	CBitmap* bmp = new CBitmap(); 
	bmp->LoadBitmap(ID);
	sourceDC.SelectObject(bmp);

	BITMAP bmpInfo;
	bmp->GetBitmap(&bmpInfo);

	double scaleFactor = maximum ? (1.0/2.0) : (2.0/3.0);
	int newWidth = (int)(bmpInfo.bmWidth * scaleFactor);
	int newHeight = (int)(bmpInfo.bmHeight * scaleFactor);
	
	mPic = new CBitmap();
	mPic->CreateCompatibleBitmap(m_pDC, newWidth, newHeight);
	targetDC.SelectObject(mPic);

	targetDC.StretchBlt(0, 0, newWidth, newHeight, &sourceDC,
		0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);
	
	delete bmp;
	DeleteDC(sourceDC);
	DeleteDC(targetDC);



}
