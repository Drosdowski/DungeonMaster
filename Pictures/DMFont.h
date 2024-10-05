#pragma once
#include "CBasePictures.h"
class CDMFont : public CBasePictures
{
public:
	CDMFont(CDC* pDC);
	~CDMFont();

	CBitmap* GetBlackLetters() { return m_pFontBlack; }
	CBitmap* GetWhiteLetters() { return m_pFontWhite; }
	CBitmap* GetWallLetters() { return m_pFontWall; }
	CBitmap* GetLightGreyLetters() { return m_pFontLightGrey; }
	CPoint GetKoordsBlack(char letter);
	CPoint GetKoordsWhiteChar(char letter);
	CPoint GetKoordsLightGreyChar(char letter);
	// CPoint GetKoordsWhiteSpecialLetter(char letter);
	CPoint GetKoordsWhiteManaSymbol(int sheet, int no);
	CPoint GetKoordsWall(char letter);

private:
	void InitFonts();
	CBitmap* m_pFontBlack;
	CBitmap* m_pFontWhite;
	CBitmap* m_pFontWall;
	CBitmap* m_pFontLightGrey;
};

