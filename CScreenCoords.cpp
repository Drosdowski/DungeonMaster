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
}

int CScreenCoords::CheckHitActiveWizard(CPoint point, int activeWizardID) {
	if (point.x > 460)
	{
		if ((point.y > 63) && (point.y < 129)) {
			int nr;
			if (point.y < 72)	// Reiter
			{
				nr = point.x / 28;
				if (nr > (activeWizardID + 1))
					nr -= 3;

				return nr;
			}
		}
	}
	return 0;
}

int CScreenCoords::CheckHitAction(CPoint point, int phase)
{
	if ((point.y > 146) && (point.y < 290))
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

bool CScreenCoords::CheckHitDeco(CPoint point) {
	return (point.x > 200 && point.x < 250 && point.y > 140 && point.y < 180);
}

bool CScreenCoords::CheckHitMainScr(CPoint point) {
	return (point.y > 63) && (point.x < 460) && (point.y < 335);
}