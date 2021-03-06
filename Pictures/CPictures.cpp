#include "stdafx.h"
#include "stdafx.h"
#include "DM.h"
#include "CPictures.h"
#include "CWallPic.h"
#include "Items2D/CItemPic.h"
#include "..\Mobs\Held.h"
#include "..\Items\FloorDecoration.h"
#include "..\Items\Item.h"
#include "..\XMLParser\ItemInfos.h"
#include "..\Rucksack.h"
#include "..\CalculationHelper\CScreenCoords.h"
#include "..\CalculationHelper\CHelpfulValues.h"
#include "..\Consts\WeaponConst.h"
#include <sstream>
#include <string>

CPictures::CPictures(CDC* pDC) : CBasePictures(pDC)
{	
	InitBitmaps();
	m_pItemPic = new CItemPic(pDC);
	m_textBuffer = new char[10];
}

CPictures::~CPictures() 
{
	delete m_textBuffer;
	delete m_pBmpHintergrund;
	delete m_pBmpInversePfeile;
	delete m_pBmpPfeile;
	delete m_pBmpRuck;
	for (int i = 1; i < 5; i++) {
		delete m_pWizardTabs[i];
		delete m_pRunes[i];
		if (i < 3) {
			delete m_pDamageReceived[i-1];
			delete m_pInterface[i-1];
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
	LoadPic(m_pBmpPfeile, IDB_BITMAP_P);
	LoadPic(m_pDamageReceived[0], IDB_DMG_REC_SMALL);
	LoadPic(m_pDamageReceived[1], IDB_DMG_REC_BIG);
	LoadPic(m_pInterface[0], IDB_INTERFACE_ALIVE);
	LoadPic(m_pInterface[1], IDB_INTERFACE_DEAD);

	LoadPic(m_pBmpRuck, IDB_BITMAP_RUCK);
	LoadPic(m_pRunes[1], IDB_RUNES1);
	LoadPic(m_pRunes[2], IDB_RUNES2);
	LoadPic(m_pRunes[3], IDB_RUNES3);
	LoadPic(m_pRunes[4], IDB_RUNES4);
	LoadPic(m_pWizardTabs[3], IDB_REITER3);
	LoadPic(m_pWizardTabs[4], IDB_REITER4);
	LoadPicAndFlip(m_pWizardTabs[1], IDB_REITER4);
	LoadPicAndFlip(m_pWizardTabs[2], IDB_REITER3);
	LoadPic(m_pActionsArea, IDB_ACTIONS_AREA);
	LoadPic(m_pActionsDamage, IDB_ACTIONS_DAMAGE);
	LoadPic(m_pOneHand, IDB_ONE_HAND);

}

CBitmap* CPictures::GetIconBitmap(CDC* pDC, CItem* pItem) {
	CDC iconDC;
	CDC sheetDC;
	iconDC.CreateCompatibleDC(pDC);
	sheetDC.CreateCompatibleDC(pDC);
	
	CBitmap* bmpSheet = m_pItemPic->GetBitmapSheet(pItem);
	CBitmap* bmpIcon = new CBitmap();
	bmpIcon->CreateCompatibleBitmap(pDC, 32, 32);

	CPoint p = m_pItemPic->GetSheetKoords(pItem);
	sheetDC.SelectObject(bmpSheet);
	iconDC.SelectObject(bmpIcon);
	iconDC.StretchBlt(0, 0, 32, 32, &sheetDC, p.x, p.y, 16, 16, SRCCOPY);

	DeleteObject(iconDC);
	DeleteObject(sheetDC);
	return bmpIcon;
}


void CPictures::WerteZeichnen(CDC* pDC, CHeld* pHeld)
{
	int index = pHeld->getIndex();

	CDC tmpdc;
	tmpdc.CreateCompatibleDC(pDC);	
	tmpdc.SelectObject(m_pInterface[0]);
	pDC->StretchBlt((index - 1) * 138, 0, 138, 56, &tmpdc, 0, 0, 80, 29, SRCCOPY);

	// Hp, St, Ma - Balken
	int x = (pHeld->getIndex() - 1) * 138 + 94;

	pDC->FillSolidRect(CRect(x, 52 - int(48 * pHeld->LifePart()), x + 7, 52), pHeld->Farbe());
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

	int dx = 560 + ((relPos & 0b1000) ? 0 : 40);
	int dy = (relPos & 0b0100) ? 0 : 28;
	pDC->BitBlt(dx, dy, 40, 28, &tmpdc, sx, sy, SRCCOPY);
	tmpdc.DeleteDC();
}

void CPictures::DrawHand(CDC* pDC, CHeld* pHeld, int handId) {
	CDC tmpdc;
	tmpdc.CreateCompatibleDC(pDC);
	
	CItem* itemInThisHand = pHeld->GetItemCarrying(handId);
	
	tmpdc.SelectObject(m_pBmpRuck);
	pDC->BitBlt((pHeld->getIndex() - 1) * 138 + 5 + 40 * handId, 16, 37, 37, &tmpdc, 5 + 40 * handId, 16, SRCCOPY);

	if (itemInThisHand != NULL) {
		CBitmap* bmp = m_pItemPic->GetBitmapSheet(itemInThisHand);
		CPoint pos = m_pItemPic->GetSheetKoords(itemInThisHand);
		tmpdc.SelectObject(bmp);
		pDC->StretchBlt((pHeld->getIndex() - 1) * 138 + 7 + 40 * handId, 18, 32, 32, &tmpdc, pos.x, pos.y, 16, 16, SRCCOPY);
	}
	tmpdc.DeleteDC();

}

void CPictures::HaendeZeichnen(CDC* pDC, CHeld* pHeld)
{
	DrawHand(pDC, pHeld, 0);
	DrawHand(pDC, pHeld, 1);

}

void CPictures::KnochenZeichnen(CDC* pDC, int index)
{
	CDC tmpdc;
	tmpdc.CreateCompatibleDC(pDC);
	tmpdc.SelectObject(m_pInterface[1]);
	pDC->StretchBlt((index - 1) * 138, 0, 138, 56, &tmpdc, 0, 0, 80, 29, SRCCOPY);

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
	GewichtZeichnen(pDC, pHeld);
	if (iModusExtend == MOD_EXT_NORMAL)
		ZeichneHungerDurst(pDC, pHeld->getFood(), pHeld->getWater());
	else if (iModusExtend == MOD_EXT_AUGE)
		ZeichneSkills(pDC, pHeld);
	ZeichneHpStMa(pDC, pHeld->Hp(), pHeld->St(), pHeld->Ma());
	ZeichneIcons(pDC, pHeld);
}

void CPictures::ZeichnenHauptbereichHintergrund(CDC* pDC, int iModusExtend)
{
	CDC tmpdc;
	tmpdc.CreateCompatibleDC(pDC);
	tmpdc.SelectObject(m_pBmpRuck);
	pDC->BitBlt(0, 64, 460, 270, &tmpdc, 0, 64, SRCCOPY);

	if (iModusExtend == MOD_EXT_AUGE)
		pDC->BitBlt(22, 88, 34, 36, &tmpdc, 0, 338, SRCCOPY);

	tmpdc.DeleteDC();
}

void CPictures::ZeichneIcons(CDC* pDC, CHeld* pHeld) {
	CDC tmpdc;
	tmpdc.CreateCompatibleDC(pDC);

	for (int iconID = 0; iconID < 30; iconID++) {
		CItem* item = pHeld->GetItemCarrying(iconID);
		if (item) {
			CPoint posBackpack = CScreenCoords::GetbackPackSlotKoords(iconID);
			CBitmap* bmp = m_pItemPic->GetBitmapSheet(item);
			CPoint pos = m_pItemPic->GetSheetKoords(item);
			tmpdc.SelectObject(bmp);
			//pDC->TransparentBlt(posBackpack.x, posBackpack.y, 32, 32, &tmpdc, pos.x, pos.y, 16, 16, TRANS_GRA);
			pDC->StretchBlt(posBackpack.x, posBackpack.y, 32, 32, &tmpdc, pos.x, pos.y, 16, 16, SRCCOPY);
		}
	}

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
	pDC->ExtTextOut(x + 4, -2, ETO_CLIPPED | ETO_OPAQUE, CRect(x, 0, x + 78, 14), strName, NULL);
}

void CPictures::SchadenZeichnen(CDC* pDC, int index, bool bigDmg, int dmg)
{
	CDC tmpdc;
	tmpdc.CreateCompatibleDC(pDC);
	int l = (int)log10(dmg);
	sprintf(m_textBuffer, "%d", dmg);
	pDC->SetTextColor(WEISS);
	pDC->SetBkColor(PURROT);
	if (bigDmg) {
		tmpdc.SelectObject(m_pDamageReceived[1]);
		pDC->TransparentBlt((index - 1) * 138, 0, 64, 58, &tmpdc, 0, 0, 32, 29, TRANS_ORA);
		int x = (index - 1) * 138 + 30 - 4 * l;
		pDC->ExtTextOut(x, 20, ETO_CLIPPED | ETO_OPAQUE, CRect(x, 20, x + 24, 34), m_textBuffer, NULL);
	}
	else {
		tmpdc.SelectObject(m_pDamageReceived[0]);
		pDC->TransparentBlt((index - 1) * 138, 0, 96, 14, &tmpdc, 0, 0, 48, 7, TRANS_ORA); 
		int x = (index - 1) * 138 + 40 - 4*l;
		pDC->ExtTextOut(x, -1, ETO_CLIPPED | ETO_OPAQUE, CRect(x, 0, x + 24, 14), m_textBuffer, NULL);
	}

	tmpdc.DeleteDC();
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


void CPictures::ZeichneSkills(CDC* pDC, CHeld* pHeld)
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
			strTitel = CHelpfulValues::SkillGrade(sExp[i]);
			strKlasse = CHelpfulValues::SkillClass(i-1);
			strZeile.Format("%s %s", strTitel, strKlasse);
			pDC->TextOut(230, 160 + i * 16, strZeile);
		}
	}
}

void CPictures::DrawActionAreaChoice(CDC* pDC, CItemInfos* m_pItemInfos, int weaponIndex) {
	CDC tmpdc;
	tmpdc.CreateCompatibleDC(pDC);
	tmpdc.SelectObject(m_pActionsArea);
	BITMAP bmpInfo;
	double numberActions = 3;
	CString actionText[3];
	for (int j = 0; j < 3; j++) {
		actionText[j] = m_pItemInfos->GetWeaponInfo(weaponIndex).style[j].type;
		if (actionText[j].GetLength() == 0)
			numberActions--;
	}
	
	m_pActionsArea->GetBitmap(&bmpInfo);
	double partFactor = (numberActions + 1) / 4.0;
	pDC->TransparentBlt(448, 150, bmpInfo.bmWidth * 2, bmpInfo.bmHeight * 2 * partFactor, &tmpdc, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight * partFactor, SRCCOPY);
	for (int j = 0; j < 3; j++) {
		DrawText(pDC, 474, 170 + j * 23, actionText[j], 20, WEISS, SCHWARZ);
	}
	DeleteDC(tmpdc);
}

void CPictures::DrawText(CDC* pDC, int x, int y, CString text, int h, COLORREF fc, COLORREF bc) {
	HFONT hFont;
	HDC hDC = pDC->GetSafeHdc();
	SetTextColor(hDC, fc);
	SetBkColor(hDC, bc);
	hFont = CreateFont(h, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 2, 0, "SYSTEM_FIXED_FONT");
	SelectObject(hDC, hFont);
	pDC->TextOut(x, y, text);
	DeleteObject(hFont);
}

void CPictures::DrawActionAreaDamage(CDC* pDC, int dmg) {
	CString text = "";
	text.Format("%d", dmg);

	CDC tmpdc;
	tmpdc.CreateCompatibleDC(pDC);
	tmpdc.SelectObject(m_pActionsDamage);
	BITMAP bmpInfo;
	m_pActionsDamage->GetBitmap(&bmpInfo);
	pDC->TransparentBlt(448, 150, bmpInfo.bmWidth * 2, bmpInfo.bmHeight * 2, &tmpdc, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);
	DrawText(pDC, 532, 180, text, 34, HELLBLAU, SCHWARZ);

	DeleteDC(tmpdc);
}

void CPictures::DrawActiveWeapon(CDC* pDC, CHeld* held, int id) {
	CDC tmpdc;
	tmpdc.CreateCompatibleDC(pDC);

	CItem* itemInThisHand = held->GetItemCarrying(1);
	if (itemInThisHand == NULL) {
		tmpdc.SelectObject(GetOneHand());
		pDC->BitBlt(466 + 44 * (id - 1), 176, 44, 66, &tmpdc, 0, 0, SRCCOPY);
	}
	else
	{
		int x = 466 + 44 * (id - 1);		
		pDC->FillSolidRect(CRect(x, 176, x + 40, 242), HELLBLAU);
		CBitmap* bmp = m_pItemPic->GetBitmapSheet(itemInThisHand);
		CPoint pos = m_pItemPic->GetSheetKoords(itemInThisHand);
		tmpdc.SelectObject(bmp);
		pDC->TransparentBlt(466 + 50 * (id - 1), 193, 32, 32, &tmpdc, pos.x, pos.y, 16, 16, TRANS_GRA);
	}
}

void CPictures::PfeilZeichnen(CDC* pDC, int index)
{
	CDC tmpdc;
	tmpdc.CreateCompatibleDC(pDC);
 	tmpdc.SelectObject(m_pBmpPfeile);
	pDC->BitBlt(468, 248, 168, 90, &tmpdc, 0, 0, SRCCOPY);

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

void CPictures::GewichtZeichnen(CDC* pDC, CHeld* pHeld) {
	pDC->SetTextColor(HELLGRAU);
	pDC->SetBkColor(GANZDUNKELGRAU);
	double dCurValue = pHeld->CurLoad();
	double dMaxValue = pHeld->MaxLoad();

	CString strZeile;
	strZeile.Format("LOAD         %1.1f/ %2.1f KG", dCurValue, dMaxValue);
	pDC->TextOut(208, 320, strZeile);
}
