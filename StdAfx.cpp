// stdafx.cpp : source file that includes just the standard includes
//	DM.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
#include "CalculationHelper/ZoomBlt.h"

bool InRect(CPoint p, int x1, int y1, int x2, int y2)
{
	double fx = CZoomBlt::fx() / 2;
	double fy = CZoomBlt::fy() / 2;
	x1 *= fx;
	y1 *= fy;
	x2 *= fx;
	y2 *= fy;
	return ((x1<=p.x) && (x2>=p.x) && (y1<=p.y) && (y2>=p.y));
}
