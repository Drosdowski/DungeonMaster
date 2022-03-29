#include "stdafx.h"
#include "CScreenCoords.h"

CScreenCoords::CScreenCoords() {

}

int CScreenCoords::CheckHitArrows(CPoint point) {
	if (point.x > 460)
	{
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
		}
	return 0;
}

int CScreenCoords::CheckHitActiveWizard(CPoint point, int activeWizardID) {
	if (point.x > 465)
	{
		if ((point.y > 80) && (point.y < 129)) {
			if (point.y < 95)	// Reiter
			{
				int relX = point.x - 466;
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
					return 1 + (int) min(relX / 27, 4);
				default:
					break;
				}

				return activeWizardID;
			}
			else {
				// Runes - casting!
			}
		}
	}
	return 0;
}

int CScreenCoords::CheckHitAction(CPoint point, int phase)
{
	if ((point.y > 146) && (point.y < 250))
	{
		// Klick in ActionArea - Status prüfen
		
		if (phase == 1)// 1 = Heldwahl 2 = Attackewahl 3 = Schaden
		{
			return (1 + (int)(point.x - 460) / 44);
		}
		else if (phase == 2) {
			if (point.x > 565 && point.y > 146 && point.y < 162) // pass
			{
				return -1;
			}
			else {				
				return (1 + (int)(point.y - 168) / 24);
			}

		}
	}
	return 0;
}

int CScreenCoords::CheckHitHeroes(CPoint point) {
	// TODO evtl verbesern in: Entfernung der Mitte < halbe Größe des Deco Bilds
	if (point.y < 15)
	{
		int n = int(point.x / 138) + 1;
		if ((n < 5) && ((point.x % 138) < 85))
			return n;
	}
	return 0;
}

bool CScreenCoords::CheckHitSlot(CPoint clickPoint, CPoint topLeftCorner) {
	return ((clickPoint.x >= topLeftCorner.x) &&
		(clickPoint.y >= topLeftCorner.y) &&
		(clickPoint.x <= topLeftCorner.x + 31) &&
		(clickPoint.y <= topLeftCorner.y + 31));

}

int CScreenCoords::CheckHitPortraitHands(CPoint point) {
	// 1. Hand 6/16  - 41/51
	// 2. Hand 46/16 - 81/51
	// 3. Hand 144/16 - ...
	int handId = int(point.x / 138);
	point.x = point.x % 138;
	if (CheckHitSlot(point, CPoint(8, 18))) {
		return 1 + 2 * handId;
	}
	if (CheckHitSlot(point, CPoint(48, 18))) {
		return 2 + 2 * handId;
	}
	
	return 0;
}


int CScreenCoords::CheckHitBackpackSlots(CPoint point) {
	if (CheckHitSlot(point, CPoint(12, 170))) {
		return 1; // Left Hand
	}
	else if (CheckHitSlot(point, CPoint(124, 170))) {
		return 2; // Right Hand
	}
	else if (CheckHitSlot(point, CPoint(68, 116))) {
		return 3; // Head
	}
	else if (CheckHitSlot(point, CPoint(12, 130))) {
		return 4; // Neck
	}
	else if (CheckHitSlot(point, CPoint(68, 156))) {
		return 5; // Torso
	}
	else if (CheckHitSlot(point, CPoint(68, 196))) {
		return 6; // Legs
	}
	else if (CheckHitSlot(point, CPoint(68, 236))) {
		return 7; // Feet
	}
	else if (CheckHitSlot(point, CPoint(12, 210))) {
		return 8; // Belt 1
	}
	else if (CheckHitSlot(point, CPoint(12, 244))) {
		return 9; // Belt 2
	}
	else if (CheckHitSlot(point, CPoint(124, 210))) {
		return 10; // Quiver 1
	}
	else if (CheckHitSlot(point, CPoint(158, 210))) {
		return 11; // Quiver 2
	}
	else if (CheckHitSlot(point, CPoint(124, 244))) {
		return 12; // Quiver 3
	}
	else if (CheckHitSlot(point, CPoint(158, 244))) {
		return 13; // Quiver 4
	}
	else if (CheckHitSlot(point, CPoint(132, 130))) {
		return 14; // Backpack
	}
	else {
		if (point.x >= 166 && point.y >= 96 && point.x <= 435 && point.y <= 127) {
			return (int)(15 + (point.x - 166) / 34); // Backpack 1st row
		}
		else if (point.x >= 166 && point.y >= 130 && point.x <= 435 && point.y <= 161) {
			return (int)(23 + (point.x - 166) / 34); // Backpack 2nd row
		}
	}
	return 0;
}

bool CScreenCoords::CheckHitDeco(CPoint point) {
	return (point.x > 200 && point.x < 250 && point.y > 140 && point.y < 180);
}

bool CScreenCoords::CheckHitMainScr(CPoint point) {
	return (point.y > 63) && (point.x < 460) && (point.y < 335);
}

SUBPOS CScreenCoords::CheckHitFloor(CPoint point) {
	// Hinten sind von EBENE 0 links & Rechts sichtbar
	if ((point.x < 230) && (point.y > 305)) return LINKSHINTEN;
	if ((point.x > 230) && (point.y > 305)) return RECHTSHINTEN;
	// Vorne  sind von EBENE 1 links & Rechts sichtbar
	if ((point.y > 270) && (point.x < 230) && (point.y < 305)) return LINKSVORNE;
	if ((point.y > 270) && (point.x > 230) && (point.y < 305)) return RECHTSVORNE;
	return NONE;
}

SUBPOS CScreenCoords::CheckHitAir(CPoint point) {
	if (point.y > 63 && point.y < 250) {
		if (point.x < 230) return LINKSHINTEN; // Wurf von links
		if (point.x >= 230) return RECHTSHINTEN; // Wurf von rechts
	}	
	return NONE;
}

bool CScreenCoords::CheckHitEye(CPoint point) {
	return InRect(point, 22, 88, 56, 124);
}

bool CScreenCoords::CheckHitMouth(CPoint point) {
	return InRect(point, 112, 88, 146, 124);
}