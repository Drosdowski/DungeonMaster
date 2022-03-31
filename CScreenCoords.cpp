#include "stdafx.h"
#include "CScreenCoords.h"

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
		if (index >13 && index < 22)		
			return CPoint(166 + 34 * (index-14), 96);// Backpack 1st row
		else if (index > 21 && index < 30)
			return CPoint(166 + 34 * (index-22), 130);// Backpack 2nd row		
	}
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
	for (int i = 0; i< 30; i++)
		if (CheckHitSlot(point, GetbackPackSlotKoords(i))) {
			return i; 
		}	
	return -1;
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