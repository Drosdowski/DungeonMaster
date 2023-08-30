// stdafx.cpp : source file that includes just the standard includes
//	DM.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
#include "CalculationHelper/ZoomBlt.h"

bool InRect(CPoint p, int x1, int y1, int x2, int y2)
{
	x1 = CZoomBlt::fx(x1);
	y1 = CZoomBlt::fy(y1);
	x2 = CZoomBlt::fx(x2);
	y2 = CZoomBlt::fy(y2);
	return ((x1<=p.x) && (x2>=p.x) && (y1<=p.y) && (y2>=p.y));
}
