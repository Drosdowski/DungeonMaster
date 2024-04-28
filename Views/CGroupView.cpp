#include "stdafx.h"
#include "..\CalculationHelper\CHelpfulValues.h"
#include "..\Pictures\CPictures.h"
#include "..\Mobs\MobGroups\GrpHeld.h"
#include "CGroupView.h"

CGroupView::CGroupView()
{
}

CGroupView::~CGroupView()
{
}

void CGroupView::GroupZeichnen(CDC* pDC, CPictures* pPictures, DMMode iModus, CGrpHeld* pGrpHeld)
{
	for (int i = 1; i <= 4; i++)
	{
		CHeld* pHeroToDraw = pGrpHeld->GetHero(i);

		if (pHeroToDraw != NULL)
		{
			if (!pHeroToDraw->isAlive())
				pPictures->KnochenZeichnen(pDC, i);
			else
			{
				pPictures->WerteZeichnen(pDC, pHeroToDraw);
				GroupMode gMode = pGrpHeld->GetModus();
				switch (gMode)
				{
				case (DEFAULT):
				case (ASLEEP):
				{
					pPictures->NameZeichnen(pDC, pHeroToDraw->isActive(), i, pHeroToDraw->getName());
					pPictures->HaendeZeichnen(pDC, pHeroToDraw);
					break;
				}
				case (BACKPACK):
				{
					if (pHeroToDraw == pGrpHeld->GetActiveHero())
					{
						pPictures->BildZeichnen(pDC, pHeroToDraw->isActive(), i);
					}
					else {
						pPictures->HaendeZeichnen(pDC, pHeroToDraw);
						pPictures->NameZeichnen(pDC, pHeroToDraw->isActive(), i, pHeroToDraw->getName());
					}
					break;
				}
				}
				pPictures->WaffeZeichnen(pDC);
				SUBPOS relPos = CHelpfulValues::GetRelativeSubPosPassive(pHeroToDraw->HoleSubPosition(), pGrpHeld->GetDirection());
				pPictures->SymbolZeichnen(pDC, i, relPos);
				int allDamage = pHeroToDraw->ReceivedDmg() + pHeroToDraw->ReceivedPoison();
				if (allDamage > 0) {
					pPictures->SchadenZeichnen(pDC, i, pHeroToDraw->isActive() && (pGrpHeld->GetModus() == BACKPACK), allDamage);
					//pHeroToDraw->ResetDmg();
				}
			}
		}
	}
}