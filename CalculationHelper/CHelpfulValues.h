#pragma once
class CHelpfulValues
{
public:
#define PI 3.1415926536

	CHelpfulValues();

	int m_stx[4];
	int m_sty[4];

	COMPASS_DIRECTION static OppositeDirection(COMPASS_DIRECTION direction);

	static SUBPOS_ABSOLUTE FindNextSubposWithoutFieldChange(SUBPOS_ABSOLUTE posAbs, VEKTOR force);

	VEKTOR static MakeVektor(COMPASS_DIRECTION direction, int force);
	bool static VectorEqual(VEKTOR a, VEKTOR b) { return a.x == b.x && a.y == b.y && a.z == b.z; }
	CPoint static CalcSubPosition(CPoint p, SUBPOS subPos, double faktor); // for monsters - todo weg damit!
	CPoint static CalcRelSubFloorPosition(BITMAP bmpInfo, CPoint wallPos, SUBPOS subPos, double faktor, int xx, int ebene); // for items 
	SUBPOS static GetRelativeSubPosActive(SUBPOS_ABSOLUTE pos, COMPASS_DIRECTION heroDir);
	SUBPOS static GetRelativeSubPosPassive(SUBPOS_ABSOLUTE pos, COMPASS_DIRECTION heroDir);

	SUBPOS_ABSOLUTE static GetRelativeSubPosActive(SUBPOS opponentPos, COMPASS_DIRECTION heroDir);
	SUBPOS_ABSOLUTE static GetRelativeSubPosPassive(SUBPOS pos, COMPASS_DIRECTION heroDir);
	SUBPOS_ABSOLUTE static GetFirstPositionFromDirection(COMPASS_DIRECTION heroDir);
	SUBPOS_ABSOLUTE static GetSecondPositionFromDirection(COMPASS_DIRECTION heroDir);
	SUBPOS_ABSOLUTE static RightFrom(SUBPOS_ABSOLUTE pos);
	SUBPOS_ABSOLUTE static LeftFrom(SUBPOS_ABSOLUTE pos);
	VEKTOR static GetNextFieldKoord(int toDirection, int viewDirection, int range, VEKTOR sourcePos);

	bool static westOf(VEKTOR myPos, VEKTOR hisPos);
	bool static eastOf(VEKTOR myPos, VEKTOR hisPos);
	bool static northOf(VEKTOR myPos, VEKTOR hisPos);
	bool static southOf(VEKTOR myPos, VEKTOR hisPos);

	CString static SkillGrade(int exp);
	CString static SkillClass(int nr);
	CString static VitalName(int nr);
	int static ManaCost(int layer, int runeId, int power);
	FlyingVektor static GetRelativeVector(COMPASS_DIRECTION heroDir, VEKTOR itemVektor);
	double static getDistanceFactor(int iEntfernung);

	double static round1(double value);
	//VEKTOR static originFront(int width, int height, boolean bottom, int x, int ebene);
	//VEKTOR static originSide(int width, int height, boolean bottom, int x, int ebene);

private:
	SUBPOS static GetPosByIndexWhenFacingNorth(SUBPOS_ABSOLUTE SUBPOSINDEX); // only internal usage when DIR = 0!
	SUBPOS_ABSOLUTE static GetAbsPosBySubposWhenFacingNorth(SUBPOS pos); // only internal usage when DIR = 0!
	
	int static stx(int i);
	int static sty(int i);

};

