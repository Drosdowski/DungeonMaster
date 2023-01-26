#include "stdafx.h"
#include "CScreenCoords.h"
#include <CalculationHelper/ZoomBlt.h>

CScreenCoords::CScreenCoords() {
}

CPoint CScreenCoords::GetbackPackSlotKoords(int index)
{
	switch (index) {

	case 0: return CPoint(12, 170);// Left Hand
	case 1: return CPoint(124, 170);// Right Hand
	case 2: return CPoint(68, 116);// Head
	case 3: return CPoint(12, 130);// Neck
	case 4: return CPoint(68, 156);// Torso
	case 5: return CPoint(68, 196);// Legs
	case 6: return CPoint(68, 236);// Feet
	case 7: return CPoint(12, 210);// Belt 1
	case 8: return CPoint(12, 244);// Belt 2
	case 9: return CPoint(124, 210);// Quiver 1
	case 10: return CPoint(158, 210);// Quiver 2
	case 11: return CPoint(124, 244);// Quiver 3
	case 12: return CPoint(158, 244);// Quiver 4
	case 13: return CPoint(132, 130);// Backpack
	default:
		if (index > 13 && index < 22)
			return CPoint(166 + 34 * (index - 14), 96);// Backpack 1st row
		else if (index > 21 && index < 30)
			return CPoint(166 + 34 * (index - 22), 130);// Backpack 2nd row		
		else
			return CPoint(0, 0);
	}
}

int CScreenCoords::CheckHitArrows(CPoint point) {
	if (InRect(point, 526, 248, 580, 290))
		return VORWAERTS;
	else if (InRect(point, 526, 292, 580, 334))
		return RUECKWAERTS;
	else if (InRect(point, 468, 292, 524, 334))
		return LINKS_STRAFE;
	else if (InRect(point, 582, 292, 638, 334))
		return RECHTS_STRAFE;
	else if (InRect(point, 468, 248, 524, 290))
		return LINKS_DREHEN;
	else if (InRect(point, 582, 248, 638, 290))
		return RECHTS_DREHEN;
return 0;
}

int CScreenCoords::CheckHitRunes(CPoint point) {
	if (InRect(point, 465, 94, 640, 129))
	{
		// 640 - 466 = 174.   174 / 6 = 28
		for (int runeId = 1; runeId < 7; runeId++) {
			int dx = (28 * (runeId - 1));
			if (InRect(point, 466 + dx, 94, 494 + dx, 129)) return runeId;
		}
		//int runeId = (int)((point.x - 466) / 28) + 1;
		//return runeId;
	}
	return 0;
}

bool CScreenCoords::CheckHitSpell(CPoint point) {
	return (InRect(point, 465, 128, 640, 153));
}


int CScreenCoords::CheckHitActiveWizard(CPoint point, int activeWizardID) {
	if (InRect(point, 465, 80, 640, 95))
	{
		int fx = CZoomBlt::fx() / 2;
		int relX = (point.x / fx) - 466;
		switch (activeWizardID)
		{
		case 1:
			if (relX < 96) return 1;
			return 1 + (int)(relX - 96 + 27) / 27;
		case 2:
			if (relX < 28) return 1;
			return 1 + (int)(relX - 96 + 27) / 27;
		case 3:
			if (relX < 55) return 1 + (int)relX / 27;
			if (relX > 148) return 4; else return 3;
		case 4:
			return 1 + (int)min(relX / 27, 4);
		default:
			break;
		}

		return activeWizardID;
	}
	return 0;
}

int CScreenCoords::CheckHitAction(CPoint point, int phase)
{
	//if ((point.y > 146) && (point.y < 250))
	if (InRect(point, 460, 146, 640, 250))
	{
		// Klick in ActionArea - Status prüfen

		if (phase == 1)// 1 = Heldwahl 2 = Attackewahl 3 = Schaden
		{
			for (int i=0; i<4; i++)
				if (InRect(point, 460 + i*44, 146, 504 + i * 44, 250)) return (i+1);
		}
		else if (phase == 2) {
			// if (point.x > 565 && point.y > 146 && point.y < 162) 
			if (InRect(point, 565,146,640,162))
			{
				return -1; // pass
			}
			else {			
				for (int i = 0; i < 4; i++)
					if (InRect(point, 460, 168 + i * 24, 640, 192 + i * 24)) return (i + 1);

				//return (1 + (int)(point.y - 168) / 24);
			}

		}
	}
	return 0;
}

int CScreenCoords::CheckHitHeroes(CPoint point) {
	if (InRect(point, 0, 0, 138, 15)) return 1;
	if (InRect(point, 138, 0, 138*2, 15)) return 2;
	if (InRect(point, 138*2, 0, 138*3, 15)) return 3;
	if (InRect(point, 138*3, 0, 138*4, 15)) return 4;
	return 0;
}

bool CScreenCoords::CheckHitSlot(CPoint clickPoint, CPoint topLeftCorner) {
	return (InRect(clickPoint, topLeftCorner.x, topLeftCorner.y, topLeftCorner.x + 31, topLeftCorner.y + 31));
}

int CScreenCoords::CheckHitPortraitHands(CPoint point) {
	// 1. Hand 6/16  - 41/51
	// 2. Hand 46/16 - 81/51
	// 3. Hand 144/16 - ...
	for (int i = 0; i < 4; i++)
	{
		if (CheckHitSlot(point, CPoint(8 + 138*i, 18))) {
			return 1 + 2 * i;
		}
		if (CheckHitSlot(point, CPoint(48 + 138 * i, 18))) {
			return 2 + 2 * i;
		}
	}

	return 0;
}


int CScreenCoords::CheckHitBackpackSlots(CPoint point) {
	for (int i = 0; i < 30; i++)
		if (CheckHitSlot(point, GetbackPackSlotKoords(i))) {
			return i;
		}
	return -1;
}

bool CScreenCoords::CheckHitDeco(CPoint point, CSize size) {
	if (size == CSize(0, 0))
		return (InRect(point, 200, 140, 250, 180));
	else
	{
		int wx = size.cx; // halbe Breite, /2*2 = 1.
		int wy = size.cy * 2;
		return (InRect(point, 225 - wx, 140, 225 + wx, 140 + wy));
	}
}

bool CScreenCoords::CheckHitDoorButton(CPoint point) {
	return InRect(point, 64 + 128 * 2, 82 + 34 * 2, 64 + 32 + 128 * 2, 82 + 18 + 34 * 2);
	//return (point.x >= 64 + 128 * 2 && point.y >= 82 + 34 * 2 &&
		//point.x <= 64 + 32 + 128 * 2 && point.y <= 82 + 18 + 34 * 2);
}


bool CScreenCoords::CheckHitMainScr(CPoint point) {
	return InRect(point, 0, 64, 460, 336);
	//return (point.y > 63) && (point.x < 460) && (point.y < 335);
}

SUBPOS CScreenCoords::CheckHitFloor(CPoint point) {
	// Hinten sind von EBENE 0 links & Rechts greifbar
	if (InRect(point, 0, 305, 230, 400)) return LINKSFRONT;
	if (InRect(point, 230, 305, 460, 400)) return RECHTSFRONT;

	//if ((point.x < 230) && (point.y > 305)) return LINKSFRONT;
	//if ((point.x > 230) && (point.y > 305)) return RECHTSFRONT;
	// Vorne  sind von EBENE 1 links & Rechts greifbar
	if (InRect(point, 0, 270, 230, 305)) return LINKSBACK;
	if (InRect(point, 230, 270, 460, 305)) return RECHTSBACK;
	return NONE;
}

SUBPOS CScreenCoords::CheckHitAir(CPoint point) {
	if (InRect(point, 0, 63, 230, 250)) return LINKSFRONT; // Wurf von links
	if (InRect(point, 230, 63, 460, 250)) return RECHTSFRONT; // Wurf von rechts

	return NONE;
}

bool CScreenCoords::CheckHitEye(CPoint point) {
	return InRect(point, 22, 88, 56, 124);
}

bool CScreenCoords::CheckHitMouth(CPoint point) {
	return InRect(point, 112, 88, 146, 124);
}

bool CScreenCoords::CheckHitSleep(CPoint point) {
	return InRect(point, 376, 70, 408, 86);
}

bool CScreenCoords::CheckHitSave(CPoint point) {
	return InRect(point, 348, 70, 366, 86);
}