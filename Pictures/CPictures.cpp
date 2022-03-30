#include "stdafx.h"
#include "DM.h"
#include "CPictures.h"
#include "CWallPic.h"
#include "Items2D/CItemPic.h"
#include "..\Mobs\Held.h"
#include "..\Items\Decoration.h"
#include "..\Items\CMiscellaneous.h"
#include "..\Rucksack.h"

CPictures::CPictures(CDC* pDC) : CBasePictures(pDC)
{	
	InitBitmaps();
	m_pItemPic = new CItemPic(pDC);
}

CPictures::~CPictures() 
{

	delete m_pBmpHintergrund;
	delete m_pBmpInversePfeile;
	delete m_pBmpRuck;
	delete m_pBmpKram;
	for (int i = 1; i < 5; i++) {
		delete m_pWizardTabs[i];
		if (i < 4) {
			delete m_pRunes[i];
		}
	}
	delete m_pActionsArea;
	delete m_pActionsDamage;
	delete m_pOneHand;
	delete m_pItemPic;
}


double CPictures::getFaktor(int iEntfernung) {
	if (iEntfernung == 1) return 1;
	if (iEntfernung == 2) return 0.75;
	if (iEntfernung == 3) return 0.5;
	if (iEntfernung == 4) return 0.4;
	return 1; // todo 1 !
}


void CPictures::InitBitmaps()
{
	// raus hier -> zu Init Dungeon

	LoadPic(m_pBmpHintergrund, IDB_BITMAP_E);
	LoadPic(m_pBmpInversePfeile, IDB_BITMAP_PINV);

	LoadPic(m_pBmpRuck, IDB_BITMAP_RUCK);
	LoadPic(m_pBmpKram, IDB_BITMAP_KRAM);
	LoadPic(m_pRunes[1], IDB_RUNES1);
	LoadPic(m_pRunes[2], IDB_RUNES2);
	LoadPic(m_pRunes[3], IDB_RUNES3);
	LoadPic(m_pWizardTabs[3], IDB_REITER3);
	LoadPic(m_pWizardTabs[4], IDB_REITER4);
	LoadPicAndFlip(m_pWizardTabs[1], IDB_REITER4);
	LoadPicAndFlip(m_pWizardTabs[2], IDB_REITER3);
	LoadPic(m_pActionsArea, IDB_ACTIONS_AREA);
	LoadPic(m_pActionsDamage, IDB_ACTIONS_DAMAGE);
	LoadPic(m_pOneHand, IDB_ONE_HAND);

}

CBitmap* CPictures::GetActionDamage(int dmg) {

	// TODO Zahl dazu!
	return m_pActionsDamage;
}


void CPictures::WerteZeichnen(CDC* pDC, CHeld* pHeld)
{
	// Hp, St, Ma - Balken
	int x = (pHeld->getIndex() - 1) * 138 + 94;
	pDC->FillSolidRect(CRect(x, 4, x + 35, 52), GANZDUNKELGRAU);
	pDC->FillSolidRect(CRect(x, 52 - int(48 * pHeld->LifePart()), x + 7, 52), pHeld->Farbe());
	int s = int(48 * pHeld->StaminaPart());
	pDC->FillSolidRect(CRect(x + 14, 52 - int(48 * pHeld->StaminaPart()), x + 21, 52), pHeld->Farbe());
	pDC->FillSolidRect(CRect(x + 28, 52 - int(48 * pHeld->ManaPart()), x + 35, 52), pHeld->Farbe());
}

void CPictures::WaffeZeichnen(CDC* pDC)
{
	// ggf. die Hand (zweimal!)
}

void CPictures::SymbolZeichnen(CDC* pDC, int heldIndex, SUBPOS relPos)
{
	// kleines Symbol oben rechts; zeigt Richtung / Subpos der einzelnen Helden an
	CDC tmpdc;
	tmpdc.CreateCompatibleDC(pDC);

	tmpdc.SelectObject(m_pBmpRuck);
	int sx = 560 + (((heldIndex == 1) || (heldIndex == 4)) ? 0 : 40);
	int sy = (heldIndex > 2) ? 28 : 0;

	int dx = 560 + ((relPos & 0x1000) ? 0 : 40);
	int dy = (relPos & 0x0100) ? 0 : 28;
	pDC->BitBlt(dx, dy, 40, 28, &tmpdc, sx, sy, SRCCOPY);
	tmpdc.DeleteDC();
}

void CPictures::DrawHand(CDC* pDC, CHeld* pHeld, int handId) {
	CDC tmpdc;
	tmpdc.CreateCompatibleDC(pDC);
	
	CMiscellaneous* itemInThistHand = pHeld->GetItemCarrying(handId);

	if (itemInThistHand == NULL) {
		tmpdc.SelectObject(m_pBmpRuck);
		pDC->BitBlt((pHeld->getIndex() - 1) * 138 + 5 + 40 * handId, 16, 37, 37, &tmpdc, 5 + 40 * handId, 16, SRCCOPY);
	}
	else {
		CBitmap* bmp = m_pItemPic->GetBitmap(itemInThistHand);
		CPoint pos = m_pItemPic->GetSheetKoords(itemInThistHand);
		tmpdc.SelectObject(bmp);
		pDC->StretchBlt((pHeld->getIndex() - 1) * 138 + 5 + 40 * handId, 16, 32, 32, &tmpdc, pos.x, pos.y, 16, 16, SRCCOPY);
	}
	tmpdc.DeleteDC();

}

void CPictures::HaendeZeichnen(CDC* pDC, int index, CHeld* pHeld)
{
	RECT r = { (index - 1) * 138, 0, (index - 1) * 138 + 138, 64 };
	CBrush* b = new CBrush(GANZDUNKELGRAU);
	pDC->FillRect(&r, b);
	delete b;
	
	DrawHand(pDC, pHeld, 0);
	DrawHand(pDC, pHeld, 1);

}

void CPictures::KnochenZeichnen(CDC* pDC, int index)
{
	CDC tmpdc;
	tmpdc.CreateCompatibleDC(pDC);

	tmpdc.SelectObject(m_pBmpKram);
	pDC->BitBlt((index - 1) * 138, 0, 138, 56, &tmpdc, 276, 320, SRCCOPY);

	tmpdc.DeleteDC();
}

void CPictures::BildZeichnen(CDC* pDC, bool aktiv, int index)
{
	// todo hero pic
}

void CPictures::RucksackZeichnen(CDC* pDC, CHeld* pHeld)
{
	CRucksack* pRucksack = pHeld->GetRucksack();
	int iModusExtend = pRucksack->HoleModusExtend();
	ZeichnenHauptbereichHintergrund(pDC, iModusExtend);
	if (iModusExtend == MOD_EXT_NORMAL)
		ZeichneHungerDurst(pDC, pHeld->getFood(), pHeld->getWater());
	else if (iModusExtend == MOD_EXT_AUGE)
		ZeichneSkills(pDC, pHeld, pRucksack);
	ZeichneHpStMa(pDC, pHeld->Hp(), pHeld->St(), pHeld->Ma());
}

void CPictures::ZeichnenHauptbereichHintergrund(CDC* pDC, int iModusExtend)
{
	CDC tmpdc;
	tmpdc.CreateCompatibleDC(pDC);
	tmpdc.SelectObject(m_pBmpRuck);
	pDC->BitBlt(0, 64, 460, 270, &tmpdc, 0, 64, SRCCOPY);

	if (iModusExtend == MOD_EXT_AUGE)
		pDC->BitBlt(22, 88, 34, 36, &tmpdc, 0, 338, SRCCOPY);

	// TODO Items in Rucksack malen!

	tmpdc.DeleteDC();
}

void CPictures::NameZeichnen(CDC* pDC, bool aktiv, int index, CString strName)
{
	if (aktiv)
		pDC->SetTextColor(GELB);
	else
		pDC->SetTextColor(HELLBRAUN);
	pDC->SetBkColor(DUNKELGRAU);
	int x = (index - 1) * 138;
	pDC->ExtTextOut(x + 4, -3, ETO_CLIPPED | ETO_OPAQUE, CRect(x, 0, x + 86, 12), strName, NULL);
}

void CPictures::SchadenZeichnen(CDC* pDC, int index)
{
	CDC tmpdc;
	tmpdc.CreateCompatibleDC(pDC);

	tmpdc.SelectObject(m_pBmpKram);
	pDC->BitBlt((index - 1) * 138, 0, 84, 14, &tmpdc, 192, 92, SRCCOPY);

	tmpdc.DeleteDC();
	DeleteDC(tmpdc);
}

void CPictures::ZeichneHungerDurst(CDC* pDC, int i, int j)
{
	pDC->FillSolidRect(CRect(230, 206, 230 + i, 218), SCHWARZ);
	COLORREF col;
	if (i > 50)
		col = DUNKELBRAUN;
	else if (i > 15)
		col = GELB;
	else
		col = ROT;
	pDC->FillSolidRect(CRect(226, 202, 226 + i, 214), col);

	pDC->FillSolidRect(CRect(230, 252, 230 + j, 264), SCHWARZ);
	if (j > 50)
		col = BLAU;
	else if (j > 15)
		col = GELB;
	else
		col = ROT;
	pDC->FillSolidRect(CRect(226, 248, 226 + j, 260), col);

}

void CPictures::ZeichneHpStMa(CDC* pDC, WERTE hp, WERTE st, WERTE ma)
{
	pDC->SetTextColor(HELLGRAU);
	pDC->SetBkColor(GANZDUNKELGRAU);

	CString str;
	str.Format("%i / %i", hp.Aktuell, hp.Max);
	pDC->TextOut(120, 284, str);
	str.Format("%i / %i", st.Aktuell, st.Max);
	pDC->TextOut(120, 300, str);
	str.Format("%i / %i", ma.Aktuell, ma.Max);
	pDC->TextOut(120, 316, str);
}


void CPictures::ZeichneSkills(CDC* pDC, CHeld* pHeld, CRucksack* pRucksack)
{
	pDC->SetTextColor(HELLGRAU);
	pDC->SetBkColor(GANZDUNKELGRAU);
	CString strZeile, strTitel, strKlasse;

	long* sExp = pHeld->getExp();
	VITALS sVitals = pHeld->getVitals();

	pDC->FillSolidRect(210, 170, 226, 142, GANZDUNKELGRAU);
	for (int i = 1; i < 5; i++)
	{
		if (sExp[i] > 0)
		{
			strTitel = pRucksack->GetTitle(sExp[i]);
			strKlasse = pRucksack->GetClass(i);
			strZeile.Format("%s %s", strTitel, strKlasse);
			pDC->TextOut(230, 160 + i * 16, strZeile);
		}
	}
}

void CPictures::PfeilZeichnen(CDC* pDC, int index)
{
	CDC tmpdc;
	tmpdc.CreateCompatibleDC(pDC);
	tmpdc.SelectObject(m_pBmpInversePfeile);
	switch (index)
	{
	case VORWAERTS:
		pDC->BitBlt(526, 248, 54, 42, &tmpdc, 62, 3, SRCCOPY);
		break;
	case RUECKWAERTS:
		pDC->BitBlt(526, 292, 54, 42, &tmpdc, 62, 47, SRCCOPY);
		break;
	case LINKS_STRAFE:
		pDC->BitBlt(468, 292, 56, 42, &tmpdc, 4, 47, SRCCOPY);
		break;
	case RECHTS_STRAFE:
		pDC->BitBlt(582, 292, 56, 42, &tmpdc, 118, 47, SRCCOPY);
		break;
	case LINKS_DREHEN:
		pDC->BitBlt(468, 248, 56, 42, &tmpdc, 4, 3, SRCCOPY);
		break;
	case RECHTS_DREHEN:
		pDC->BitBlt(582, 248, 56, 42, &tmpdc, 118, 3, SRCCOPY);
		break;
	}
	tmpdc.DeleteDC();
}
