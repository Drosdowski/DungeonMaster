#include "stdafx.h"
#include "DM.h"
#include "CPictures.h"
#include "CWallPic.h"
#include "DMFont.h"
#include "Items2D/CItemPic.h"
#include "..\Mobs\Held.h"
#include "..\Mobs\MobGroups\GrpHeld.h"
#include "..\Items\FloorDecoration.h"
#include "..\Items\Item.h"
#include "..\Items\Scroll.h"
#include "..\Items\Cloth.h"
#include "..\Items\Container.h"
#include "..\Items\CMiscellaneous.h"
#include "..\Items\Weapon.h"
#include "..\Items\Potion.h"
#include "..\XMLParser\ItemInfos.h"
#include "..\CalculationHelper\CScreenCoords.h"
#include "..\CalculationHelper\CHelpfulValues.h"
#include "..\Consts\WeaponConst.h"
#include "ChampionPortrait.h"
#include <sstream>
#include <string>
#include <ft2build.h>
#include <cassert>
#include FT_FREETYPE_H

CPictures::CPictures(CDC* pDC) : CBasePictures(pDC)
{	
	InitBitmaps();
	m_pItemPic = new CItemPic(pDC);
	m_pDMFont = new CDMFont(pDC);
	m_pChampionPortraits = new CChampionPortrait(pDC);
}

CPictures::~CPictures() 
{
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
	delete m_pActionInactive;
	delete m_pActionsArea;
	delete m_pActionsDamage;
	delete m_pOneHand;
	delete m_pItemPic;
	delete m_pOpenScroll;
	delete m_pOpenChest;
	delete m_pDMFont;
	delete m_pItemCircle;
	delete m_pChampionPortraits;
}

void CPictures::InitBitmaps()
{
	LoadPic(m_pBmpHintergrund, IDB_BITMAP_E);
	LoadPic(m_pBmpInversePfeile, IDB_BITMAP_PINV);
	LoadPic(m_pBmpPfeile, IDB_BITMAP_P);
	LoadPic(m_pDamageReceived[0], IDB_DMG_REC_SMALL);
	LoadPic(m_pDamageReceived[1], IDB_DMG_REC_BIG);
	LoadPic(m_pInterface[0], IDB_INTERFACE_ALIVE);
	LoadPic(m_pInterface[1], IDB_INTERFACE_DEAD);
	LoadPic(m_pItemCircle, IDB_CIRCLE);

	LoadPic(m_pBmpRuck, IDB_BITMAP_RUCK);
	LoadPic(m_pRunes[1], IDB_RUNES1);
	LoadPic(m_pRunes[2], IDB_RUNES2);
	LoadPic(m_pRunes[3], IDB_RUNES3);
	LoadPic(m_pRunes[4], IDB_RUNES4);
	LoadPic(m_pWizardTabs[3], IDB_REITER3);
	LoadPic(m_pWizardTabs[4], IDB_REITER4);
	LoadPicAndFlip(m_pWizardTabs[1], IDB_REITER4);
	LoadPicAndFlip(m_pWizardTabs[2], IDB_REITER3);
	LoadPic(m_pActionInactive, IDB_ACTION_INACTIVE);
	LoadPic(m_pActionsArea, IDB_ACTIONS_AREA);
	LoadPic(m_pActionsDamage, IDB_ACTIONS_DAMAGE);
	LoadPic(m_pOneHand, IDB_ONE_HAND);
	LoadPic(m_pOpenScroll, IDB_OPEN_SCROLL);
	LoadPic(m_pOpenChest, IDB_OPEN_CHEST);
}

CBitmap* CPictures::GetIconBitmap(CDC* pDC, CItem* pItem) {
	CDC iconDC;
	CDC sheetDC;
	iconDC.CreateCompatibleDC(pDC);
	sheetDC.CreateCompatibleDC(pDC);
	
	CBitmap* bmpSheet = m_pItemPic->GetBitmapSheet(pItem);
	CBitmap* bmpIcon = new CBitmap();
	bmpIcon->CreateCompatibleBitmap(pDC, 32, 32);

	CPoint p = m_pItemPic->GetSheetKoords(pItem, false);
	sheetDC.SelectObject(bmpSheet);
	iconDC.SelectObject(bmpIcon);
	iconDC.StretchBlt(0, 0, 32, 32, &sheetDC, p.x, p.y, 16, 16, SRCCOPY);

	DeleteObject(iconDC);
	DeleteObject(sheetDC);
	return bmpIcon;
}


//void CPictures::WaffeZeichnen(CDC* pDC)
//{
	// ggf. die Hand (zweimal!)
//}

void CPictures::DrawSymbol(CDC* pDC, int heldIndex, SUBPOS relPos)
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
		CPoint pos = m_pItemPic->GetSheetKoords(itemInThisHand, true);
		tmpdc.SelectObject(bmp);
		pDC->StretchBlt((pHeld->getIndex() - 1) * 138 + 8 + 40 * handId, 18, 32, 32, &tmpdc, pos.x, pos.y, 16, 16, SRCCOPY);
	}
	tmpdc.DeleteDC();

}


void CPictures::DrawBackback(CDC* pDC, CGrpHeld* pGrpHelden)
{
	CHeld* pHeld = pGrpHelden->GetActiveHero();
	CItem* pItem = pGrpHelden->GetItemInHand();
	CItem* pActiveItem = pHeld->GetItemCarrying(1);

	bool bLooking = pHeld->GetBackpackLooking();
	bool bEating = pHeld->GetMouthEating();
	DrawMainAreaBackground(pDC, bLooking, bEating);
	DrawWeight(pDC, pHeld);
	if (!bLooking)
		if (pActiveItem && pActiveItem->getItemType() == CItem::ScrollItem)
			DrawScroll(pDC, (CScroll*)pActiveItem);
		else if (pActiveItem && pActiveItem->getItemType() == CItem::ContainerItem)
			DrawContainer(pDC, (CContainer*)pActiveItem);
		else
			DrawVitals(pDC, pHeld->getFood(), pHeld->getWater());
	else {
		if (pItem) {
			if (pItem->getItemType() == CItem::ScrollItem)
				DrawScroll(pDC, (CScroll*)pItem);
			else if (pItem->getItemType() == CItem::ContainerItem)
				DrawContainer(pDC, (CContainer*)pItem);
			else
				DrawItemInfo(pDC, pItem);
		}
		else {
			DrawSkills(pDC, pHeld);
		}

	}
	DrawHpStMa(pDC, pHeld);
	DrawIcons(pDC, pHeld);
}

void CPictures::DrawMainAreaBackground(CDC* pDC, bool bLooking, bool bEating)
{
	CDC tmpdc;
	tmpdc.CreateCompatibleDC(pDC);
	tmpdc.SelectObject(m_pBmpRuck);
	pDC->BitBlt(0, 64, 460, 270, &tmpdc, 0, 64, SRCCOPY);

	if (bLooking)
		pDC->BitBlt(22, 88, 34, 34, &tmpdc, 0, 338, SRCCOPY);
	if (bEating)
		pDC->BitBlt(110, 88, 34, 34, &tmpdc, 34, 338, SRCCOPY);

	tmpdc.DeleteDC();
}

void CPictures::DrawIcons(CDC* pDC, CHeld* pHeld) {
	CDC tmpdc;
	tmpdc.CreateCompatibleDC(pDC);

	for (int iconID = 0; iconID < 30; iconID++) {
		CItem* item = pHeld->GetItemCarrying(iconID);
		if (item) {
			CPoint posBackpack = CScreenCoords::GetBackPackSlotKoords(iconID);
			CBitmap* bmp = m_pItemPic->GetBitmapSheet(item);
			CPoint pos = m_pItemPic->GetSheetKoords(item, iconID < 2);
			tmpdc.SelectObject(bmp);
			//pDC->TransparentBlt(posBackpack.x, posBackpack.y, 32, 32, &tmpdc, pos.x, pos.y, 16, 16, TRANS_GRA);
			pDC->FillSolidRect(CRect(posBackpack.x, posBackpack.y, posBackpack.x + 32, posBackpack.y + 32), GANZDUNKELGRAU);
			pDC->TransparentBlt(posBackpack.x, posBackpack.y, 32, 32, &tmpdc, pos.x, pos.y, 16, 16, TRANS_GRA);
		}
	}

	tmpdc.DeleteDC();
}

void CPictures::DrawItemInfo(CDC* pDC, CItem* item) {
	CDC tmpdc;
	tmpdc.CreateCompatibleDC(pDC);

	pDC->FillSolidRect(CRect(220, 170, 380, 300), GANZDUNKELGRAU);
	tmpdc.SelectObject(m_pItemCircle);
	pDC->TransparentBlt(210, 170, 64, 54, &tmpdc, 0, 0, 32, 27, TRANS_GRA);
	CBitmap* bmp = m_pItemPic->GetBitmapSheet(item);
	CPoint pos = m_pItemPic->GetSheetKoords(item, true); 
	tmpdc.SelectObject(bmp);
	pDC->TransparentBlt(222, 182, 32, 32 , &tmpdc, pos.x, pos.y, 16, 16, TRANS_GRA);

	// todo Text for item : strength
	pDC->SetTextColor(SCHWARZ);
	pDC->SetBkColor(WEISSER);
	DrawFontText(pDC, 278, 190, item->GetName(), false);
	CString strWeight;
	strWeight.Format("WEIGHS %1.1f KG.", item->GetWeight());
	DrawFontText(pDC, 212, 226, strWeight, false);

	tmpdc.DeleteDC();
}

void CPictures::DrawContainer(CDC* pDC, CContainer* pContainer) {
	CDC tmpdc;
	tmpdc.CreateCompatibleDC(pDC);

	CBitmap* bmp = m_pOpenChest;
	CPoint posChest = m_pItemPic->GetChestKoord();
	tmpdc.SelectObject(bmp);
	pDC->TransparentBlt(posChest.x, posChest.y, 288, 146, &tmpdc, 0, 0, 144, 73, TRANS_BLU);

	for (int iconID = 0; iconID < 8; iconID++) {
		CItem* item = pContainer->GetSubItem(iconID);
		if (item) {
			CPoint posContainer = CScreenCoords::GetContainerSlotKoords(iconID);
			CBitmap* bmp = m_pItemPic->GetBitmapSheet(item);
			CPoint pos = m_pItemPic->GetSheetKoords(item, false);
			tmpdc.SelectObject(bmp);
			pDC->StretchBlt(posContainer.x, posContainer.y, 32, 32, &tmpdc, pos.x, pos.y, 16, 16, SRCCOPY);
		}
	}
	tmpdc.DeleteDC();
}

void CPictures::DrawScroll(CDC* pDC, CScroll* scroll) {
	CDC tmpdc;
	tmpdc.CreateCompatibleDC(pDC);

	CBitmap* bmp = m_pOpenScroll;
	CPoint pos = m_pItemPic->GetScrollKoord();
	tmpdc.SelectObject(bmp);
	pDC->TransparentBlt(pos.x, pos.y, 256, 146, &tmpdc, 0, 0, 128, 73, TRANS_BLU);

	pDC->SetTextColor(SCHWARZ);
	pDC->SetBkColor(WEISSER);
	// CRect r = CRect(pos.x + 40, 192, pos.x + 210, 290);
	DrawFontText(pDC, pos.x + 40, 192, scroll->GetText(), true);
	//DrawSpecialFont(pDC, CPoint(pos.x + 125, 241), scroll->GetText(), 12);
	//pDC->DrawText(scroll->GetText(), r, ETO_CLIPPED | ETO_OPAQUE | DT_CENTER);
	tmpdc.DeleteDC();
}


void CPictures::DrawVitals(CDC* pDC, int i, int j)
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

void CPictures::DrawHpStMa(CDC* pDC, CHeld* pHeld)
{
	CString str;
	str.Format("%3i/%3i", (int)pHeld->Hp().Aktuell, (int)pHeld->HPMax());
	DrawFontText(pDC, 96, 284, str, false);

	str.Format("%3i/%3i", (int)(pHeld->St().Aktuell / 10), (int)(pHeld-> STMax()/ 10));
	DrawFontText(pDC, 96, 300, str, false);

	str.Format("%3i/%3i", (int)pHeld->Ma().Aktuell, (int)pHeld->MAMax());
	DrawFontText(pDC, 96, 316, str, false);
}


void CPictures::DrawSkills(CDC* pDC, CHeld* pHeld)
{
	pDC->SetTextColor(HELLGRAU);
	pDC->SetBkColor(GANZDUNKELGRAU);
	CString strZeile, strTitel, strKlasse;

	VITALS sVitals = pHeld->getVitals();

	pDC->FillSolidRect(210, 170, 226, 142, GANZDUNKELGRAU);
	for (int i = 1; i < 5; i++)
	{
		int level;
		switch (i)
		{
		case 1: level = pHeld->fightLevel(); break;
		case 2: level = pHeld->ninjaLevel(); break;
		case 3: level = pHeld->priestLevel(); break;
		case 4: level = pHeld->wizardLevel(); break;
		default:
			break;
		}
		if (level > 0)
		{
			int xp = (int)(500 * exp2(level - 1));
			
			strTitel = CHelpfulValues::SkillGrade(xp);
			strKlasse = CHelpfulValues::SkillClass(i-1);
			strZeile.Format("%s %s", strTitel, strKlasse);
			// pDC->TextOut(220, 160 + i * 16, strZeile);
			DrawFontText(pDC, 210, 156 + i * 14, strZeile, false);
		}
	}
	CString strValues;
	strValues.Format("%i/ %i", (int)sVitals.str.Max, (int)sVitals.str.Aktuell);
	DrawVitalText(pDC, strValues, 0, 226);
	strValues.Format("%i/ %i", (int)sVitals.dex.Max, (int)sVitals.dex.Aktuell);
	DrawVitalText(pDC, strValues, 1, 240);
	strValues.Format("%i/ %i", (int)sVitals.vit.Max, (int)sVitals.vit.Aktuell);
	DrawVitalText(pDC, strValues, 2, 254);
	strValues.Format("%i/ %i", (int)sVitals.wis.Max, (int)sVitals.wis.Aktuell);
	DrawVitalText(pDC, strValues, 3, 268);
	strValues.Format("%i/ %i", (int)sVitals.af.Max, (int)sVitals.af.Aktuell);
	DrawVitalText(pDC, strValues, 4, 282);
	strValues.Format("%i/ %i", (int)sVitals.am.Max, (int)sVitals.am.Aktuell);
	DrawVitalText(pDC, strValues, 5, 296);
}

void CPictures::DrawVitalText(CDC* pDC, CString text, int index, int y) {
	CString strZeile, strVital;
	strVital.Format("%s", CHelpfulValues::VitalName(index));
	DrawFontText(pDC, 210, y, strVital, false);
	DrawFontText(pDC, 340, y, text, false);
}


void CPictures::DrawActionAreaChoice(CDC* pDC, CItemInfos* m_pItemInfos, int weaponIndex) {
	CDC tmpdc;
	tmpdc.CreateCompatibleDC(pDC);
	tmpdc.SelectObject(m_pActionsArea);
	BITMAP bmpInfo;
	double numberActions = 3;
	CString actionText[3];
	if (weaponIndex == CLIMBINDEX) {
		actionText[0] = "climb down";
		numberActions = 1;
	}
	else if (weaponIndex >= 0)
	{
		for (int j = 0; j < 3; j++) {
			actionText[j] = m_pItemInfos->GetWeaponInfo(weaponIndex).style[j].type;
			if (actionText[j].GetLength() == 0)
				numberActions--;
		}
	}
	else {
		numberActions = 0;
	}
	
	m_pActionsArea->GetBitmap(&bmpInfo);
	double partFactor = (numberActions + 1) / 4.0;
	pDC->TransparentBlt(448, 150, bmpInfo.bmWidth * 2, (int)(bmpInfo.bmHeight * 2 * partFactor), &tmpdc, 0, 0, bmpInfo.bmWidth, (int)(bmpInfo.bmHeight * partFactor), SRCCOPY);
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

void CPictures::DrawFontText(CDC* pDC, int x, int y, CString text, bool darkFont) {
	CDC tmpdc;
	tmpdc.CreateCompatibleDC(pDC);
	text = text.MakeUpper();
	const int xz = (darkFont ? 7 : 8) * 2;
	const int yz = (darkFont ? 5 : 8) * 2;
	int currentIndex = 0;
	for (int textIndex = 0; textIndex < text.GetLength(); textIndex++) {
		char letter = text.GetAt(textIndex);
		if (letter == 10) {
			currentIndex = 0;
			y += yz + 4;
		}
		else {
			CBitmap* bmpLetter = darkFont ? GetScrollFontLetter(pDC, letter) : GetOrigFontLetter(pDC, letter);
			if (bmpLetter) {
				tmpdc.SelectObject(bmpLetter);
				CPoint pos = { x + 12 * currentIndex, y };

				pDC->TransparentBlt(pos.x, pos.y, xz, yz, &tmpdc, 0, 0, xz, yz, GANZDUNKELGRAU);
				delete bmpLetter;
				currentIndex++;
			}
		}
	}
	DeleteObject(tmpdc);
}

CBitmap* CPictures::GetOrigFontLetter(CDC* pDC, char letter) {
	CDC iconDC;
	CDC sheetDC;
	iconDC.CreateCompatibleDC(pDC);
	sheetDC.CreateCompatibleDC(pDC);

	CBitmap* bmpSheet = m_pDMFont->GetLightGreyLetters();
	CBitmap* bmpChar = new CBitmap();
	bmpChar->CreateCompatibleBitmap(pDC, 16, 16);

	CPoint p = m_pDMFont->GetKoordsLightGreyChar(letter);
	sheetDC.SelectObject(bmpSheet);
	iconDC.SelectObject(bmpChar);
	iconDC.StretchBlt(0, 0, 16, 16, &sheetDC, p.x, p.y, 8, 8, SRCCOPY);

	DeleteObject(iconDC);
	DeleteObject(sheetDC);
	return bmpChar;
}

CBitmap* CPictures::GetScrollFontLetter(CDC* pDC, char letter) {
	if (letter == 32) letter = 65 + 26 + 1;

	CPoint p = m_pDMFont->GetKoordsBlack(letter);
	if (p.x >= 0) {
		CDC iconDC;
		CDC sheetDC;
		iconDC.CreateCompatibleDC(pDC);
		sheetDC.CreateCompatibleDC(pDC);

		CBitmap* bmpSheet = m_pDMFont->GetBlackLetters();
		CBitmap* bmpChar = new CBitmap();
		bmpChar->CreateCompatibleBitmap(pDC, 14, 10);

		sheetDC.SelectObject(bmpSheet);
		iconDC.SelectObject(bmpChar);
		iconDC.StretchBlt(0, 0, 14, 10, &sheetDC, p.x, p.y, 7, 5, SRCCOPY);

		DeleteObject(iconDC);
		DeleteObject(sheetDC);

		return bmpChar;
	}
	else {
		return NULL;
	}

}


void CPictures::DrawActionAreaDamage(CDC* pDC, int dmg) {
	CString text = "";
	text.Format("%d", dmg);

	CDC tmpdc;
	tmpdc.CreateCompatibleDC(pDC);
	tmpdc.SelectObject(m_pActionsDamage);
	BITMAP bmpInfo;
	m_pActionsDamage->GetBitmap(&bmpInfo);
	pDC->TransparentBlt(448, 150, bmpInfo.bmWidth * 2, bmpInfo.bmHeight * 2, &tmpdc, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SCHWARZ);
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
		CPoint pos = m_pItemPic->GetSheetKoords(itemInThisHand, true);
		tmpdc.SelectObject(bmp);
		pDC->TransparentBlt(470 + 44 * (id - 1), 193, 32, 32, &tmpdc, pos.x, pos.y, 16, 16, TRANS_GRA);
	}
	if (!held->isReady()) {
		tmpdc.SelectObject(m_pActionInactive);
		pDC->TransparentBlt(466 + 44 * (id - 1), 176, 40, 70, &tmpdc, 0, 0, 40, 70, TRANS_BLU);
	}
	tmpdc.DeleteDC();
}

void CPictures::DrawArrow(CDC* pDC, int index)
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

void CPictures::DrawWeight(CDC* pDC, CHeld* pHeld) {
	pDC->SetTextColor(HELLGRAU);
	pDC->SetBkColor(GANZDUNKELGRAU);
	double dCurValue = pHeld->CurLoad();
	double dMaxValue = pHeld->MaxLoad();

	CString strZeile;
	strZeile="LOAD";
	DrawFontText(pDC, 210, 314, strZeile, false);

	strZeile.Format("%1.1f/ %2.1f KG", dCurValue, dMaxValue);
	int len = strZeile.GetLength();
	DrawFontText(pDC, 438 - 12*len, 314, strZeile, false);
}

void CPictures::DrawItemInfoText(CDC* pDC, CItem* item) {
	if (item) {
		pDC->SetTextColor(HELLGRAU);
		pDC->SetBkColor(SCHWARZ);
		CString strInfo = GetText(item); 
		DrawFontText(pDC, 468, 60, strInfo, false);
	}
	else {
		pDC->FillSolidRect(468, 62, 170, 16, SCHWARZ);
	}
}


void CPictures::DrawSpecialFont(CDC* pDC, CPoint pos, CString text, int size) {
	FT_Library ft;
	if (FT_Init_FreeType(&ft)) {
		return;
	}
	FT_Face face;
	if (FT_New_Face(ft, "DALEK___.ttf", 0, &face)) {
		FT_Done_FreeType(ft);
		return;
	}

	FT_Set_Pixel_Sizes(face, 0, size); 
	HDC hDC = pDC->GetSafeHdc();
	SetTextColor(hDC, WEISS);
	int x = pos.x;
	int y = pos.y;
	// Breite ermitteln
	int rowWidth[5];
	int currentWidth = 0;
	int maxHeight = 0, allheight = 0;
	int maxRows = 0;
	int line = 0;
	for (size_t i = 0; i < strlen(text); ++i) {
		if (text[i] == '\n')
		{
			rowWidth[line] = currentWidth;
			allheight += maxHeight;
			maxHeight = 0;
			currentWidth = 0;
			line++;
			continue;
		}
		FT_Load_Char(face, text[i], FT_LOAD_RENDER);
		currentWidth += (face->glyph->advance.x >> 6);
		maxHeight = max((int)(face->size->metrics.height >> 6), maxHeight);
		maxRows = max((int)(face->glyph->bitmap.rows), maxRows);
	}
	rowWidth[line] = currentWidth;
	allheight += maxHeight;
	line = 0;
	// Zeichnen
	for (size_t i = 0; i < strlen(text); i++) {
		if (text[i] == '\n')
		{
			x = pos.x;
			y += face->size->metrics.height >> 6; // Faktor 64 , da Glyphen ín 1/64 Abständen berechnet werden
			line++;
			continue;
		}
		FT_Load_Char(face, text[i], FT_LOAD_RENDER);

		FT_Bitmap& bitmap = face->glyph->bitmap;

		int xDelay = x - rowWidth[line] / 2;
		int yDelay = y - allheight / 2 + allheight / 8;
		if (maxRows > (int)bitmap.rows)
			yDelay++; // 1 extra pixel for smaller letter
		for (unsigned row = 0; row < bitmap.rows; ++row) {
			for (unsigned col = 0; col < bitmap.width; ++col) {
				int index = row * bitmap.width + col;
				BYTE pixelValue = bitmap.buffer[index]; // Wert des Pixels

				// Zeichnen Sie den Pixelwert auf den HDC bei den Koordinaten (x + col, y + row)
				// Je nach Framework und Zeichnungsfunktionen kann dies unterschiedlich sein
				if (pixelValue > 0) {
					int xKoord = xDelay + col;
					int yKoord = yDelay + row;
					if (xKoord < MainAreaWidth && yKoord < MainAreaHeight)
						SetPixel(hDC, xKoord, yKoord, RGB(pixelValue, pixelValue, pixelValue));

				}
			}
		}

		x += face->glyph->advance.x >> 6;
	}


	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}

CString CPictures::GetText(CItem* item) {
	CItem::ItemType typ = item->getItemType();
	if (typ == CItem::ItemType::MiscItem) {
		return ((CMiscellaneous*)item)->GetName();
	}
	else if (typ == CItem::ItemType::WeaponItem) {
		return ((CWeapon*)item)->GetName();
	}
	else if (typ == CItem::ItemType::ClothItem) {
		return ((CCloth*)item)->GetName();
	}
	else if (typ == CItem::ItemType::PotionItem) {
		return ((CPotion*)item)->GetName();
	}
	else if (typ == CItem::ItemType::ScrollItem) {
		return ((CScroll*)item)->GetName();
	}
	else if (typ == CItem::ItemType::ContainerItem) {
		return ((CContainer*)item)->GetName();
	}
	assert(false);
	return "UNKNOWN";
}


CBitmap* CPictures::GetChampions() { 
	return m_pChampionPortraits->GetChampions(); 
}

CPoint CPictures::GetKoords(int heroId) { 
	return m_pChampionPortraits->GetKoords(heroId); 
}
