#include "stdafx.h"
#include "CHelpfulValues.h"
#include <cassert>

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

	if (xV == 0 && yV == 0) return posAbs;

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

bool CHelpfulValues::westOf(VEKTOR myPos, VEKTOR hisPos) {
	return (myPos.y == myPos.y) && ((myPos.x - hisPos.x) >= 1);
}

bool CHelpfulValues::eastOf(VEKTOR myPos, VEKTOR hisPos) {
	return (myPos.y == myPos.y) && ((hisPos.x - myPos.x) >= 1);
}

// his is north of my
bool CHelpfulValues::northOf(VEKTOR myPos, VEKTOR hisPos) {
	return (myPos.x == hisPos.x) && ((myPos.y - hisPos.y) >= 1);
}

bool CHelpfulValues::southOf(VEKTOR myPos, VEKTOR hisPos) {
	return (myPos.x == hisPos.x) && ((hisPos.y - myPos.y) >= 1);
}

FlyingVektor CHelpfulValues::GetRelativeVector(COMPASS_DIRECTION heroDir, VEKTOR itemVektor) {
	switch (heroDir)
	{
	case NORTH:
		if (itemVektor.x != 0) return Side;
		if (itemVektor.y < 0) return Backside;
		return Frontside;
		break;
	case EAST:
		if (itemVektor.y != 0) return Side;
		if (itemVektor.x > 0) return Backside;
		return Frontside;
		break;
	case SOUTH:
		if (itemVektor.x != 0) return Side;
		if (itemVektor.y > 0) return Backside;
		return Frontside;
		break;
	case WEST:
		if (itemVektor.y != 0) return Side;
		if (itemVektor.x < 0) return Backside;
		return Frontside;
		break;
	case STOP:
		break;
	default:
		break;
	}
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

SUBPOS_ABSOLUTE CHelpfulValues::GetFirstPositionFromDirection(COMPASS_DIRECTION heroDir) {
	if (heroDir == EAST) return SOUTHEAST;
	if (heroDir == SOUTH) return SOUTHWEST;
	if (heroDir == WEST) return NORTHWEST;
	if (heroDir == NORTH) return NORTHEAST;
}
SUBPOS_ABSOLUTE CHelpfulValues::GetSecondPositionFromDirection(COMPASS_DIRECTION heroDir) {
	if (heroDir == EAST) return NORTHEAST;
	if (heroDir == SOUTH) return SOUTHEAST;
	if (heroDir == WEST) return SOUTHWEST;
	if (heroDir == NORTH) return NORTHWEST;
}

VEKTOR CHelpfulValues::GetNextFieldKoord(int toDirection, int viewDirection, int range, VEKTOR sourcePos)
{
	CHelpfulValues* HV = new CHelpfulValues();
	int sx = HV->m_stx[viewDirection] * range;
	int sy = HV->m_sty[viewDirection] * range;
	VEKTOR targetPos = sourcePos;
	switch (toDirection)
	{
	case LINKS_STRAFE:
		targetPos.x = sourcePos.x - sx;
		targetPos.y = sourcePos.y - sy;
		break;
	case RUECKWAERTS:
		targetPos.x = sourcePos.x - sy;
		targetPos.y = sourcePos.y + sx;
		break;
	case RECHTS_STRAFE:
		targetPos.x = sourcePos.x + sx;
		targetPos.y = sourcePos.y + sy;
		break;
	case VORWAERTS:
		targetPos.x = sourcePos.x + sy;
		targetPos.y = sourcePos.y - sx;
		break;
	default:
		break;
	}
	delete HV;
	return targetPos;
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
		0	  | 130 | 365		95
		1v	  | 150 | 325		75
		1h	  | 165 | 310		60
		2v	  | 177 | 285		48
		2h	  | 185 | 275		40
		3v	  | 191 | 255		34 
		3h	  | 191 | 250		34 */

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
			posY = 360;
		}
		else {
			posX += (int)xFaktor * 60;
			if (subPos == MITTE) {
				posY = 290;
			}
			else {
				posY = 310;
			}
		}
		break;
	case 2:
		if (vorne) {
			posX += (int)xFaktor * 48;
			posY = 285;
		}
		else {
			posX += (int)xFaktor * 40;
			if (subPos == MITTE) {
				posX += (int)(faktor * 75 * xx);
				posY = 268;
			}
			else {
				posY = 275;
			}
		}
		break;
	case 3:
		if (vorne) {
			posX += (int)xFaktor * 34;
			posY = 255;
		}
		else {
			posX += (int)xFaktor * 30;
			if (subPos == MITTE) {
				posX += (int)(faktor * 60 * xx);
				posY = 244;
			}
			else {
				posY = 255;
			}
		}
		break;
	}

	if (posY > 0) {
		posX -= (int)(bmpInfo.bmWidth * faktor); // entspr- halber Breite, später Faktor 2
		posY -= (int)(bmpInfo.bmHeight * faktor * 2);
		posY -= 55;
	}

	return CPoint(posX, posY);
}

CPoint CHelpfulValues::CalcSubPosition(CPoint p, SUBPOS subPos, double faktor) {
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
	else if (subPos == RECHTSFRONT) {
		posX += (int)(40 * faktor);
		posY -= (int)(30 * faktor);
	}
	return CPoint(posX, posY);
}

CString CHelpfulValues::SkillGrade(int exp) {
	int e = int(exp / 500);
	if (e == 0) return "XP TODO";
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
	return "UNK";
}

CString CHelpfulValues::VitalName(int nr) {
	switch (nr) {
	case 0: return "STRENGTH";
	case 1: return "DEXTERITY";
	case 2: return "WISDOM";
	case 3: return "VITALITY";
	case 4: return "ANTI-MAGIC";
	case 5: return "ANTI-FIRE";
	}
	return "UNK";
}


int CHelpfulValues::ManaCost(int layer, int runeId, int power) {
	switch (layer) {
		case 1: return runeId;
		case 2: {
			switch (runeId) {
			case 1: return power + 1;
			case 2: return 3 + (int)((power - 1) * 1.5);
			case 3: return 2 + 2 * power;
			case 4: return 5 + (int)((power - 1) * 2.5);
			case 5: return 3 + 3 * power;
			case 6: return 7 + (int)((power - 1) * 3.5);
			}
		case 3:
			switch (runeId) {
			case 1: return 2 + 2 * power;
			case 2: return 5 + (int)((power - 1) * 2.5);
			case 3: return 3 + 3 * power;
			case 4: return 7 + (int)((power - 1) * 3.5);
			case 5: return 7 + (int)((power - 1) * 3.5); // really
			case 6: return 9 + (int)((power - 1) * 4.5);
			}
		case 4:
			switch (runeId) {
			case 1: return power + 1;
			case 2: return power + 1;
			case 3: return 3 + (int)((power - 1) * 1.5);
			case 4: return 2 + 2 * power;
			case 5: return 3 + 3 * power;
			case 6: return 7 + (int)((power - 1) * 3.5);
			}
		}
	}
	return 0;
}


double CHelpfulValues::round1(double value) {
	return floor(value * 10.0 + .5) / 10.0;
}


double CHelpfulValues::getDistanceFactor(int iEntfernung) {
	if (iEntfernung == 0) return 1;
	if (iEntfernung == 1) return 1;
	if (iEntfernung == 2) return 0.75;
	if (iEntfernung == 3) return 0.5;
	if (iEntfernung == 4) return 0.4;
	assert(false);
	return 1; // todo 1 !
}

