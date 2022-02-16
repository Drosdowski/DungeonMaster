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

SUBPOS CHelpfulValues::GetRelativeSubPos(SUBPOS opponentPos, int heroDir) {
	// TODO
	return opponentPos;
}

SUBPOS CHelpfulValues::GetRelativeSubPos(int index, int heroDir) {
	// TODO
	return CHelpfulValues::GetRelativeSubPos(GetPosByIndex(index), heroDir);
}

SUBPOS CHelpfulValues::GetPosByIndex(int index) {
	switch (index) {
	case 1:
		return LINKSHINTEN;
	case 2:
		return RECHTSHINTEN;
	case 3:
		return LINKSVORNE;
	case 4:
		return RECHTSVORNE;
	}
	return MITTE;
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