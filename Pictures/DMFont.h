#pragma once
#include "CBasePictures.h"
class CDMFont : public CBasePictures
{
public:
	CDMFont(CDC* pDC);
	~CDMFont();

	CBitmap* GetBlackLetter() { return m_pFontBlack; }
	CBitmap* GetWhiteLetter() { return m_pFontWhite; }
	CBitmap* GetWallLetter() { return m_pFontWall; }
	CPoint GetKoordsBlack(char letter);
	CPoint GetKoordsWhiteChar(char letter);
	CPoint GetKoordsWhiteSpecialLetter(char letter);
	CPoint GetKoordsWhiteManaSymbol(int sheet, int no);
	CPoint GetKoordsWall(char letter);

private:
	void InitFonts();
	CBitmap* m_pFontBlack;
	CBitmap* m_pFontWhite;
	CBitmap* m_pFontWall;
};

