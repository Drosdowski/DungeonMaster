#include "stdafx.h"
#include "..\CalculationHelper\CHelpfulValues.h"
#include "..\Pictures\CPictures.h"
#include "..\Mobs\Held.h"
#include "..\Mobs\MobGroups\GrpHeld.h"
#include "DMView.h"
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
			if (pHeroToDraw->Hp().Aktuell <= 0)
				pPictures->KnochenZeichnen(pDC, i);
			else
			{
				switch (iModus)
				{
				case (MOD_LAUFEN):
				{
					pPictures->WerteZeichnen(pDC, pHeroToDraw);
					pPictures->NameZeichnen(pDC, pHeroToDraw->isActive(), i, pHeroToDraw->getName());
					pPictures->HaendeZeichnen(pDC, pHeroToDraw);
					break;
				}
				case (MOD_RUCKSACK):
				{
					pPictures->WerteZeichnen(pDC, pHeroToDraw);
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
				if (pHeroToDraw->ReceivedDmg() > 0) {
					pPictures->SchadenZeichnen(pDC, i, pHeroToDraw->isActive() && (iModus == MOD_RUCKSACK), pHeroToDraw->ReceivedDmg());
					pHeroToDraw->ResetDmg();
				}
			}
		}
	}
}