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

CPoint CHelpfulValues::CalcSubPosition(BITMAP bmpInfo, SUBPOS subPos, double faktor, int xx) {
	int posX = 225 - (int)(bmpInfo.bmWidth * faktor - (xx * 156));
	int posY = 90 + (int)(bmpInfo.bmHeight * (1 - faktor) / 2);

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