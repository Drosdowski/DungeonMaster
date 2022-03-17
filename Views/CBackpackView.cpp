#include "stdafx.h"
#include "..\Pictures\CPictures.h"
#include "..\Mobs\MobGroups\GrpHeld.h"
#include "..\Mobs\Held.h"
#include "CBackpackView.h"

CBackpackView::CBackpackView()
{
}

CBackpackView::~CBackpackView()
{
}

void CBackpackView::UpdateRucksack(CDC* pDC, CPictures* pPictures, CGrpHeld* grpHero)
{
	for (int i = 1; i < 5; i++)
	{
		CHeld* pActiveHero = grpHero->GetActiveHero();
		CHeld* pHeroToDraw = grpHero->GetHero(i);
		if (pHeroToDraw)
			if (pHeroToDraw->Hp().Aktuell > 0)
			{
				if (pActiveHero == pHeroToDraw)
				{
					pPictures->BildZeichnen(pDC, true, i);
					pPictures->RucksackZeichnen(pDC, pActiveHero);
				}
				else {
					pPictures->HaendeZeichnen(pDC, i);
				}
				pPictures->WerteZeichnen(pDC, pHeroToDraw);
			}
			else
				pPictures->KnochenZeichnen(pDC, i);
	}
}