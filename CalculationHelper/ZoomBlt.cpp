#include "stdafx.h"
#include "ZoomBlt.h"

// todo /2 raus, und Pos() Funktionen entspr. ändern. Viel Arbeit!

void CZoomBlt::DrawFullTrans(CDC* pDC, CDC* tmpdc, int x, int y, int w, int h, int sx, int sy, int sw, int sh, int col)
{
	int x2 = (int)(x * fx() / 2);
	int y2 = (int)(y * fy() / 2);
	int w2 = (int)(w * fx() / 2);
	int h2 = (int)(h * fy() / 2);
	pDC->TransparentBlt(x2, y2, w2, h2, tmpdc, sx, sy, sw, sh, col);
}

void CZoomBlt::DrawFullStd(CDC* pDC, CDC* tmpdc, int x, int y, int w, int h, int sx, int sy)
{
	int x2 = (int)(x * fx() / 2);
	int y2 = (int)(y * fy() / 2);
	int w2 = (int)(w * fx() / 2);
	int h2 = (int)(h * fy() / 2);
	pDC->BitBlt(x2, y2, w2, h2, tmpdc, sx, sy, SRCCOPY);
}

void CZoomBlt::DrawFullStretch(CDC* pDC, CDC* tmpdc, int x, int y, int w, int h, int sx, int sy, int sw, int sh)
{
	int x2 = (int)(x * fx() / 2);
	int y2 = (int)(y * fy() / 2);
	int w2 = (int)(w * fx() / 2);
	int h2 = (int)(h * fy() / 2);
	pDC->StretchBlt(x2, y2, w2, h2, tmpdc, sx, sy, sw, sh, SRCCOPY);
}

void CZoomBlt::DrawFullRect(CDC* pDC, int x, int y, int r, int b, int c)
{
	pDC->FillSolidRect(CRect((int)(x * fx() / 2), (int)(y * fy() / 2), (int)(r * fx()), (int)(b * fy())), c);
}

RECT CZoomBlt::ScreenRect()
{
	RECT desktop;
	// Get a handle to the desktop window
	const HWND hDesktop = GetDesktopWindow();
	// Get the size of screen to the variable desktop
	GetWindowRect(hDesktop, &desktop);
	return desktop;
}

double CZoomBlt::fx() {
	RECT r = ScreenRect();
	return (r.right - r.left) / origX;
}
double CZoomBlt::fy() {
	RECT r = ScreenRect();
	return (r.bottom - r.top) / origY;
}

