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
	CPoint static CalcRelSubPosition(BITMAP bmpInfo, CPoint wallPos, SUBPOS subPos, double faktor, int xx);
	SUBPOS static GetRelativeSubPosPassive(SUBPOS opponentPos, int heroDir);
	SUBPOS static GetRelativeSubPosPassive(SUBPOSINDEX index, int heroDir);
	
	SUBPOS static GetRelativeSubPosActive(SUBPOS opponentPos, int heroDir);
	SUBPOS static GetRelativeSubPosActive(SUBPOSINDEX index, int heroDir);
	SUBPOS static GetPosByIndex(SUBPOSINDEX SUBPOSINDEX);
	SUBPOSINDEX static GetIndexBySubpos(SUBPOS pos);
	SUBPOSINDEX static RightFrom(SUBPOSINDEX pos);
	SUBPOSINDEX static LeftFrom(SUBPOSINDEX pos);

};

