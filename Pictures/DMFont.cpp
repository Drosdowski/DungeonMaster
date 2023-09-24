#include "stdafx.h"
#include "..\resource.h"
#include "DMFont.h"

CDMFont::CDMFont(CDC* pDC) : CBasePictures(pDC)
{
	InitFonts();
}

CDMFont:: ~CDMFont() {
	delete m_pFontBlack;
	delete m_pFontWhite;
	delete m_pFontWall;
}

void CDMFont::InitFonts() {
	LoadPic(m_pFontBlack, IDB_FONT_BLACK);  // 192x6	A-Z
	LoadPic(m_pFontWhite, IDB_FONT_WHITE); // 1024x6  Blank, A-Z, (2 Rows!)
	LoadPic(m_pFontWall, IDB_FONT_WALL);  // 288x8
}

CPoint CDMFont::GetKoordsBlack(char letter) {
	/*int x = (id % 8) * 32;
	int y = ((int)(id / 8)) * 29;
	return CPoint(x, y);*/
}
CPoint CDMFont::GetKoordsWhite(char letter){
	/*int x = (id % 8) * 32;
	int y = ((int)(id / 8)) * 29;
	return CPoint(x, y);*/
}

CPoint CDMFont::GetKoordsWall(char letter)
	/*int x = (id % 8) * 32;
	int y = ((int)(id / 8)) * 29;
	return CPoint(x, y);*/
}