#include "stdafx.h"
#include "ZoomBlt.h"

// todo /2 raus, und Pos() Funktionen entspr. ändern. Viel Arbeit!

void CZoomBlt::DrawFullTrans(CDC* pDC, CDC* tmpdc, int x, int y, int w, int h, int sx, int sy, int sw, int sh, int col)
{
	double x2 = x * fx() / 2;
	double y2 = y * fy() / 2;
	double w2 = w * fx() / 2;
	double h2 = h * fy() / 2;
	pDC->TransparentBlt(x2, y2, w2, h2, tmpdc, sx, sy, sw, sh, col);
}

void CZoomBlt::DrawFullStd(CDC* pDC, CDC* tmpdc, int x, int y, int w, int h, int sx, int sy)
{
	double x2 = x * fx() / 2;
	double y2 = y * fy() / 2;
	double w2 = w * fx() / 2;
	double h2 = h * fy() / 2;
	pDC->BitBlt(x2, y2, w2, h2, tmpdc, sx, sy, SRCCOPY);
}

void CZoomBlt::DrawFullStretch(CDC* pDC, CDC* tmpdc, int x, int y, int w, int h, int sx, int sy, int sw, int sh)
{
	double x2 = x * fx() / 2;
	double y2 = y * fy() / 2;
	double w2 = w * fx() / 2;
	double h2 = h * fy() / 2;
	pDC->StretchBlt(x2, y2, w2, h2, tmpdc, sx, sy, sw, sh, SRCCOPY);
}

void CZoomBlt::DrawFullRect(CDC* pDC, int x, int y, int r, int b, int c)
{
	pDC->FillSolidRect(CRect(x * fx() / 2, y * fy() / 2, r * fx(), b * fy()), c);
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

int CZoomBlt::fx() {
	RECT r = ScreenRect();
	return (640) / origX;
	//return (r.right - r.left) / origX;
}
int CZoomBlt::fy() {
	RECT r = ScreenRect();
	return (400) / origY;
	//return (r.bottom - r.top) / origY;
}

