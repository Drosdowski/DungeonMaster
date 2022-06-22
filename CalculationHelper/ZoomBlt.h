#pragma once
class CZoomBlt
{
public:
	static void DrawFullTrans(CDC* pDC, CDC* tmpdc, int x, int y, int w, int h, int sx, int sy, int sw, int sh, int col);
	static void DrawFullStd(CDC* pDC, CDC* tmpdc, int x, int y, int w, int h, int sx, int sy);
	static void DrawFullStretch(CDC* pDC, CDC* tmpdc, int x, int y, int w, int h, int sx, int sy, int sw, int sh);
	static void DrawFullRect(CDC* pDC, int x, int y, int w, int h, int c);

	static RECT ScreenRect();
	static double fx();
	static double fy();

private:
	static const int origX = 320;
	static const int origY = 200;



};

