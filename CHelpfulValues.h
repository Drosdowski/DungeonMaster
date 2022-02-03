#pragma once
class CHelpfulValues
{
public:
#define PI 3.1415926536

	CHelpfulValues();

	int m_stx[4];
	int m_sty[4];

	int static OppositeDirection(int direction);
	CPoint static CalcSubPosition(BITMAP bmpInfo, SUBPOS subPos, double faktor, int xx);
	SUBPOS static GetRelativeSubPos(SUBPOS opponentPos, int heroDir);
	SUBPOS static GetRelativeSubPos(int index, int heroDir);
	SUBPOS static GetPosByIndex(int index);

};

