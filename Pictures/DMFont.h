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
	CPoint GetKoordsWhite(int id);
	CPoint GetKoordsWall(int id);

private:
	void InitFonts();
	CBitmap* m_pFontBlack;
	CBitmap* m_pFontWhite;
	CBitmap* m_pFontWall;
};

