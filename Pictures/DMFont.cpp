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
	int x = (letter - 65) * 6;
	int y = 0;
	return CPoint(x, y);
}
CPoint CDMFont::GetKoordsWhiteChar(char letter) {
	if (letter >= 32) {
		int x = 260 + 8 * (letter - 32);
		int y = 0;
		return CPoint(x, y);
	}
}

CPoint GetKoordsWhiteSpecialLetter(char letter) {
	if (letter >= 65 && letter < 91) { 
		int x = 10 + 8 * (letter - 65);
		int y = 0;
		return CPoint(x, y);
	}
}

CPoint CDMFont::GetKoordsWall(char letter) {
	int y = 0;
	int x;
	if (letter >= 65 && letter < 91) {
		int x = (letter - 65) * 8;
	}
	else if (letter == ' ') {
		x = 208;
	}
	else if (letter == '.') {
		x = 216;
	}
	else if (letter == '?') {
		x = 224;
	}
	return CPoint(x, y);
}

CPoint CDMFont::GetKoordsWhiteManaSymbol(int sheet, int no) {
	int x = 770 + 8*no + 24 * sheet;
	int y = 0;
	return CPoint(x, y);
}