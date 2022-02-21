#include "stdafx.h"
#include "CHelpfulValues.h"

CHelpfulValues::CHelpfulValues() {
	for (int i = 0; i < 4; i++)
	{
		m_stx[i] = int(cos(i * PI / 2));  // 0,  1, 0, -1
		m_sty[i] = int(sin(i * PI / 2));  // 1, 0, -1, 0
	}
}

int CHelpfulValues::OppositeDirection(int direction) {
	return (direction + 2) % 4;
}

SUBPOSINDEX CHelpfulValues::GetIndexBySubpos(SUBPOS pos) {
	switch (pos) {
	case LINKSHINTEN: return TOPLEFT;
	case RECHTSHINTEN: return TOPRIGHT;
	case RECHTSVORNE: return BOTTOMRIGHT;
	case LINKSVORNE: return BOTTOMLEFT;
	}
}

SUBPOS CHelpfulValues::GetPosByIndex(SUBPOSINDEX index) {
	switch (index) {
	case TOPLEFT:
		return LINKSHINTEN; 
	case TOPRIGHT:
		return RECHTSHINTEN;
	case BOTTOMRIGHT:
		return RECHTSVORNE;
	case BOTTOMLEFT:
		return LINKSVORNE;		
	}
	return NONE;
}

SUBPOSINDEX CHelpfulValues::RightFrom(SUBPOSINDEX pos) {
	switch (pos) {
	case TOPLEFT:
		return TOPRIGHT;
	case TOPRIGHT:
		return BOTTOMRIGHT;
	case BOTTOMRIGHT:
		return BOTTOMLEFT;
	case BOTTOMLEFT:
		return TOPLEFT;
	}
}

SUBPOSINDEX CHelpfulValues::LeftFrom(SUBPOSINDEX pos) {
	switch (pos) {
	case TOPLEFT:
		return BOTTOMLEFT;
	case TOPRIGHT:
		return TOPLEFT;
	case BOTTOMRIGHT:
		return TOPRIGHT;
	case BOTTOMLEFT:
		return BOTTOMRIGHT;
	}
}

SUBPOS CHelpfulValues::GetRelativeSubPosPassive(SUBPOS opponentPos, int heroDir) {
	SUBPOSINDEX index = GetIndexBySubpos(opponentPos);
	for (int turns = 0; turns < heroDir; turns++)
	{
		index = LeftFrom(index);
	}
	return GetPosByIndex(index);
}

SUBPOS CHelpfulValues::GetRelativeSubPosPassive(SUBPOSINDEX index, int heroDir) {
	return GetRelativeSubPosPassive(GetPosByIndex(index), heroDir);
}

SUBPOS CHelpfulValues::GetRelativeSubPosActive(SUBPOS opponentPos, int heroDir) {
	SUBPOSINDEX index = GetIndexBySubpos(opponentPos);
	for (int turns = 0; turns < heroDir; turns++)
	{
		index = RightFrom(index);
	}
	return GetPosByIndex(index);
}

SUBPOS CHelpfulValues::GetRelativeSubPosActive(SUBPOSINDEX index, int heroDir) {
	return GetRelativeSubPosActive(GetPosByIndex(index), heroDir);
}


CPoint CHelpfulValues::CalcRelSubPosition(BITMAP bmpInfo, CPoint wallMiddlePos, SUBPOS subPos, double faktor, int xx) 
{
	int posX = wallMiddlePos.x;
	int posY = wallMiddlePos.y;

	if (subPos == LINKSVORNE) {
		posX -= (int)(90 * faktor);
		posY += (int)(25 * faktor);
	}
	else if (subPos == RECHTSVORNE) {
		posX += (int)(90 * faktor);
		posY += (int)(25 * faktor);
	}
	else if (subPos == LINKSHINTEN) {
		posX -= (int)(75 * faktor);
		posY -= (int)(15 * faktor);
	}
	else if (RECHTSHINTEN) {
		posX += (int)(75 * faktor);
		posY -= (int)(15 * faktor);
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