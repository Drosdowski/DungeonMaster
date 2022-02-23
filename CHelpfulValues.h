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
	SUBPOS static GetRelativeSubPosPassive(SUBPOS_ABSOLUTE pos, int heroDir);
	
	SUBPOS_ABSOLUTE static GetRelativeSubPosActive(SUBPOS opponentPos, int heroDir);
	SUBPOS_ABSOLUTE static GetRelativeSubPosActive(SUBPOS_ABSOLUTE index, int heroDir);
	SUBPOS static GetPosByIndex(SUBPOS_ABSOLUTE SUBPOSINDEX);
	SUBPOS_ABSOLUTE static GetAbsPosBySubpos(SUBPOS pos);
	SUBPOS_ABSOLUTE static RightFrom(SUBPOS_ABSOLUTE pos);
	SUBPOS_ABSOLUTE static LeftFrom(SUBPOS_ABSOLUTE pos);

};

