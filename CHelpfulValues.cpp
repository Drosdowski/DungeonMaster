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
int CHelpfulValues::OppositeDirection(int direction) {
	return (direction + 2) % 4;
}

VEKTOR CHelpfulValues::MakeVektor(int direction, int force) {

	switch (direction) {
	case 0: return VEKTOR{ 0, -force, 0 };
	case 1: return VEKTOR{ force, 0, 0 };
	case 2: return VEKTOR{ 0, force, 0 };
	case 3: return VEKTOR{ -force, 0, 0 };
	}
	return VEKTOR {0, 0, 0};
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
	return MIDDLE;
}



SUBPOS_ABSOLUTE CHelpfulValues::GetAbsPosBySubposWhenFacingNorth(SUBPOS pos) {
	switch (pos) {
	case LINKSHINTEN: return NORTHWEST;
	case RECHTSHINTEN: return NORTHEAST;
	case RECHTSVORNE: return SOUTHEAST;
	case LINKSVORNE: return SOUTHWEST;
	}
	return MIDDLE;
}

SUBPOS CHelpfulValues::GetPosByIndexWhenFacingNorth(SUBPOS_ABSOLUTE pos) {
	switch (pos) {
	case NORTHWEST:
		return LINKSHINTEN; 
	case NORTHEAST:
		return RECHTSHINTEN;
	case SOUTHEAST:
		return RECHTSVORNE;
	case SOUTHWEST:
		return LINKSVORNE;		
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

SUBPOS CHelpfulValues::GetRelativeSubPosPassive(SUBPOS_ABSOLUTE pos_abs, int heroDir) {
	for (int turns = 0; turns < heroDir; turns++)
	{
		pos_abs = LeftFrom(pos_abs);
	}
	return GetPosByIndexWhenFacingNorth(pos_abs);
}

SUBPOS_ABSOLUTE CHelpfulValues::GetRelativeSubPosActive(SUBPOS opponentPos, int heroDir) {
	SUBPOS_ABSOLUTE pos_abs = GetAbsPosBySubposWhenFacingNorth(opponentPos);
	for (int turns = 0; turns < heroDir; turns++)
	{
		pos_abs = RightFrom(pos_abs);
	}
	return pos_abs;
}

SUBPOS_ABSOLUTE CHelpfulValues::GetRelativeSubPosPassive(SUBPOS pos, int heroDir) {
	SUBPOS_ABSOLUTE pos_abs = GetAbsPosBySubposWhenFacingNorth(pos);
	for (int turns = 0; turns < heroDir; turns++)
	{
		pos_abs = LeftFrom(pos_abs);
	}
	return pos_abs;
}

SUBPOS CHelpfulValues::GetRelativeSubPosActive(SUBPOS_ABSOLUTE pos_abs, int heroDir) {
	for (int turns = 0; turns < heroDir; turns++)
	{
		pos_abs = RightFrom(pos_abs);
	}
	return GetPosByIndexWhenFacingNorth(pos_abs);
}


CPoint CHelpfulValues::CalcRelSubFloorPosition(BITMAP bmpInfo, CPoint wallMiddlePos, SUBPOS subPos, double faktor, int xx, int ebene)
{
	int posX = wallMiddlePos.x;
	int posY = 0; // = wallMiddlePos.y;

	bool vorne = (subPos == LINKSVORNE || subPos == RECHTSVORNE);
	int xFaktor = (subPos == LINKSVORNE || subPos == LINKSHINTEN) ? -1 : 1;

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

CPoint CHelpfulValues::CalcSubPosition(BITMAP bmpInfo, SUBPOS subPos, double faktor, int xx) {
	int posX = 225 - (int)(bmpInfo.bmWidth * faktor - (xx * 156));
	int posY = 90 + (int)(bmpInfo.bmHeight * (1 - faktor) / 2);
	//int posY = (int)(260 - bmpInfo.bmHeight * 2 - (1 - faktor) * 40); // TODO !!!!!!!!!!!
	//int posY = (int)(260 - bmpInfo.bmHeight*2 ); 

	if (subPos == LINKSVORNE) {
		posX -= (int)(60 * faktor);
		posY += (int)(50 * faktor);
	}
	else if (subPos == RECHTSVORNE) {
		posX += (int)(60 * faktor);
		posY += (int)(50 * faktor);
	}
	else if (subPos == LINKSHINTEN) {
		posX -= (int)(40 * faktor);
	}
	else if (RECHTSHINTEN) {
		posX += (int)(40 * faktor);
	}
	return CPoint(posX, posY);
}