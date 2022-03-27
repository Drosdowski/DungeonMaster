#include "stdafx.h"
#include "..\CHelpfulValues.h"
#include "..\Pictures\CPictures.h"
#include "..\Mobs\Held.h"
#include "..\Mobs\MobGroups\GrpHeld.h"
#include "CGroupView.h"

CGroupView::CGroupView()
{
}

CGroupView::~CGroupView()
{
}

void CGroupView::Zeichnen(CDC* pDC, CPictures* pPictures, int iModus, CGrpHeld* pGrpHeld)
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
					pPictures->HaendeZeichnen(pDC, i, pHeroToDraw);
					pPictures->WerteZeichnen(pDC, pHeroToDraw);
					pPictures->NameZeichnen(pDC, pHeroToDraw->isActive(), i, pHeroToDraw->getName());
					break;
				}
				case (MOD_RUCKSACK):
				{
					if (pHeroToDraw == pGrpHeld->GetActiveHero())
					{
						pPictures->BildZeichnen(pDC, pHeroToDraw->isActive(), i);
						pPictures->RucksackZeichnen(pDC, pHeroToDraw);
					}
					break;
				}
				}
				pPictures->WaffeZeichnen(pDC);
				SUBPOS relPos = CHelpfulValues::GetRelativeSubPosActive(pHeroToDraw->HoleSubPosition(), pGrpHeld->GetDirection());
				pPictures->SymbolZeichnen(pDC, i, relPos);
				if (pHeroToDraw->ReceivedDmg() > 0) {
					pPictures->SchadenZeichnen(pDC, i);
					pHeroToDraw->ResetDmg();
				}
			}
		}
	}
}