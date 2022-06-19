#include "stdafx.h"
#include "ZoomBlt.h"

void CZoomBlt::DrawFullTrans(CDC* pDC, CDC* tmpdc, int x, int y, int w, int h, int sx, int sy, int sw, int sh, int col)
{
	pDC->TransparentBlt(x, y, w * fx(), h * fy(), tmpdc, sx, sy, sw, sh, col);
}

void CZoomBlt::DrawFullStd(CDC* pDC, CDC* tmpdc, int x, int y, int w, int sx, int sy, int h)
{
	pDC->BitBlt(x, y, w, h, tmpdc, sx, sy, SRCCOPY);
}

void CZoomBlt::DrawFullStretch(CDC* pDC, CDC* tmpdc, int x, int y, int w, int h, int sx, int sy, int sw, int sh)
{
	pDC->StretchBlt(x, y, w, h, tmpdc, sx, sy, sw, sh, SRCCOPY);

}

void CZoomBlt::DrawFullRect(CDC* pDC, int x, int y, int r, int b, int c)
{
	pDC->FillSolidRect(CRect(x, y, r, b), c);
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
	return (r.right - r.left) / origX;
}
int CZoomBlt::fy() {
	RECT r = ScreenRect();
	return (r.bottom - r.top) / origY;
}

