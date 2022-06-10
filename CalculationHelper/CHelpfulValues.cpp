#include "stdafx.h"
#include "CHelpfulValues.h"

CHelpfulValues::CHelpfulValues() {
	for (int i = 0; i < 4; i++)
	{
		m_stx[i] = stx(i);
		m_sty[i] = sty(i);
	}
}

int CHelpfulValues::stx(int i) {
	return int(cos(i * PI / 2)); // 0,  1, 0, -1;
}

int CHelpfulValues::sty(int i) {
	return int(sin(i * PI / 2)); // 1, 0, -1, 0;
}
COMPASS_DIRECTION CHelpfulValues::OppositeDirection(COMPASS_DIRECTION direction) {
	return (COMPASS_DIRECTION)((direction + 2) % 4);
}

VEKTOR CHelpfulValues::MakeVektor(COMPASS_DIRECTION direction, int force) {

	switch (direction) {
	case COMPASS_DIRECTION::NORTH: return VEKTOR{ 0, -force, 0 };
	case COMPASS_DIRECTION::EAST: return VEKTOR{ force, 0, 0 };
	case COMPASS_DIRECTION::SOUTH: return VEKTOR{ 0, force, 0 };
	case COMPASS_DIRECTION::WEST: return VEKTOR{ -force, 0, 0 };
	}
	return VEKTOR{ 0, 0, 0 };
}


SUBPOS_ABSOLUTE CHelpfulValues::FindNextSubposWithoutFieldChange(SUBPOS_ABSOLUTE posAbs, VEKTOR force) {
	int xV = force.x;
	int yV = force.y;
	// Annahme: nur einer ist gesetzt!
	switch (posAbs) {
	case NORTHWEST:
		if (xV > 0) return NORTHEAST;
		if (yV > 0) return SOUTHWEST;
		break;
	case NORTHEAST:
		if (xV < 0) return NORTHWEST;
		if (yV > 0) return SOUTHEAST;
		break;
	case SOUTHWEST:
		if (xV > 0) return SOUTHEAST;
		if (yV < 0) return NORTHWEST;
		break;
	case SOUTHEAST:
		if (xV < 0) return SOUTHWEST;
		if (yV < 0) return NORTHEAST;
		break;
	}
	return OUTSIDE;
}



SUBPOS_ABSOLUTE CHelpfulValues::GetAbsPosBySubposWhenFacingNorth(SUBPOS pos) {
	switch (pos) {
	case LINKSFRONT: return NORTHWEST;
	case RECHTSFRONT: return NORTHEAST;
	case RECHTSBACK: return SOUTHEAST;
	case LINKSBACK: return SOUTHWEST;
	}
	return MIDDLE;
}

SUBPOS CHelpfulValues::GetPosByIndexWhenFacingNorth(SUBPOS_ABSOLUTE pos) {
	switch (pos) {
	case NORTHWEST:
		return LINKSFRONT;
	case NORTHEAST:
		return RECHTSFRONT;
	case SOUTHEAST:
		return RECHTSBACK;
	case SOUTHWEST:
		return LINKSBACK;
	case MIDDLE:
		return MITTE;
	}
	return NONE;
}

SUBPOS_ABSOLUTE CHelpfulValues::RightFrom(SUBPOS_ABSOLUTE pos) {
	switch (pos) {
	case NORTHWEST:
		return NORTHEAST;
	case NORTHEAST:
		return SOUTHEAST;
	case SOUTHEAST:
		return SOUTHWEST;
	case SOUTHWEST:
		return NORTHWEST;
	}
	return MIDDLE;
}

SUBPOS_ABSOLUTE CHelpfulValues::LeftFrom(SUBPOS_ABSOLUTE pos) {
	switch (pos) {
	case NORTHWEST:
		return SOUTHWEST;
	case NORTHEAST:
		return NORTHWEST;
	case SOUTHEAST:
		return NORTHEAST;
	case SOUTHWEST:
		return SOUTHEAST;
	}
	return MIDDLE;
}

SUBPOS CHelpfulValues::GetRelativeSubPosPassive(SUBPOS_ABSOLUTE pos_abs, COMPASS_DIRECTION heroDir) {
	for (int turns = 0; turns < heroDir; turns++)
	{
		pos_abs = LeftFrom(pos_abs); // bei Änderungen: Prüfe items am boden vs angriff des monsters
	}
	return GetPosByIndexWhenFacingNorth(pos_abs);
}

SUBPOS CHelpfulValues::GetRelativeSubPosActive(SUBPOS_ABSOLUTE pos_abs, COMPASS_DIRECTION heroDir) {
	for (int turns = 0; turns < heroDir; turns++)
	{
		pos_abs = RightFrom(pos_abs);
	}
	return GetPosByIndexWhenFacingNorth(pos_abs);
}

SUBPOS_ABSOLUTE CHelpfulValues::GetRelativeSubPosActive(SUBPOS opponentPos, COMPASS_DIRECTION heroDir) {
	SUBPOS_ABSOLUTE pos_abs = GetAbsPosBySubposWhenFacingNorth(opponentPos);
	for (int turns = 0; turns < heroDir; turns++)
	{
		pos_abs = RightFrom(pos_abs);
	}
	return pos_abs;
}

SUBPOS_ABSOLUTE CHelpfulValues::GetRelativeSubPosPassive(SUBPOS pos, COMPASS_DIRECTION heroDir) {
	SUBPOS_ABSOLUTE pos_abs = GetAbsPosBySubposWhenFacingNorth(pos);
	for (int turns = 0; turns < heroDir; turns++)
	{
		pos_abs = LeftFrom(pos_abs);
	}
	return pos_abs;
}

CPoint CHelpfulValues::CalcRelSubFloorPosition(BITMAP bmpInfo, CPoint wallMiddlePos, SUBPOS subPos, double faktor, int xx, int ebene)
{
	int posX = wallMiddlePos.x;
	int posY = 0; // = wallMiddlePos.y;

	bool vorne = (subPos == LINKSBACK || subPos == RECHTSBACK);
	int xFaktor = (subPos == LINKSBACK || subPos == LINKSFRONT) ? -1 : 1;
	if (subPos == MITTE) xFaktor = 0;

	/*Coords - Mitte des Items
		Ebene | x   |  y	  (225 - x)
		0	  | 130 | 370		95
		1v	  | 150 | 325		75
		1h	  | 165 | 300		60
		2v	  | 177 | 280		48
		2h	  | 185 | 265		40
		3v	  | 191 | 255		34 */

	switch (ebene) {
	case 0:
		if (!vorne) {
			posX += (int)xFaktor * 95;
			posY = 370;
		}
		break;
	case 1:
		if (vorne) {
			posX += (int)xFaktor * 75;
			posY = 325;
		}
		else {
			posX += (int)xFaktor * 60;
			posY = 300;
		}
		break;
	case 2:
		if (vorne) {
			posX += (int)xFaktor * 48;
			posY = 280;
		}
		else {
			posX += (int)xFaktor * 40;
			posY = 265;
		}
		break;
	case 3:
		if (vorne) {
			posX += (int)xFaktor * 34;
			posY = 255;
		}
		else {
			posX += (int)xFaktor * 34;
			posY = 250;
		}
		break;
	}

	if (posY > 0) {
		posX -= (int)(bmpInfo.bmWidth * faktor); // entspr- halber Breite, später Faktor 2
		posY -= (int)(bmpInfo.bmHeight * faktor);
		posY -= 55;
	}

	return CPoint(posX, posY);
}

CPoint CHelpfulValues::CalcSubPosition(CPoint p, SUBPOS subPos, double &faktor) {
	int posX = p.x;
	int posY = p.y;
	if (subPos == LINKSBACK) {
		posX -= (int)(60 * faktor);
	}
	else if (subPos == RECHTSBACK) {
		posX += (int)(60 * faktor);
	}
	else if (subPos == LINKSFRONT) {
		posX -= (int)(40 * faktor);
		posY -= (int)(30 * faktor);
	}
	else if (RECHTSFRONT) {
		posX += (int)(40 * faktor);
		posY -= (int)(30 * faktor);
	}
	return CPoint(posX, posY);
}

CString CHelpfulValues::SkillGrade(int exp) {
	int e = int(exp / 500);
	if (e == 0) return "";
	else if (e == 1) return "NEOPHYTE";
	else if (e == 2) return "NOVICE";
	else if (e <= 4) return "APPRENTICE";
	else if (e <= 8) return "JOURNEYMAN";
	else if (e <= 16) return "ARTISAN";
	else if (e <= 32) return "ADEPT";
	else if (e <= 64) return "EXPERT";
	else if (e <= 128) return "MASTER 1";
	else if (e <= 256) return "MASTER 2";
	else if (e <= 512) return "MASTER 3";
	else if (e <= 1024) return "MASTER 4";
	else if (e <= 2048) return "MASTER 5";
	else if (e <= 4096) return "MASTER 6";
	else return "ARCHMASTER";
}

CString CHelpfulValues::SkillClass(int nr) {
	switch (nr) {
	case 0: return "FIGHTER";
	case 1: return "NINJA";
	case 2: return "PRIEST";
	case 3: return "WIZARD";
	}
}