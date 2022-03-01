#pragma once
class CHelpfulValues
{
public:
#define PI 3.1415926536

	CHelpfulValues();

	int m_stx[4];
	int m_sty[4];

	int static OppositeDirection(int direction);

	static SUBPOS_ABSOLUTE FindNextSubposWithoutFieldChange(SUBPOS_ABSOLUTE posAbs, VEKTOR force);

	VEKTOR static MakeVektor(int direction, int force);
	CPoint static CalcSubPosition(BITMAP bmpInfo, SUBPOS subPos, double faktor, int xx); // for monsters - todo weg damit!
	CPoint static CalcRelSubFloorPosition(BITMAP bmpInfo, CPoint wallPos, SUBPOS subPos, double faktor, int xx, int ebene); // for items 
	SUBPOS static GetRelativeSubPosActive(SUBPOS_ABSOLUTE pos, int heroDir);
	SUBPOS static GetRelativeSubPosPassive(SUBPOS_ABSOLUTE pos, int heroDir);

	SUBPOS_ABSOLUTE static GetRelativeSubPosActive(SUBPOS opponentPos, int heroDir);
	SUBPOS_ABSOLUTE static GetRelativeSubPosPassive(SUBPOS pos, int heroDir);
	SUBPOS_ABSOLUTE static RightFrom(SUBPOS_ABSOLUTE pos);
	SUBPOS_ABSOLUTE static LeftFrom(SUBPOS_ABSOLUTE pos);

private:
	SUBPOS static GetPosByIndexWhenFacingNorth(SUBPOS_ABSOLUTE SUBPOSINDEX); // only internal usage when DIR = 0!
	SUBPOS_ABSOLUTE static GetAbsPosBySubposWhenFacingNorth(SUBPOS pos); // only internal usage when DIR = 0!
	
	int static stx(int i);
	int static sty(int i);

};

