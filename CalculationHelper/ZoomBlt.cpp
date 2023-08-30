#include "stdafx.h"
#include "ZoomBlt.h"

void CZoomBlt::DrawFullTrans(CDC* pDC, CDC* tmpdc, int x, int y, int w, int h, int sx, int sy, int sw, int sh, int col)
{
	pDC->TransparentBlt(fx(x), fy(y), fx(w), fy(h), tmpdc, sx, sy, sw, sh, col);
}

void CZoomBlt::DrawFullStd(CDC* pDC, CDC* tmpdc, int x, int y, int w, int h, int sx, int sy)
{
	pDC->BitBlt(fx(x), fy(y), fx(w), fy(h), tmpdc, sx, sy, SRCCOPY);
}

void CZoomBlt::DrawFullStretch(CDC* pDC, CDC* tmpdc, int x, int y, int w, int h, int sx, int sy, int sw, int sh)
{
	pDC->StretchBlt(fx(x), fy(y), fx(w), fy(h), tmpdc, sx, sy, sw, sh, SRCCOPY);
}

void CZoomBlt::DrawFullRect(CDC* pDC, int x, int y, int r, int b, int c)
{
	pDC->FillSolidRect(CRect(fx(x), fy(y), fx(r), fy(b)), c);
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

int CZoomBlt::fx(int x) {
	RECT r = ScreenRect();
	return (int)((r.right - r.left) / origX * x / 2);
}
int CZoomBlt::fy(int y) {
	RECT r = ScreenRect();
	return (int)((r.bottom - r.top) / origY * y / 2);
}

