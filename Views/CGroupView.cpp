#include "stdafx.h"
#include "..\CalculationHelper\CHelpfulValues.h"
#include "..\Pictures\CPictures.h"
#include "..\Mobs\MobGroups\GrpHeld.h"
#include "..\Mobs\Held.h"
#include "CGroupView.h"

CGroupView::CGroupView(CPictures* pPictures)
{
	m_pPictures = pPictures;
	m_textBuffer = new char[10];
}

CGroupView::~CGroupView()
{
	delete m_textBuffer;
}

void CGroupView::GroupZeichnen(CDC* pDC, DMMode iModus, CGrpHeld* pGrpHeld)
{
	m_pDC = pDC;
	for (int i = 1; i <= 4; i++)
	{
		CHeld* pHeroToDraw = pGrpHeld->GetHero(i);

		if (pHeroToDraw != NULL)
		{
			if (!pHeroToDraw->isAlive())
				KnochenZeichnen(i);
			else
			{
				WerteZeichnen(pHeroToDraw);
				GroupMode gMode = pGrpHeld->GetModus();
				switch (gMode)
				{
				case (DEFAULT):
				case (ASLEEP):
				{
					NameZeichnen(pHeroToDraw->isActive(), i, pHeroToDraw->getName());
					HaendeZeichnen(pHeroToDraw);
					break;
				}
				case (BACKPACK):
				{
					if (pHeroToDraw == pGrpHeld->GetActiveHero())
					{
						BildZeichnen(pHeroToDraw->isActive(), i);
					}
					else {
						HaendeZeichnen(pHeroToDraw);
						NameZeichnen(pHeroToDraw->isActive(), i, pHeroToDraw->getName());
					}
					break;
				}
				}
				SUBPOS relPos = CHelpfulValues::GetRelativeSubPosPassive(pHeroToDraw->HoleSubPosition(), pGrpHeld->GetDirection());
				m_pPictures->SymbolZeichnen(pDC, i, relPos);
				int allDamage = pHeroToDraw->ReceivedDmg() + pHeroToDraw->ReceivedPoison();
				if (allDamage > 0) {
					SchadenZeichnen(i, pHeroToDraw->isActive() && (pGrpHeld->GetModus() == BACKPACK), allDamage);
					//pHeroToDraw->ResetDmg();
				}
			}
		}
	}

	
}

void CGroupView::KnochenZeichnen(int index)
{
	CDC tmpdc;
	tmpdc.CreateCompatibleDC(m_pDC);
	tmpdc.SelectObject(m_pPictures->GetInterface(1));
	m_pDC->StretchBlt((index - 1) * 138, 0, 138, 56, &tmpdc, 0, 0, 80, 29, SRCCOPY);

	tmpdc.DeleteDC();
}

void CGroupView::WerteZeichnen(CHeld* pHeld)
{
	int index = pHeld->getIndex();

	CDC tmpdc;
	tmpdc.CreateCompatibleDC(m_pDC);
	tmpdc.SelectObject(m_pPictures->GetInterface(0));
	m_pDC->StretchBlt((index - 1) * 138, 0, 138, 56, &tmpdc, 0, 0, 80, 29, SRCCOPY);

	// Hp, St, Ma - Balken
	int x = (pHeld->getIndex() - 1) * 138 + 94;

	m_pDC->FillSolidRect(CRect(x, 52 - int(48 * pHeld->LifePart()), x + 7, 52), pHeld->Farbe());
	if (pHeld->StaminaPart() > 0)
	{
		m_pDC->FillSolidRect(CRect(x + 14, 52 - int(48 * pHeld->StaminaPart()), x + 21, 52), pHeld->Farbe());
	}
	if (pHeld->ManaPart() > 0)
	{
		m_pDC->FillSolidRect(CRect(x + 28, 52 - int(48 * pHeld->ManaPart()), x + 35, 52), pHeld->Farbe());
	}

	tmpdc.DeleteDC();
}

void CGroupView::NameZeichnen(bool aktiv, int index, CString strName)
{
	if (aktiv)
		m_pDC->SetTextColor(GELB);
	else
		m_pDC->SetTextColor(HELLBRAUN);
	m_pDC->SetBkColor(DUNKELGRAU);
	int x = (index - 1) * 138;
	//pDC->ExtTextOut(x + 4, -2, ETO_CLIPPED | ETO_OPAQUE, CRect(x, 0, x + 78, 14), strName, NULL);
	m_pPictures->DrawFontText(m_pDC, x, -2, strName, false);
}

void CGroupView::HaendeZeichnen(CHeld* pHeld)
{
	m_pPictures->DrawHand(m_pDC, pHeld, 0);
	m_pPictures->DrawHand(m_pDC, pHeld, 1);
}

void CGroupView::BildZeichnen(bool aktiv, int index)
{
	// todo hero pic
	// CBitmap* heroPic = m_pChampionPortraits->GetChampions();
	//  CPoint koord = m_pChampionPortraits->GetKoords(heroId);

}

void CGroupView::SchadenZeichnen(int index, bool bigDmg, int dmg)
{
	CDC tmpdc;
	tmpdc.CreateCompatibleDC(m_pDC);
	int l = (int)log10(dmg);
	sprintf(m_textBuffer, "%d", dmg);
	m_pDC->SetTextColor(WEISS);
	m_pDC->SetBkColor(PURROT);
	if (bigDmg) {
		tmpdc.SelectObject(m_pPictures->GetDamageReceived(1));
		m_pDC->TransparentBlt((index - 1) * 138, 0, 64, 58, &tmpdc, 0, 0, 32, 29, TRANS_ORA);
		int x = (index - 1) * 138 + 30 - 4 * l;
		m_pDC->ExtTextOut(x, 20, ETO_CLIPPED | ETO_OPAQUE, CRect(x, 20, x + 24, 34), m_textBuffer, NULL);
	}
	else {
		tmpdc.SelectObject(m_pPictures->GetDamageReceived(0));
		m_pDC->TransparentBlt((index - 1) * 138, 0, 96, 14, &tmpdc, 0, 0, 48, 7, TRANS_ORA);
		int x = (index - 1) * 138 + 40 - 4 * l;
		m_pDC->ExtTextOut(x, -1, ETO_CLIPPED | ETO_OPAQUE, CRect(x, 0, x + 24, 14), m_textBuffer, NULL);
	}

	tmpdc.DeleteDC();
}