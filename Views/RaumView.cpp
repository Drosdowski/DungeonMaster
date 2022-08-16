// RaumView.cpp : implementation file
//


#include "stdafx.h"
#include <deque>
#include <typeinfo>
#include "..\CalculationHelper/CHelpfulValues.h"
#include "..\CalculationHelper/ZoomBlt.h"
#include "DmDoc.h"
#include "Feld.h"
#include "Items/Item.h"
#include "Items/CMiscellaneous.h"
#include "Items/Cloth.h"
#include "Items/Weapon.h"
#include "Items/CActuator.h"
#include "Items\MagicMissile.h"
#include "RaumView.h"
#include "XMLParser\CDungeonMap.h"
#include "XMLParser\ItemInfos.h"
#include "XMLParser\AttackInfos.h"
#include "SpecialTile/CStairs.h"
#include "SpecialTile/CPit.h"
#include "SpecialTile/CTeleporter.h"
#include "Items\FloorDecoration.h"
#include "Items\WallDecoration.h"
#include "Pictures\CPictures.h"
#include "Pictures\CDoorPic.h"
#include "Pictures\CWallPic.h"
#include "Pictures/CStairsPic.h"
#include "Pictures/CPitPic.h"
#include "Pictures/CTeleportPic.h"
#include "Pictures/CPressurePadPic.h"
#include "Pictures/CFloorOrnatePic.h"
#include "Pictures\CWallDecoPic.h"
#include "Pictures\Creatures\CMonsterPic.h"
#include "Pictures\Items3D\CItem3DPic.h"
#include "Pictures\MagicMissilePic.h"
#include "Mobs\Monster.h"
#include "Mobs\MobGroups\GrpMonster.h"
#include "Mobs\MobGroups\GrpHeld.h"
#include <cassert>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRaumView


CRaumView::CRaumView()
{
	wallXFactor[0] = -2;
	wallXFactor[1] = 2;
	wallXFactor[2] = -1;
	wallXFactor[3] = 1;
	wallXFactor[4] = 0;

	m_bMirror = true;

	m_values = new CHelpfulValues();
	m_pMap = NULL;
	m_pItemInfos = NULL;
	m_pAttackInfos = NULL;
	m_pMonsterInfos = NULL;
	m_pDoc = NULL;
	m_pDoorPic = NULL;
	m_pWallPic = NULL;
	m_pStairsPic = NULL;
	m_pPitPic = NULL;
	m_pPressurePadPic = NULL;
	m_pTeleportPic = NULL;
	m_pOrnatePic = NULL;
	m_pPictures = NULL;
	m_pWallDecoPic = NULL;
	m_pMonsterPic = NULL;
	m_pItem3DPic = NULL;
	m_pMagicMissilePic = NULL;
}

CRaumView::~CRaumView()
{
	delete m_pItemInfos;
	delete m_pAttackInfos;
	delete m_pMonsterInfos;
	delete m_values;
	delete m_pDoorPic;
	delete m_pStairsPic;
	delete m_pPitPic;
	delete m_pWallPic;
	delete m_pPressurePadPic;
	delete m_pTeleportPic;
	delete m_pOrnatePic;
	delete m_pWallDecoPic;
	delete m_pMonsterPic;
	delete m_pItem3DPic;
	delete m_pMagicMissilePic;
	delete m_pMap;
}

/////////////////////////////////////////////////////////////////////////////
// CRaumView message handlers

void CRaumView::DrawFrame(CDC* pDC, CDC* cdc, int xxx, int ebene, bool left) {
	BITMAP bmpInfo;
	CBitmap* bmp = m_pDoorPic->GetDoorFramePic(ebene, left);
	if (bmp) {
		CPoint pos = m_pDoorPic->GetDoorFramePos(xxx, ebene, left, m_pWallPic->GetWallPos(xxx, ebene));
		if (pos != CPoint(0, 0))
		{
			cdc->SelectObject(bmp);
			bmp->GetBitmap(&bmpInfo);
			pDC->TransparentBlt(pos.x, pos.y, bmpInfo.bmWidth * 2, bmpInfo.bmHeight * 2, cdc, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, TRANS_ORA);
		}
	}
}

void CRaumView::DrawSquarePressurePad(CDC* pDC, CDC* cdc, int xxx, int ebene, CActuator* pActuator) {
	BITMAP bmpInfo;
	CBitmap* bmp = m_pPressurePadPic->GetPressurePadPic(xxx, ebene);
	if (bmp) {
		CPoint floorMiddlePos = m_pPressurePadPic->GetPos(xxx, ebene);
		if (floorMiddlePos.x > 0 || floorMiddlePos.y > 0) {
			cdc->SelectObject(bmp);
			bmp->GetBitmap(&bmpInfo);
			pDC->TransparentBlt(floorMiddlePos.x - bmpInfo.bmWidth, floorMiddlePos.y - bmpInfo.bmHeight,
				bmpInfo.bmWidth * 2, bmpInfo.bmHeight * 2, cdc, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, TRANS_ORA);
		}
	}
}

void CRaumView::DrawTeleporter(CDC* pDC, CDC* cdc, int xxx, int ebene, CTeleporter* tele) {
	BITMAP bmpInfo;
	CBitmap* bmp = m_pTeleportPic->GetFrontPic();
	CBitmap* bmpWall = m_pWallPic->GetWallPic(xxx, ebene, false);
	if (bmp) {
		CPoint pos = m_pWallPic->GetWallPos(xxx, ebene);
		cdc->SelectObject(bmp);
		if (ebene == 0 && xxx == 4) {
			bmp->GetBitmap(&bmpInfo);
			pDC->TransparentBlt(pos.x, pos.y,
				MainAreaWidth, MainAreaHeight, cdc, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, TRANS_ORA);
		}
		else {
			bmpWall->GetBitmap(&bmpInfo);
			pDC->TransparentBlt(pos.x, pos.y,
				bmpInfo.bmWidth * 2, bmpInfo.bmHeight * 2, cdc, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, TRANS_ORA);
		}
	}
}

void CRaumView::DrawStairsSide(CDC* pDC, CDC* cdc, int xxx, int ebene, CStairs* pStairs)
{
	BITMAP bmpInfo;
	CPoint pos;
	CBitmap* bmp;
	if (pStairs == NULL) return;
	if (pStairs->GetType() == CStairs::UP) {
		bmp = m_pStairsPic->GetStairUpSidePic(xxx, ebene);
		pos = m_pStairsPic->GetStairsUpSidePos(xxx, ebene, m_pWallPic->GetWallPos(xxx, ebene));
	}
	else {
		bmp = m_pStairsPic->GetStairDownSidePic(xxx, ebene);
		pos = m_pStairsPic->GetStairsDownSidePos(xxx, ebene, m_pWallPic->GetWallPos(xxx, ebene));
	}
	if (bmp) {
		if (pos != CPoint(0, 0))
		{
			cdc->SelectObject(bmp);
			bmp->GetBitmap(&bmpInfo);
			pDC->TransparentBlt(pos.x, pos.y, bmpInfo.bmWidth * 2, bmpInfo.bmHeight * 2, cdc, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, TRANS_ORA);
		}
	}
}

void CRaumView::DrawFloorPit(CDC* pDC, CDC* cdc, int xxx, int ebene, CPit* pit) {
	BITMAP bmpPitInfo;
	if (pit) {
		CBitmap* pitBmp = NULL;
		CPit::PitType type = pit->GetType();
		if (type == CPit::PitType::Standard || type == CPit::PitType::Imaginary) {
			pitBmp = m_pPitPic->GetPitPic(ebene, xxx);
		}
		else {
			// Invisible Pit
			pitBmp = m_pPitPic->GetInvPitPic(ebene, xxx);
		}

		CPoint center = m_pPressurePadPic->GetPos(xxx, ebene);
		if (pitBmp && center.x > 0 && center.y > 0) {
			double faktor = m_pPictures->getFaktor(ebene);
			cdc->SelectObject(pitBmp);
			pitBmp->GetBitmap(&bmpPitInfo);
			int decoPosX = center.x - (int)(bmpPitInfo.bmWidth * faktor);
			int decoPosY = center.y - (int)(bmpPitInfo.bmHeight * faktor);

			DrawInArea(decoPosX, decoPosY, bmpPitInfo.bmWidth, bmpPitInfo.bmHeight, faktor, pDC, cdc, TRANS_ORA);

		}
	}
}

void CRaumView::DrawCeilingPit(CDC* pDC, CDC* cdc, int xxx, int ebene, CPit* pit) {
	BITMAP bmpPitInfo;
	if (pit) {
		CBitmap* pitBmp = m_pPitPic->GetPitCeilingPic(ebene, xxx);
		CPit::PitType type = pit->GetType();

		CPoint center = m_pPressurePadPic->GetCeilingPos(xxx, ebene);
		if (pitBmp && center.x > 0 && center.y > 0) {
			double faktor = m_pPictures->getFaktor(ebene);
			cdc->SelectObject(pitBmp);
			pitBmp->GetBitmap(&bmpPitInfo);
			int decoPosX = center.x - (int)(bmpPitInfo.bmWidth * faktor);
			int decoPosY = center.y - (int)(bmpPitInfo.bmHeight * faktor);

			DrawInArea(decoPosX, decoPosY, bmpPitInfo.bmWidth, bmpPitInfo.bmHeight, faktor, pDC, cdc, TRANS_ORA);

		}
	}
}

void CRaumView::DrawStairsFront(CDC* pDC, CDC* cdc, int xxx, int ebene, CStairs* pStairs)
{
	BITMAP bmpInfo;
	CPoint pos;
	CBitmap* bmp;
	if (pStairs == NULL) return;

	if (pStairs->GetType() == CStairs::UP) {
		bmp = m_pStairsPic->GetStairUpFrontPic(xxx, ebene);
		pos = m_pStairsPic->GetStairsUpFrontPos(xxx, ebene, m_pWallPic->GetWallPos(xxx, ebene));
	}
	else {
		bmp = m_pStairsPic->GetStairDownFrontPic(xxx, ebene);
		pos = m_pStairsPic->GetStairsDownFrontPos(xxx, ebene, m_pWallPic->GetWallPos(xxx, ebene));
	}
	if (bmp) {
		if (pos != CPoint(0, 0))
		{
			cdc->SelectObject(bmp);
			bmp->GetBitmap(&bmpInfo);
			pDC->TransparentBlt(pos.x, pos.y, bmpInfo.bmWidth * 2, bmpInfo.bmHeight * 2, cdc, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, TRANS_ORA);
		}
	}

}


void CRaumView::DrawDoor(CDC* pDC, CDC* cdc, int xxx, int ebene, COMPASS_DIRECTION richt, CDoor* pDoor) {
	BITMAP bmpInfo;

	int xx = wallXFactor[xxx];

	CPoint wallPos = m_pWallPic->GetWallPos(xxx, ebene);

	bool doorVisible = pDoor->Visible(richt);
	if (doorVisible && ebene > 0)
	{
		CBitmap* bmp = m_pDoorPic->GetDoorTopPic(ebene);
		if (bmp) {
			cdc->SelectObject(bmp);
			CPoint pos = m_pDoorPic->GetDoorTopPos(xxx, ebene, wallPos);
			bmp->GetBitmap(&bmpInfo);

			DrawInArea(pos.x, pos.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 1, pDC, cdc, TRANS_ORA);
		}
		DrawFrame(pDC, cdc, xxx, ebene, true); // left Frame
		DrawFrame(pDC, cdc, xxx, ebene, false); // right Frame
		bmp = m_pDoorPic->GetDoorFrontPic(pDoor->getType(), ebene);
		if (bmp) {
			cdc->SelectObject(bmp);
			CPoint pos = m_pDoorPic->GetDoorFrontPos(xxx, ebene, wallPos);
			bmp->GetBitmap(&bmpInfo);
			if (pos.x != 0 || pos.y != 0) {
				int reducedWidth = min(bmpInfo.bmWidth, (MainAreaWidth - pos.x) / 2);
				int reducedHeight = bmpInfo.bmHeight - pDoor->getDoorBottomHeight();
				pDC->TransparentBlt(pos.x, pos.y, reducedWidth * 2, reducedHeight * 2, cdc, 0, pDoor->getDoorBottomHeight(), reducedWidth, reducedHeight, TRANS_ORA);
				if (pDoor->hasButton()) {
					double faktor = m_pPictures->getFaktor(ebene);

					CBitmap* bmpButton = m_pDoorPic->GetButtonPic(ebene);
					cdc->SelectObject(bmpButton);
					CPoint posButton = m_pDoorPic->GetButtonPos(xxx, ebene, m_pWallPic->GetWallPos(xxx, ebene));
					if (posButton != CPoint(0, 0))
						pDC->TransparentBlt(posButton.x, posButton.y, (int)(16 * 2 * faktor), (int)(9 * 2 * faktor), cdc, 0, 0, 16, 9, TRANS_ORA);

				}
			}
		}
	}
	else if (!doorVisible && (ebene == 0) && (xx == 0)) {
		// innenrahmen!
		CBitmap* bmp = m_pDoorPic->GetDoorFrontPic(0, ebene);
		if (bmp) {
			cdc->SelectObject(bmp);
			CPoint pos = m_pDoorPic->GetDoorFrontPos(xxx, ebene, wallPos);
			bmp->GetBitmap(&bmpInfo);
			DrawInArea(pos.x, pos.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 1, pDC, cdc, TRANS_ORA);

		}
	}


}

void CRaumView::DrawWall(CDC* pDC, CDC* cdc, int xxx, int ebene, COMPASS_DIRECTION richt, CField* pField) {
	BITMAP bmpDecoInfo;
	BITMAP bmpInfo;

	CBitmap* bmp = m_pWallPic->GetWallPic(xxx, ebene, m_bMirror);
	CBitmap* bmpDecoFront = NULL;
	CBitmap* bmpDecoSide = NULL;
	int xx = wallXFactor[xxx];

	COMPASS_DIRECTION richtOppo = (COMPASS_DIRECTION)CHelpfulValues::OppositeDirection(richt);
	std::deque<CActuator*> actuatorsFront = pField->GetActuator(richtOppo);
	WallDecorationType graphicTypeFront = None;
	if (!actuatorsFront.empty()) {
		int graphicId = actuatorsFront.back()->GetGraphic();
		graphicTypeFront = m_pMap->GetWallDecorationType(pField->HolePos().z, graphicId);
	}
	else {
		CWallDecoration* pWallDeco = pField->GetWallDeco(richtOppo);
		if (pWallDeco) {
			graphicTypeFront = pWallDeco->GetDecoType();
		}
	}
	if (graphicTypeFront != None)
		bmpDecoFront = m_pWallDecoPic->GetPicFront(graphicTypeFront);


	std::deque<CActuator*> actuatorsSide;
	COMPASS_DIRECTION richtSide;
	if (xx > 0)
	{
		richtSide = (COMPASS_DIRECTION)((richt + 3) % 4);
	}
	else if (xx < 0) {
		richtSide = (COMPASS_DIRECTION)((richt + 1) % 4);
	}
	if (xx != 0)
		actuatorsSide = pField->GetActuator(richtSide);

	WallDecorationType graphicTypeSide = None;
	if (!actuatorsSide.empty()) {
		int graphicId = actuatorsSide.back()->GetGraphic();
		graphicTypeSide = m_pMap->GetWallDecorationType(pField->HolePos().z, graphicId);
	}
	else if (xx != 0) {
		CWallDecoration* pWallDeco = pField->GetWallDeco(richtSide);
		if (pWallDeco) {
			graphicTypeSide = pWallDeco->GetDecoType();
		}
	}
	if (graphicTypeSide != None)
		bmpDecoSide = m_pWallDecoPic->GetPicSide(graphicTypeSide, (xx < 0));

	bool isBigContainer;

	cdc->SelectObject(bmp);
	CPoint posWall = m_pWallPic->GetWallPos(xxx, ebene);
	double faktor = m_pPictures->getFaktor(ebene);

	bmp->GetBitmap(&bmpInfo);

	pDC->TransparentBlt(posWall.x, posWall.y, bmpInfo.bmWidth * 2, bmpInfo.bmHeight * 2, cdc, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, TRANS_VIO);
	//CZoomBlt::DrawFullTrans(pDC, cdc, posWall.x, posWall.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, TRANS_VIO);

	// Deko auf FRONT Wand zeichnen
	if (bmpDecoFront)
	{
		if (((xxx == 4) && (ebene == 1)) ||
			((xxx > 1) && (ebene == 2)) ||
			(ebene == 3)) {
			CPoint centerFrontWall;
			if (m_pWallDecoPic->DrawNearFloor(graphicTypeFront))
				centerFrontWall = m_pWallPic->GetBottomCenterFromFrontWall(xxx, ebene);
			else
				centerFrontWall = m_pWallPic->GetCenterFromFrontWall(xxx, ebene);
			if (bmpDecoFront && centerFrontWall.x > 0 && centerFrontWall.y > 0) {
				cdc->SelectObject(bmpDecoFront);
				bmpDecoFront->GetBitmap(&bmpDecoInfo);
				int decoPosX = posWall.x + centerFrontWall.x - (int)(bmpDecoInfo.bmWidth * faktor);
				int decoPosY = posWall.y + centerFrontWall.y - (int)(bmpDecoInfo.bmHeight * faktor) / 2;
				isBigContainer = ((graphicTypeFront == SquareAlcove ||
					graphicTypeFront == ArchedAlcove ||
					graphicTypeFront == ViAltar ||
					graphicTypeFront == Fountain ));

				if (!isBigContainer)
					decoPosY -= (int)(bmpDecoInfo.bmHeight * faktor) / 2;

				DrawInArea(decoPosX, decoPosY, bmpDecoInfo.bmWidth, bmpDecoInfo.bmHeight, faktor, pDC, cdc, TRANS_ORA);

				if (isBigContainer) {
					// icons rein malen!
					std::deque<CItem*> pile = pField->GetItem((SUBPOS_ABSOLUTE)0);
					if (pile.size() > 0) {
						COMPASS_DIRECTION heroDir = m_pMap->GetHeroes()->GetDirection();
						DrawPile(pDC, cdc, xxx, ebene, MIDDLE, heroDir, pile);
					}
				}
			}
		}

	}
	// Deko auf SIDE Wand zeichnen
	if (bmpDecoSide)
	{
		if (ebene > 0 && xxx < 4) {

			CPoint centerSideWall;
			if (m_pWallDecoPic->DrawNearFloor(graphicTypeSide))
				centerSideWall = m_pWallPic->GetBottomCenterFromSideWall(xxx, ebene);
			else
				centerSideWall = m_pWallPic->GetCenterFromSideWall(xxx, ebene);
			if (centerSideWall.x > 0 && centerSideWall.y > 0) {
				bmpDecoSide->GetBitmap(&bmpDecoInfo);
				cdc->SelectObject(bmpDecoSide);
				int decoPosX = posWall.x + centerSideWall.x; // die Mitte für die linke Seite ist links im Bild, also nix abziehen
				if (xx > 0) {
					decoPosX -= (int)(bmpDecoInfo.bmWidth * 2 * faktor);
					decoPosX = max(decoPosX, posWall.x);
				}
				else
					decoPosX = max(0, decoPosX - (int)(bmpDecoInfo.bmWidth * faktor));
				int decoPosY = (int)(posWall.y + centerSideWall.y - bmpDecoInfo.bmHeight * faktor);
				isBigContainer = ((graphicTypeSide == SquareAlcove ||
					graphicTypeSide == ArchedAlcove ||
					graphicTypeSide == ViAltar ||
					graphicTypeSide == Fountain));
				if (isBigContainer)
					decoPosY += (int)(bmpDecoInfo.bmHeight * faktor / 2);
				DrawInArea(decoPosX, decoPosY, bmpDecoInfo.bmWidth, bmpDecoInfo.bmHeight, faktor, pDC, cdc, TRANS_ORA);
			}

		}
	}
}

void CRaumView::DrawMonsterGroup(CDC* pDC, CDC* cdc, int xxx, int ebene, COMPASS_DIRECTION richt, CField* pField) {
	CGrpMonster* pGrpMon = (CGrpMonster*)pField->GetMonsterGroup();
	if (pGrpMon)
	{
		DrawMonster(pDC, cdc, xxx, ebene, richt, pGrpMon->GetMonsterByRelSubPos(LINKSFRONT, richt));
		DrawMonster(pDC, cdc, xxx, ebene, richt, pGrpMon->GetMonsterByRelSubPos(RECHTSFRONT, richt));
		DrawMonster(pDC, cdc, xxx, ebene, richt, pGrpMon->GetMonsterByRelSubPos(LINKSBACK, richt));
		DrawMonster(pDC, cdc, xxx, ebene, richt, pGrpMon->GetMonsterByRelSubPos(RECHTSBACK, richt));
	}
}

void CRaumView::DrawMonster(CDC* pDC, CDC* cdc, int xxx, int ebene, COMPASS_DIRECTION richt, CMonster* pMonster) {
	if (pMonster && pMonster->isAlive()) // todo staubwolke hier berücksichtigen
	{
		CBitmap* bmp = m_pMonsterPic->GetBitmap(pMonster, richt);
		if (bmp == NULL) return; // todo passiert, wenn Monster nicht da sind
		BITMAP bmpInfo, bmpInfo2;

		//get original size of bitmap
		bmp->GetBitmap(&bmpInfo);
		double faktor = m_pPictures->getFaktor(ebene);
		// monster pos an wallpos orientieren
		CPoint p = m_pWallPic->GetWallPos(xxx, ebene);
		CBitmap* bmpWall = m_pWallPic->GetWallPic(xxx, ebene, false);
		bmpWall->GetBitmap(&bmpInfo2);
		p.x += bmpInfo2.bmWidth ;
		p.y += bmpInfo2.bmHeight * 2; // = untere Kante des Monsters!
		p.x = p.x - (int)(bmpInfo.bmWidth * faktor);
		p.y = p.y - (int)(bmpInfo.bmHeight * faktor * 2);

		SUBPOS subPos = CHelpfulValues::GetRelativeSubPosPassive(pMonster->HoleSubPosition(), richt);
		CPoint pos = CHelpfulValues::CalcSubPosition(p, subPos, faktor);

		cdc->SelectObject(bmp);
		DrawInArea(pos.x, pos.y, bmpInfo.bmWidth, bmpInfo.bmHeight, faktor, pDC, cdc, pMonster->transCol);
	}
}


void test(CDC* pDC, int x, int y) {
	y = y - 55;
	pDC->Ellipse(x - 5, y - 5, x + 5, y + 5);
}

void CRaumView::DrawOnFloor(CDC* pDC, CDC* cdc, int xxx, int ebene, CField* pField) {
	BITMAP bmpDecoInfo;

	std::deque<CActuator*> actuators = pField->GetActuator((COMPASS_DIRECTION)0);  // Boden hat immer POsition 0.
	for (CActuator* actuator : actuators) {
		if (actuator->GetType() == 3) {
			DrawSquarePressurePad(pDC, cdc, xxx, ebene, actuator);
		}
	}

	CFloorDecoration* floorDeco = pField->GetFloorDeco();
	CBitmap* decoBmp = NULL;
	if (floorDeco)
	{
		if (floorDeco->GetDecoType() == FloorMoss) {
			decoBmp = m_pOrnatePic->GetMossPic(ebene, xxx);
		}
		else if (floorDeco->GetDecoType() == FloorPuddle) {
			decoBmp = m_pOrnatePic->GetPuddlePic(ebene, xxx);
		}
		CPoint center = m_pPressurePadPic->GetPos(xxx, ebene);
		if (decoBmp && center.x > 0 && center.y > 0) {
			double faktor = m_pPictures->getFaktor(ebene);
			cdc->SelectObject(decoBmp);
			decoBmp->GetBitmap(&bmpDecoInfo);
			int decoPosX = center.x - (int)(bmpDecoInfo.bmWidth * faktor);
			int decoPosY = center.y - (int)(bmpDecoInfo.bmHeight * faktor);

			DrawInArea(decoPosX, decoPosY, bmpDecoInfo.bmWidth, bmpDecoInfo.bmHeight, faktor, pDC, cdc, TRANS_ORA);
		}
	}

}

void CRaumView::DrawPile(CDC* pDC, CDC* cdc, int xxx, int ebene, SUBPOS_ABSOLUTE itemSubPos, COMPASS_DIRECTION heroDir, std::deque<CItem*> pile) {
	int xx = wallXFactor[xxx]; // 0,1,2,3,4 => -2,2,-1,1,0
	CBitmap* bmp;
	// TODO - besser als "nur oberstes Malen... "
	CItem* item = pile.back();	
	CItem::ItemType typ = item->getItemType();
	if (typ == CItem::ItemType::MiscItem) {
		bmp = GetMiscBitmap((CMiscellaneous*)item);
	}
	else if (typ == CItem::ItemType::WeaponItem) {
		bmp = GetWeaponBitmap((CWeapon*)item, item->IsFlying());
	}
	else if (typ == CItem::ItemType::ClothItem) {
		bmp = GetClothBitmap((CCloth*)item, item->IsFlying());
	}
	if (bmp) {
		BITMAP bmpInfo;
		bmp->GetBitmap(&bmpInfo);
		double faktor = m_pPictures->getFaktor(ebene);

		CPoint floorMiddlePos = m_pItem3DPic->GetFloorMiddle(xxx, ebene);
		if (floorMiddlePos.x > 0 || floorMiddlePos.y > 0) {
			SUBPOS subPos = CHelpfulValues::GetRelativeSubPosPassive(itemSubPos, heroDir); // todo subpos angleichen
			if (ebene > 0 || subPos == LINKSFRONT || subPos == RECHTSFRONT)
			{
				if (subPos == LINKSFRONT || subPos == RECHTSFRONT)
				{
					faktor = m_pPictures->getFaktor(ebene + 1);
				}
				CPoint pos = CHelpfulValues::CalcRelSubFloorPosition(bmpInfo, floorMiddlePos, subPos, faktor, xx, ebene);
				if (item->IsFlying() && pos.y != 0) {
					pos.y = 250 - pos.y / 2;
				}
				cdc->SelectObject(bmp);
				DrawInArea(pos.x, pos.y, bmpInfo.bmWidth, bmpInfo.bmHeight, faktor, pDC, cdc, TRANS_ORA);
			}
		}

	}
}

void CRaumView::DrawMagicMissile(CDC* pDC, CDC* cdc, int xxx, int ebene, SUBPOS_ABSOLUTE itemSubPos, COMPASS_DIRECTION heroDir, std::deque<CMagicMissile*> magicMissiles) {
	int xx = wallXFactor[xxx]; // 0,1,2,3,4 => -2,2,-1,1,0
	CBitmap* bmp;	
	CMagicMissile* magicMissile = magicMissiles.back();
	
	bmp = GetMagicMissileBitmap(magicMissile->GetType(), magicMissile->IsExploding());
	if (bmp) {
		// todo refaktorieren mit Throw... viel DOppelcode!
		// todo exploding in mitte?
		BITMAP bmpInfo;
		bmp->GetBitmap(&bmpInfo);
		double faktor = m_pPictures->getFaktor(ebene);
		
		CPoint floorMiddlePos = m_pItem3DPic->GetFloorMiddle(xxx, ebene);
		if (floorMiddlePos.x > 0 || floorMiddlePos.y > 0) { // todo refaktor: inView()
			SUBPOS subPos = CHelpfulValues::GetRelativeSubPosPassive(itemSubPos, heroDir); // todo subpos angleichen
			if (ebene > 0 || subPos == LINKSFRONT || subPos == RECHTSFRONT)
			{
				if (subPos == LINKSFRONT || subPos == RECHTSFRONT)
				{
					faktor = m_pPictures->getFaktor(ebene + 1);
				}
				CPoint pos = CHelpfulValues::CalcRelSubFloorPosition(bmpInfo, floorMiddlePos, subPos, faktor, xx, ebene);
				
				for (int aebene = 0; aebene <= 4; aebene++) {
					CPoint xPos = CHelpfulValues::CalcRelSubFloorPosition(bmpInfo, m_pItem3DPic->GetFloorMiddle(xxx, aebene), subPos, faktor, xx, aebene);
					pDC->Ellipse(xPos.x - 3, xPos.y - 3, xPos.x + 3, xPos.y + 3);
				}
				
				if (!magicMissile->IsExploding()) {
					if (pos.y != 0) {
						pos.y = 250 - pos.y / 2;
					}
				}
				else {
					CPoint posWall = m_pWallPic->GetWallPos(xxx, ebene);
					CPoint posMitte = m_pWallPic->GetCenterFromFrontWall(xxx, ebene);	
					pos.x = posWall.x + posMitte.x - bmpInfo.bmWidth * faktor;
					pos.y = posWall.y + posMitte.y - bmpInfo.bmHeight * faktor;
				}
				cdc->SelectObject(bmp);
				DrawInArea(pos.x, pos.y, bmpInfo.bmWidth, bmpInfo.bmHeight, faktor, pDC, cdc, TRANS_ORA);
			}
		}

	}
}

CBitmap* CRaumView::GetMagicMissileBitmap(CMagicMissile::MagicMissileType type, bool exploding) {
	if (type == CMagicMissile::MagicMissileType::AntiMagic)
		return m_pMagicMissilePic->GetAntiMaterial(exploding);
	else if (type == CMagicMissile::MagicMissileType::Fireball)
		return m_pMagicMissilePic->GetFireball(exploding);
	else if (type == CMagicMissile::MagicMissileType::Poison)
		return m_pMagicMissilePic->GetPoison(exploding);
	else if (type == CMagicMissile::MagicMissileType::PoisonBlob)
		return m_pMagicMissilePic->GetPoisonBlob(exploding);
	return NULL;
}

CBitmap* CRaumView::GetMiscBitmap(CMiscellaneous* misc) {
	CBitmap* bmp;
	if (misc->GetType() == CMiscellaneousAttributes::MiscItemType::Apple) // TODO Logik auslagern!
		bmp = m_pItem3DPic->GetApple();
	else if (misc->GetType() == CMiscellaneousAttributes::MiscItemType::Bread)
		bmp = m_pItem3DPic->GetBread();
	else if (misc->GetType() == CMiscellaneousAttributes::MiscItemType::Corn)
		bmp = m_pItem3DPic->GetCorn();
	else if (misc->GetType() == CMiscellaneousAttributes::MiscItemType::Cheese)
		bmp = m_pItem3DPic->GetCheese();
	else if (misc->GetType() == CMiscellaneousAttributes::MiscItemType::Compass)
		bmp = m_pItem3DPic->GetCompass();
	else if (misc->GetType() >= CMiscellaneousAttributes::MiscItemType::IronKey &&
		misc->GetType() <= CMiscellaneousAttributes::MiscItemType::SkeletonKey)
		bmp = m_pItem3DPic->GetIronKey();
	else if (misc->GetType() >= CMiscellaneousAttributes::MiscItemType::GoldKey &&
		misc->GetType() <= CMiscellaneousAttributes::MiscItemType::MasterKey)
		bmp = m_pItem3DPic->GetGoldKey();
	else if (misc->GetType() == CMiscellaneousAttributes::MiscItemType::Water)
		if (misc->GetSubtype() > 0)
			bmp = m_pItem3DPic->GetWaterskin(1);
		else
			bmp = m_pItem3DPic->GetWaterskin(0);
	else if (misc->GetType() == CMiscellaneousAttributes::MiscItemType::ScreamerSlice)
		bmp = m_pItem3DPic->GetScreamerSlice();
	else if (misc->GetType() == CMiscellaneousAttributes::MiscItemType::WormRound)
		bmp = m_pItem3DPic->GetWormRound();
	else
		bmp = NULL;

	return bmp;
}

CBitmap* CRaumView::GetClothBitmap(CCloth* cloth, bool inAir) {
	CBitmap* bmp;
	if (cloth->GetType() == CClothAttributes::ClothType::LeatherBoots)
		bmp = m_pItem3DPic->GetLeatherBoots();
	else if (cloth->GetType() == CClothAttributes::ClothType::ElvenDoublet ||
		cloth->GetType() == CClothAttributes::ClothType::ElvenHuke)
		bmp = m_pItem3DPic->GetGreenCloth();
	else if (cloth->GetType() == CClothAttributes::ClothType::FineRobeBody ||
		cloth->GetType() == CClothAttributes::ClothType::FineRobeLegs)
		bmp = m_pItem3DPic->GetWhiteCloth();
	else
		bmp = NULL;

	return bmp;
}

CBitmap* CRaumView::GetWeaponBitmap(CWeapon* weapon, bool inAir) {
	CBitmap* bmp;
	if (weapon->GetType() >= CWeaponAttributes::WeaponType::Falchion &&
		weapon->GetType() <= CWeaponAttributes::WeaponType::DiamondEdge ||
		weapon->GetType() == CWeaponAttributes::WeaponType::TheInquisitor)
		bmp = m_pItem3DPic->GetSword(inAir);
	else if (weapon->GetType() == CWeaponAttributes::WeaponType::Axe ||
		weapon->GetType() == CWeaponAttributes::WeaponType::Hardcleave)
		bmp = m_pItem3DPic->GetAxe(inAir);
	else if (weapon->GetType() == CWeaponAttributes::WeaponType::Dagger)
		bmp = m_pItem3DPic->GetDagger(inAir);
	else if (weapon->GetType() == CWeaponAttributes::WeaponType::Club)
		bmp = m_pItem3DPic->GetClub(inAir);
	else if (weapon->GetType() == CWeaponAttributes::WeaponType::StoneClub)
		bmp = m_pItem3DPic->GetStoneClub(inAir);
	else if (weapon->GetType() == CWeaponAttributes::WeaponType::Arrow)
		bmp = m_pItem3DPic->GetArrow(inAir);
	else if (weapon->GetType() == CWeaponAttributes::WeaponType::Slayer)
		bmp = m_pItem3DPic->GetSlayer(inAir);
	else if (weapon->GetType() == CWeaponAttributes::WeaponType::ThrowingStar)
		bmp = m_pItem3DPic->GetThrowingStar(inAir);
	else if (weapon->GetType() == CWeaponAttributes::WeaponType::PoisonDart)
		bmp = m_pItem3DPic->GetPoisonDart(inAir);
	else if (weapon->GetType() == CWeaponAttributes::WeaponType::Torch)
		bmp = m_pItem3DPic->GetTorch();
	else
		bmp = NULL;

	return bmp;
}


void CRaumView::DrawInArea(int x, int y, int w, int h, double faktor, CDC* pDC, CDC* cdc, COLORREF col) {
	int realWidth = w * 2 * faktor;
	int realHeight = h * 2 * faktor;
	int rechterRand = realWidth + x;
	int reducedWidth = realWidth;
	if (rechterRand > MainAreaWidth)
	{
		int zuvielrechts = rechterRand - MainAreaWidth;
		reducedWidth -= (int)((zuvielrechts));
	}

	if (reducedWidth > 0)
	{
		pDC->TransparentBlt(x, y,
			reducedWidth, realHeight,
			cdc, 0, 0, w, h, col);
	}
}

void CRaumView::DrawActionAreaChoice(CDC* pDC, int weaponIndex) {
	
	m_pPictures->DrawActionAreaChoice(pDC, m_pItemInfos, weaponIndex);
}

void CRaumView::DrawActionAreaDamage(CDC* pDC, int dmg) {
	m_pPictures->DrawActionAreaDamage(pDC, dmg);
}


void CRaumView::RaumZeichnen(CDC* pDC)
{
	CDC compCdc;
	compCdc.CreateCompatibleDC(pDC);

	compCdc.SelectObject(m_pPictures->GetHintergrund());

	//CZoomBlt::DrawFullStd(pDC, &compCdc, 0, 64, MainAreaWidth, 336, 0, 0);
	pDC->BitBlt(0, 64, MainAreaWidth, 336, &compCdc, 0, 0, SRCCOPY);
	if (m_bMirror) {
		pDC->StretchBlt(0, 64, MainAreaWidth, 269, &compCdc, MainAreaWidth, 0, -MainAreaWidth, 269, SRCCOPY);
		//CZoomBlt::DrawFullStretch(pDC, &compCdc, 0, 64, MainAreaWidth, 269, MainAreaWidth, 0, -MainAreaWidth, 269 );
	}

	int x = m_pMap->GetHeroes()->GetVector().x;
	int y = m_pMap->GetHeroes()->GetVector().y;
	int z = m_pMap->GetHeroes()->GetVector().z;

	COMPASS_DIRECTION heroDir = m_pMap->GetHeroes()->GetDirection();
	int stx = m_values->m_stx[heroDir];
	int sty = m_values->m_sty[heroDir];

	for (int ebene = 3; ebene >= 0; ebene--)
	{
		for (int xxx = 0; xxx <= 4; xxx++)
		{
			int xx = wallXFactor[xxx]; // 0,1,2,3,4 => -2,2,-1,1,0
			if (ebene > 1 || xxx > 1)
			{ // nur für Ebene 2&3 sind Außenwerte -2 / 2 zu zeichnen - far left  & far right
				int addx = x + ebene * sty + xx * stx;
				int addy = y - ebene * stx + xx * sty;
				CField* pField = m_pMap->GetField(addx, addy, z);
				int fieldType = pField->HoleTyp();

				if (z > 0) {
					CField* pFieldAbove = m_pMap->GetField(addx, addy, z - 1);
					int fieldTypeAbove = pFieldAbove->HoleTyp();

					if (fieldTypeAbove == FeldTyp::PIT) {
						CPit* pit = pFieldAbove->HolePit();
						if (pit->GetType() != CPit::PitType::Invisible &&
							pit->GetState() == CPit::PitState::Opened) {
							DrawCeilingPit(pDC, &compCdc, xxx, ebene, pit);
						}
					}
				}

				if ((fieldType == FeldTyp::WALL || fieldType == FeldTyp::TRICKWALL) && ((ebene != 0) || (xx != 0)))
				{
					DrawWall(pDC, &compCdc, xxx, ebene, heroDir, pField);
				}
				else if (fieldType == FeldTyp::DOOR)
				{
					CDoor* pDoor = pField->HoleDoor();
					DrawDoor(pDC, &compCdc, xxx, ebene, heroDir, pDoor);
				}
				else if (fieldType == FeldTyp::STAIRS)
				{
					CStairs* pStairs = pField->HoleStairs();

					if (pStairs->Visible(heroDir)) {
						DrawStairsFront(pDC, &compCdc, xxx, ebene, pStairs);
					}
					else {
						DrawStairsSide(pDC, &compCdc, xxx, ebene, pStairs);
					}
				}
				else if (fieldType == FeldTyp::PIT) {
					CPit* pit = pField->HolePit();
					if (pit->GetType() != CPit::PitType::Invisible &&
						pit->GetState() == CPit::PitState::Opened) {
						DrawFloorPit(pDC, &compCdc, xxx, ebene, pit);
					}

				}
				else if (fieldType == FeldTyp::TELEPORT) {
					CTeleporter* tele = pField->HoleTeleporter();
					if (tele && tele->isVisible()) {
						DrawTeleporter(pDC, &compCdc, xxx, ebene, tele);
					}
				}
				else if (fieldType == FeldTyp::EMPTY) {
					// Platten, Pfützen, Fussabdrücke, ...
					DrawOnFloor(pDC, &compCdc, xxx, ebene, pField);
				}

				if (fieldType != FeldTyp::WALL) {
					for (int pos = 0; pos < 4; pos++)
					{
						std::deque<CItem*> pile = pField->GetItem((SUBPOS_ABSOLUTE)pos);
						if (pile.size() > 0) {
							DrawPile(pDC, &compCdc, xxx, ebene, (SUBPOS_ABSOLUTE)pos, heroDir, pile);
						}
						std::deque<CMagicMissile*> magicMissiles = pField->GetMagicMissile((SUBPOS_ABSOLUTE)pos);
						if (magicMissiles.size() > 0) {
							DrawMagicMissile(pDC, &compCdc, xxx, ebene, (SUBPOS_ABSOLUTE)pos, heroDir, magicMissiles);
						}
					}
					if (ebene > 0 && xxx > 1)
					{
						DrawMonsterGroup(pDC, &compCdc, xxx, ebene, heroDir, pField);
					}
				}
			}
		}
	}

	/* Reihenfolge:
	1  3  2
	4  6  5
	7  9  8
	10 12 11 */

	compCdc.DeleteDC();
}

CGrpMonster* CRaumView::GetMonsterGroup(VEKTOR pos) {
	CField* pField = m_pMap->GetField(pos);
	return pField->GetMonsterGroup();
}

VEKTOR CRaumView::Betrete(VEKTOR fromPos, VEKTOR toPos)
{
	CField* pField = m_pMap->GetField(toPos);
	FeldTyp iTyp = pField->HoleTyp();
	CGrpHeld* pGrpHelden = m_pMap->GetHeroes();
	if (iTyp == FeldTyp::WALL)
		return fromPos;
	else if (iTyp == FeldTyp::DOOR)
	{
		CDoor* pDoor = pField->HoleDoor();
		if (pDoor->getState() != CDoor::DoorState::OPEN)
			return fromPos;
	}
	else if (iTyp == FeldTyp::EMPTY) {
		CGrpMonster* pGrpMonster = pField->GetMonsterGroup();
		if (pGrpMonster) return fromPos;
	}
	else if (iTyp == FeldTyp::PIT) {
		CPit* pit = pField->HolePit();
		if (pit->GetState() == CPit::PitState::Opened) {
			toPos.z++;
			toPos.x += (m_pMap->GetOffset(fromPos.z).x - m_pMap->GetOffset(toPos.z).x);
			toPos.y += (m_pMap->GetOffset(fromPos.z).y - m_pMap->GetOffset(toPos.z).y);
			pGrpHelden->FallingDamage();
			// todo sound
		}
		return toPos;
	}
	else if (iTyp == FeldTyp::TELEPORT) {
		CTeleporter* tele = pField->HoleTeleporter();
		if (tele->getScope() == TeleporterAttributes::Scope::Items_Party ||
			tele->getScope() == TeleporterAttributes::Scope::All) {
			toPos = tele->getTargetField();
			if (tele->getRotationType() == TeleporterAttributes::RotationType::Absolute)
			{
				pGrpHelden->SetzeRichtung(tele->getTargetDirection());
				// todo sound
			}
			else
			{
				if (tele->getTargetDirection() == 90)
				{
					pGrpHelden->DrehenRelativ(RECHTS);
				}
				else if (tele->getTargetDirection() == 180) {
					pGrpHelden->DrehenRelativ(RECHTS);
					pGrpHelden->DrehenRelativ(RECHTS);
				}
				else if (tele->getTargetDirection() == 270) {
					pGrpHelden->DrehenRelativ(LINKS);
				}
			}
		}
	}
	else if (iTyp == FeldTyp::STAIRS) {
		CStairs* stairsBegin = pField->HoleStairs();
		if (stairsBegin->GetType() == CStairs::StairType::DOWN)
		{
			toPos.z++;
		}
		else {
			toPos.z--;
		}
		toPos.x += (m_pMap->GetOffset(fromPos.z).x - m_pMap->GetOffset(toPos.z).x);
		toPos.y += (m_pMap->GetOffset(fromPos.z).y - m_pMap->GetOffset(toPos.z).y);
		// neue Richtung: Blick auf das einzige EMPTY Feld neben Hero

		CStairs* stairsEnd = m_pMap->GetField(toPos)->HoleStairs();

		pGrpHelden->DrehenAbsolut(stairsEnd->StairExit());
	}
	return toPos;
}

void CRaumView::MoveMonsters(VEKTOR heroPos) {
	CField* field = m_pMap->GetField(heroPos);
	CGrpMonster* pGrpMon = field->GetMonsterGroup();
	if (pGrpMon)
	{
		if (!pGrpMon->Altern()) {
			// Gruppe ausgestorben!
			field->RemoveMonsterGroup();
		}
		else if (pGrpMon->AnyoneReady())
		{
			VEKTOR target = MonsterMoveOrAttack(pGrpMon);
			if (target.x != heroPos.x || target.y != heroPos.y) {
				CField* targetField = m_pMap->GetField(target);
				field->SetMonsterGroup(NULL);
				targetField->SetMonsterGroup(pGrpMon);
				pGrpMon->MoveDone(); 
			}
		}
	}
}

void CRaumView::MoveDoors(VEKTOR heroPos) {
	CField* field = m_pMap->GetField(heroPos);
	CDoor* pDoor = field->HoleDoor();
	if (pDoor) {
		if ((pDoor->getState() == CDoor::DoorState::OPENING) ||
			(pDoor->getState() == CDoor::DoorState::CLOSING))
		{
			pDoor->ContinueMoving();
		}
	}
}

void CRaumView::PrepareMoveObjects(VEKTOR heroPos) {
	CField* field = m_pMap->GetField(heroPos);
	// Flag setzen, Item muss sich ggf. noch bewegen
	for (int s = 0; s < 4; s++) {
		SUBPOS_ABSOLUTE posAbs = (SUBPOS_ABSOLUTE)s;
		std::deque<CItem*> pile = field->GetItem(posAbs);
		if (!pile.empty()) {
			CItem* topItem = pile.back();
			topItem->ResethasMoved();
		}
		std::deque<CMagicMissile*> magicMissiles = field->GetMagicMissile(posAbs);
		if (!magicMissiles.empty()) {
			CMagicMissile* topItem = magicMissiles.back();
			topItem->ResethasMoved();
		}
	}
}

void CRaumView::MoveMagicMissiles(VEKTOR heroPos) {
	CField* field = m_pMap->GetField(heroPos);
	// todo refaktorieren mit moveItems
	for (int s = 0; s < 4; s++) {
		SUBPOS_ABSOLUTE posAbs = (SUBPOS_ABSOLUTE)s;
		std::deque<CMagicMissile*> magicMissiles = field->GetMagicMissile(posAbs);
		if (!magicMissiles.empty()) {
			CMagicMissile* topMissile = magicMissiles.back(); // todo prüfen, reicht es, nur das oberste anzuschauen, gibt es > 1 fliegende Items je Feld
			if (!topMissile->HasMovedThisTick()) {
				SUBPOS_ABSOLUTE newPos = CHelpfulValues::FindNextSubposWithoutFieldChange(posAbs, topMissile->m_flyForce);
				if (topMissile->IsExploding() && newPos == posAbs) {
					if (topMissile->GetType() == CMagicMissile::MagicMissileType::Poison || topMissile->GetType() == CMagicMissile::MagicMissileType::Dust) {
						// Gift- und Staubwolke verschwinden langsam
						if (topMissile->GetStrength() > 1)
							topMissile->DecreaseStrength();
						else {
							field->TakeMissile(posAbs); // out of energy, gone
							delete topMissile;
						}
					}
					else {
						field->TakeMissile(posAbs);
						delete topMissile;
					}
				} else if (newPos == OUTSIDE) {
					// Feld verlassen
					CField* newField = m_pMap->GetField(heroPos.x + sign(topMissile->m_flyForce.x), heroPos.y + sign(topMissile->m_flyForce.y), heroPos.z);
					
					if (!newField->Blocked()) {
						CGrpMonster* grpHittedMonster = newField->GetMonsterGroup();
						if (grpHittedMonster) {
							grpHittedMonster->DoDamage(topMissile->GetStrength(), heroPos, true);
							topMissile->Explode();
						}
						else {
							// todo kann auch spieler treffen!
							topMissile = field->TakeMissile(posAbs);
							newField = ChangeFieldWithTeleporter(newField, posAbs);
							newField = ChangeFieldWithStairs(newField, topMissile, posAbs);
							// westlich von west ist ost => anders rum subpos suchen
							newPos = CHelpfulValues::FindNextSubposWithoutFieldChange(posAbs, VEKTOR{ -topMissile->m_flyForce.x, -topMissile->m_flyForce.y, 0 });

							newField->CastMissile(topMissile, newPos);
						}
					}
					else {
						topMissile->Explode();
					}	
				}
				else {
					topMissile = field->TakeMissile(posAbs);
					if (topMissile->IsFlying()) {
						topMissile->ReduceSpeed();
						field->CastMissile(topMissile, newPos);
					}
					else {
						delete topMissile;
					}
				}
			}
		}
	}

}


void CRaumView::MoveItems(VEKTOR heroPos) {
	CField* field = m_pMap->GetField(heroPos);

	for (int s = 0; s < 4; s++) {
		SUBPOS_ABSOLUTE posAbs = (SUBPOS_ABSOLUTE)s;
		std::deque<CItem*> pile = field->GetItem(posAbs);
		if (!pile.empty()) {
			CItem* topItem = pile.back(); // todo prüfen, reicht es, nur das oberste anzuschauen, gibt es > 1 fliegende Items je Feld
			if (topItem->IsFlying() && !topItem->HasMovedThisTick()) {
				// fliegendes Item gefunden
				SUBPOS_ABSOLUTE newPos = CHelpfulValues::FindNextSubposWithoutFieldChange(posAbs, topItem->m_flyForce);

				if (newPos == OUTSIDE) {
					// Feld verlassen
					CField* newField = m_pMap->GetField(heroPos.x + sign(topItem->m_flyForce.x), heroPos.y + sign(topItem->m_flyForce.y), heroPos.z);
					if (!newField->Blocked()) {
						topItem = field->TakeItem(posAbs);
						newField = ChangeFieldWithTeleporter(newField, posAbs);
						newField = ChangeFieldWithStairs(newField, topItem, posAbs);
						// westlich von west ist ost => anders rum subpos suchen
						if (topItem->IsFlying())
							newPos = CHelpfulValues::FindNextSubposWithoutFieldChange(posAbs, VEKTOR{ -topItem->m_flyForce.x, -topItem->m_flyForce.y, 0 });
						else
							newPos = posAbs;
						newField->PutItem(topItem, newPos);
					}
					else {
						// nicht bewegen, sondern stehen bleiben (unten)
						topItem->m_flyForce = { 0,0,0 };
					}
				}
				else {
					topItem = field->TakeItem(posAbs);
					topItem->ReduceSpeed();
					field->PutItem(topItem, newPos);
				}
			}
		}
	}
}

CField* CRaumView::ChangeFieldWithTeleporter(CField* pField, SUBPOS_ABSOLUTE& subPos) {
	CTeleporter* tp = pField->HoleTeleporter();

	if (tp) {
		// todo Teleport & items
		COMPASS_DIRECTION dir = tp->getTargetDirection();
		if (tp->getRotationType() == TeleporterAttributes::RotationType::Absolute) {
			switch (tp->getRotation()) {
			case 0:
				if (subPos == SOUTHWEST) subPos = NORTHWEST; break;
				if (subPos == SOUTHEAST) subPos = NORTHEAST; break;
			case 90:
				if (subPos == NORTHWEST) subPos = NORTHEAST; break;
				if (subPos == SOUTHWEST) subPos = SOUTHEAST; break;
			case 180:
				if (subPos == SOUTHWEST) subPos = NORTHWEST; break;
				if (subPos == SOUTHEAST) subPos = NORTHEAST; break;
			case 270:
				if (subPos == NORTHEAST) subPos = NORTHWEST; break;
				if (subPos == SOUTHEAST) subPos = SOUTHWEST; break;
			}
		}
		else { // relativ
			switch (tp->getRotation()) {
			case 0:
				break;
			case 90:
				subPos = CHelpfulValues::RightFrom(subPos); break;
			case 180:
				subPos = CHelpfulValues::RightFrom(CHelpfulValues::RightFrom(subPos)); break;
			case 270:
				subPos = CHelpfulValues::LeftFrom(subPos); break;
			}
		}
	}
	return pField;
}
CField* CRaumView::ChangeFieldWithStairs(CField* pField, CMovingObject* pItem, SUBPOS_ABSOLUTE& subPos) {
	CStairs* stair = pField->HoleStairs();
	if (stair) {
		// In Treppe: Flug zu Ende
		pItem->m_flyForce = { 0,0,0 };
		// Falls Treppe runter: Item fliegt runter!
		if (stair->GetType() == CStairs::StairType::DOWN) {
			VEKTOR oben = pField->HolePos();
			VEKTOR unten = { oben.x, oben.y, oben.z + 1 };

			unten.x += (m_pMap->GetOffset(oben.z).x - m_pMap->GetOffset(unten.z).x);
			unten.y += (m_pMap->GetOffset(oben.z).y - m_pMap->GetOffset(unten.z).y);
			pField = m_pMap->GetField(unten);
			CStairs* stairEnd = pField->HoleStairs();
			COMPASS_DIRECTION sourceDir = CHelpfulValues::OppositeDirection(stair->StairExit());
			COMPASS_DIRECTION targetDir = stairEnd->StairExit(); // N E S W
			if (sourceDir > targetDir) {
				for (int t = 0; t < (sourceDir - targetDir); t++)
					subPos = CHelpfulValues::LeftFrom(subPos);
			}
			else if (sourceDir > targetDir) {
				for (int t = 0; t < (targetDir - sourceDir); t++)
					subPos = CHelpfulValues::RightFrom(subPos);
			}
		}
	}
	return pField;
}


void CRaumView::MoveAnythingNearby() {
	VEKTOR held = m_pMap->GetHeroes()->GetPos();
	for (int i = max(held.x - 4, 0); i < min(held.x + 4, m_pMap->GetMaxWidth(held.z)); i++) {
		for (int j = max(held.y - 4, 0); j < min(held.y + 4, m_pMap->GetMaxHeight(held.z)); j++) {
			VEKTOR pos = { i, j, held.z };
			MoveMonsters(pos);
			MoveDoors(pos);
			PrepareMoveObjects(pos);
			MoveItems(pos);
			MoveMagicMissiles(pos);
		}
	}
}

void CRaumView::TriggerPassiveActuators(VEKTOR fieldPos, VEKTOR heroPos) {
	CField* field = m_pMap->GetField(fieldPos);
	std::deque<CActuator*> actuators = field->GetActuator((COMPASS_DIRECTION)0);
	for (CActuator* actuator : actuators) {
		TriggerPassiveActuator(heroPos, field, actuator);
	}
}

void CRaumView::TriggerPassiveActuator(VEKTOR heroPos, CField* field, CActuator* actuator) {
	bool criticalWeightBreached = field->CriticalWeightBreached(heroPos, actuator->GetCriticalWeigth()); // todo parameter optimieren?
	bool criticalWeightGone = field->CriticalWeightGone(heroPos, actuator->GetCriticalWeigth()); // todo parameter optimieren?

	if (criticalWeightBreached || criticalWeightGone) {
		switch (actuator->GetType()) {
		case 3:
			VEKTOR target = actuator->GetTarget();
			CActuator::ActionTypes type = actuator->GetActionType();
			// TODO: type auswerten!
			CField* pTargetField = m_pMap->GetField(target);
			CDoor* pDoor = pTargetField->HoleDoor(); // todo das kann nicht nur eine Tür treffen!
			switch (type)
			{
			case CActuator::Set:
				if (pDoor != NULL && criticalWeightBreached) {
					pDoor->Open();
				}
				break;
			case CActuator::Toggle:
				if (pDoor != NULL && criticalWeightBreached) {
					pDoor->Toggle();
				}
				break;
			case CActuator::Clear:
				if (pDoor != NULL && criticalWeightBreached) {
					pDoor->Close(); // TODO ???
				}
				break;
			case CActuator::Hold:
				if (pDoor != NULL && criticalWeightGone) {
					pDoor->Toggle(); // todo prüfen 
				}
			}
			break;
		}
	}

}

void CRaumView::TriggerActuatorsNearby() {
	VEKTOR held = m_pMap->GetHeroes()->GetPos();
	for (int i = max(held.x - 4, 0); i < min(held.x + 4, m_pMap->GetMaxWidth(held.z)); i++) {
		for (int j = max(held.y - 4, 0); j < min(held.y + 4, m_pMap->GetMaxHeight(held.z)); j++) {
			TriggerPassiveActuators(VEKTOR{ i, j, held.z }, held);
		}
	}
}

VEKTOR CRaumView::MonsterMoveOrAttack(CGrpMonster* pGrpMon) {
	// Prüfen: Held angreifbar? Erstmal nur Nahkampf!
	VEKTOR heroPos = m_pMap->GetHeroes()->GetPos();
	VEKTOR monPos = pGrpMon->GetPos();
	if (pGrpMon->GetPos().z != heroPos.z) return monPos; // Falsche Etage, nix tun!

	// Versuch, in Blickrichtung zu gehen, ggf. Angriff!
	VEKTOR targetPos = pGrpMon->HoleZielFeld(VORWAERTS);
	CField* targetField = m_pMap->GetField(targetPos);

	COMPASS_DIRECTION heroRicht = m_pMap->GetHeroes()->GetDirection();

	int xDist = monPos.x - heroPos.x;
	int yDist = monPos.y - heroPos.y;
	int absDist = abs(xDist) + abs(yDist);
	if (targetPos.x == heroPos.x && targetPos.y == heroPos.y) {
		CMonster* attackingMonster = pGrpMon->AttackHero(monPos, heroPos);
		if (attackingMonster)
		{
			m_pDoc->PlayDMSound("C:\\Source\\C++\\DM\\sound\\DMCSB-SoundEffect-Attack(Skeleton-AnimatedArmour-PartySlash).mp3");

			m_pMap->GetHeroes()->DamageFrom(attackingMonster, pGrpMon->GetVector(), false);
		}
		return monPos;
	}
	else {
		pGrpMon->EndAttack(); // Attacke ggf. beenden
	}
	if (pGrpMon->EveryoneReady()) {
		if (absDist == 1) {
			// Steht neben Held, falsch gedreht -> drehen!
			pGrpMon->TurnToHero(heroPos);
			return monPos;
		}
		// Nein: Bewege näher / drehe hin
		// todo: schlauer bewegungsalgorithmus!

		int targetDist = (abs(targetPos.x - heroPos.x) + abs(targetPos.y - heroPos.y));
		if ((targetPos.x != monPos.x || targetPos.y != monPos.y) &&
			(targetField->HoleTyp() == FeldTyp::EMPTY && targetField->GetMonsterGroup() == NULL) ||
			(targetField->HoleTyp() == FeldTyp::DOOR && targetField->GetMonsterGroup() == NULL)) { // TODO nur Open!
			// Feld vorhanden - Monster drauf?
			// TODO: Merge
			if (targetField->HoleTyp() == FeldTyp::DOOR) {
				CDoor* pDoor = targetField->HoleDoor();
				if (pDoor->getState() != CDoor::DoorState::OPEN)
					return monPos; // Tür im Weg
			}

			if (absDist > targetDist)
			{
				// Kommt näher => Move!

				pGrpMon->Laufen(targetPos);
				m_pDoc->PlayDMSound("C:\\Source\\C++\\DM\\sound\\DMCSB-SoundEffect-Move(Skeleton).mp3");

				return targetPos;
			}
			else {
				if (absDist < targetDist)
					pGrpMon->DrehenAbsolut(CHelpfulValues::OppositeDirection(heroRicht));
				// neues Ziel weiter weg -> drehen!
			}
		}
		else {
			if (absDist < targetDist)
				pGrpMon->DrehenAbsolut(CHelpfulValues::OppositeDirection(heroRicht));
				// neues Ziel weiter weg -> drehen!

		}
		// TODO stairs
		if (abs(xDist) >= abs(yDist)) {
			if (xDist > 0) {
				// Monster steht tendenziel rechts vom mir -> versuch nach links zu gehen (+drehen)
				// TODO
			}
		}
	}

	return monPos;

}


void CRaumView::TriggerMoveAnimation() {
	m_bMirror = !m_bMirror;
}

bool CRaumView::OnStairs() {
	return m_pMap->GetField(m_pMap->GetHeroes()->GetVector())->HoleTyp() == FeldTyp::STAIRS;
}

void CRaumView::InitDungeon(CDMDoc* pDoc, CDC* pDC, CPictures* pPictures)
{
	m_pDoc = pDoc;
	m_pPictures = pPictures;
	m_pDoorPic = new CDoorPic(pDC);
	m_pWallPic = new CWallPic(pDC);
	m_pStairsPic = new CStairsPic(pDC);
	m_pPitPic = new CPitPic(pDC);
	m_pPressurePadPic = new CPressurePadPic(pDC);
	m_pTeleportPic = new CTeleportPic(pDC);
	m_pOrnatePic = new CFloorOrnatePic(pDC);
	m_pWallDecoPic = new CWallDecoPic(pDC);
	m_pMonsterPic = new CMonsterPic(pDC);
	m_pItem3DPic = new CItem3DPic(pDC);
	m_pMagicMissilePic = new CMagicMissilePic(pDC);
	
	m_pItemInfos = new CItemInfos();
	m_pAttackInfos = new CAttackInfos();
	m_pMonsterInfos = new CMonsterInfos();

	m_pMap = new CDungeonMap(m_pItemInfos, m_pMonsterInfos);
}

void CRaumView::OnTrigger()
{
	// Hier werden sämtliche Trigger angestoßen: Schalter, Türen, etc.

	int x = m_pMap->GetHeroes()->GetVector().x;
	int y = m_pMap->GetHeroes()->GetVector().y;
	int z = m_pMap->GetHeroes()->GetVector().z;

	COMPASS_DIRECTION richt = m_pMap->GetHeroes()->GetDirection();
	int addx = x + m_values->m_sty[richt];
	int addy = y - m_values->m_stx[richt];
	CField* feld = m_pMap->GetField(addx, addy, z);
	int iFeld = feld->HoleTyp();

	// Testweise. Space = Wand vor Spieler erzeugen/löschen

	if (iFeld == FeldTyp::WALL)
	{
		//CFieldDecoration* deco = (feld->HoleDeko(CHelpfulValues::OppositeDirection(richt)));
		//if (deco->GetDecoType() == Switch) {
			//deco->SetState(1 - deco->GetState());
			//m_pDoc->PlayDMSound("C:\\Source\\C++\\DM\\sound\\DMCSB-SoundEffect-Switch.mp3");
		//} else if	(deco->GetDecoType() == Fountain) {
			//m_pMap->GetHeroes()->DrinkFountain();
		//}
		feld->SetType(FeldTyp::EMPTY);
	}
	else if (iFeld == FeldTyp::DOOR)
	{
		CDoor* door = feld->HoleDoor();
		if (door) {
			door->Toggle();
			m_pDoc->PlayDMSound("C:\\Source\\C++\\DM\\sound\\DMCSB-SoundEffect-Door.mp3");

		}
	}
	else
		feld->SetType(FeldTyp::WALL);
}

CSize CRaumView::GetSizeOfFrontDeco(CField* pField, COMPASS_DIRECTION dir)
{
	WallDecorationType graphicTypeFront = None;
	CBitmap* pic = NULL;

	if (pField->GetActuator(dir).size() > 0) {
		CActuator* pActuator = pField->GetActuator(dir).back();
		if (pActuator) {
			graphicTypeFront = m_pMap->GetWallDecorationType(pField->HolePos().z, pActuator->GetGraphic());
			pic = m_pWallDecoPic->GetPicFront(graphicTypeFront);
		}
	}
	else {
		CWallDecoration* deco = pField->GetWallDeco(dir);
		WallDecorationType wdt = deco->GetDecoType();
		pic = m_pWallDecoPic->GetPicFront(wdt);
	}
	if (pic) {
		BITMAP bmpInfo;
		pic->GetBitmap(&bmpInfo);

		return CSize(bmpInfo.bmWidth, bmpInfo.bmHeight);
	}
	return CSize(0, 0);
}