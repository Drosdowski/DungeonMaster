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
#include "Items/Potion.h"
#include "Items/Container.h"
#include "Items/CActuator.h"
#include "Items\MagicMissile.h"
#include "Items\Text.h"
#include "RaumView.h"
#include "XMLParser\CDungeonMap.h"
#include "XMLParser\ItemInfos.h"
#include "XMLParser\AttackInfos.h"
#include "SpecialTile/CStairs.h"
#include "SpecialTile/CPit.h"
#include "SpecialTile/CTeleporter.h"
#include "SpecialTile/TrickWall.h"
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
#include "Pictures\ChampionPortrait.h"
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
	m_pChampionPortraits = NULL;
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
	delete m_pMagicMissilePic;
	delete m_pChampionPortraits;
	delete m_pItem3DPic;
	delete m_pMap;
}

/////////////////////////////////////////////////////////////////////////////
// CRaumView message handlers

void CRaumView::DrawFrame(CDC* pDC, CDC* cdc, int xxx, int ebene) {
	BITMAP bmpInfo;
	for (int i = 0; i < 2; i++) {
		CBitmap* bmp = m_pDoorPic->GetDoorFramePic(ebene, (i==0));
		if (bmp) {
			CPoint pos = m_pDoorPic->GetDoorFramePos(xxx, ebene, (i == 0), m_pWallPic->GetWallPos(xxx, ebene));
			if (pos != CPoint(0, 0))
			{
				cdc->SelectObject(bmp);
				bmp->GetBitmap(&bmpInfo);
				pDC->TransparentBlt(pos.x, pos.y, bmpInfo.bmWidth * 2, bmpInfo.bmHeight * 2, cdc, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, TRANS_ORA);
			}
		}
	}
	
}

void CRaumView::DrawSquarePressurePad(CDC* pDC, CDC* cdc, int xxx, int ebene) {
	BITMAP bmpInfo;
	CBitmap* bmp = m_pPressurePadPic->GetPressurePadPic(xxx, ebene);
	if (bmp) {
		CPoint floorMiddlePos = m_pPressurePadPic->GetPos(xxx, ebene);
		if (floorMiddlePos.x > 0 || floorMiddlePos.y > 0) {
			cdc->SelectObject(bmp);
			bmp->GetBitmap(&bmpInfo);
			pDC->TransparentBlt(floorMiddlePos.x - bmpInfo.bmWidth, int(floorMiddlePos.y - bmpInfo.bmHeight*1.5),
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

		CPoint center = m_pPitPic->GetPos(xxx, ebene);
		if (pitBmp && center.x > 0 && center.y > 0) {
			double faktor = m_pPictures->getFaktor(ebene);
			cdc->SelectObject(pitBmp);
			pitBmp->GetBitmap(&bmpPitInfo);
			int decoPosX = center.x - (int)(bmpPitInfo.bmWidth);
			int decoPosY = center.y - (int)(bmpPitInfo.bmHeight);

			DrawInArea(decoPosX, decoPosY, bmpPitInfo.bmWidth, bmpPitInfo.bmHeight, 1, pDC, cdc, TRANS_ORA);

		}
	}
}

void CRaumView::DrawCeilingPit(CDC* pDC, CDC* cdc, int xxx, int ebene, CPit* pit) {
	BITMAP bmpPitInfo;
	if (pit) {
		CBitmap* pitBmp = m_pPitPic->GetPitCeilingPic(ebene, xxx);
		CPit::PitType type = pit->GetType();

		CPoint center = m_pPitPic->GetCeilingPos(xxx, ebene);
		if (pitBmp && center.x > 0 && center.y > 0) {
			double faktor = m_pPictures->getFaktor(ebene);
			cdc->SelectObject(pitBmp);
			pitBmp->GetBitmap(&bmpPitInfo);
			int decoPosX = center.x - (int)(bmpPitInfo.bmWidth * faktor);
			int decoPosY = center.y - (int)(bmpPitInfo.bmHeight * faktor);

			DrawInArea(decoPosX, decoPosY, bmpPitInfo.bmWidth, bmpPitInfo.bmHeight, 1, pDC, cdc, TRANS_ORA);

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
		DrawFrame(pDC, cdc, xxx, ebene); // both Frames
		bmp = m_pDoorPic->GetDoorFrontPic(pDoor, ebene);
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
		CBitmap* bmp = m_pDoorPic->GetDoorFrontPic(pDoor, ebene);
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
	if (graphicTypeFront != None) {
		bmpDecoFront = m_pWallDecoPic->GetPicFront(graphicTypeFront);		
	}

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
	CPoint centerFrontWall;
	if (bmpDecoFront)
	{
		if (((xxx == 4) && (ebene == 1)) ||
			((xxx > 1) && (ebene == 2)) ||
			(ebene == 3)) {
			bool drawNearFloor = m_pWallDecoPic->DrawNearFloor(graphicTypeFront);
			if (drawNearFloor)
				centerFrontWall = m_pWallPic->GetBottomCenterFromFrontWall(xxx, ebene);
			else
				centerFrontWall = m_pWallPic->GetCenterFromFrontWall(xxx, ebene);

			if (bmpDecoFront && centerFrontWall.x > 0 && centerFrontWall.y > 0) {
				cdc->SelectObject(bmpDecoFront);
				bmpDecoFront->GetBitmap(&bmpDecoInfo);
				int decoPosX = posWall.x + centerFrontWall.x - (int)(bmpDecoInfo.bmWidth * faktor);
				int decoPosY = posWall.y + centerFrontWall.y - (int)(bmpDecoInfo.bmHeight * faktor) / (drawNearFloor ? 1 : 2);
				isBigContainer = ((graphicTypeFront == SquareAlcove ||
					graphicTypeFront == ArchedAlcove ||
					graphicTypeFront == ViAltar ||
					graphicTypeFront == Fountain));

				DrawInArea(decoPosX, decoPosY, bmpDecoInfo.bmWidth, bmpDecoInfo.bmHeight, faktor, pDC, cdc, TRANS_ORA);

				if (isBigContainer) {
					// icons rein malen!
					std::deque<CItem*> pile = pField->GetItem((SUBPOS_ABSOLUTE)richtOppo);
					if (pile.size() > 0) {
						COMPASS_DIRECTION heroDir = m_pMap->GetHeroes()->GetDirection();
						DrawPile(pDC, cdc, xxx, ebene, MIDDLE, heroDir, pile, isBigContainer);
					}
				}
				else if (graphicTypeFront == ChampionMirror && actuatorsFront.back()->IsActive()) {
					if (ebene == 1 && xx == 0) {
						// Hero Picture
						CBitmap* heroPic = m_pChampionPortraits->GetChampions();
						int heroId = actuatorsFront.back()->GetData();
						CPoint koord = m_pChampionPortraits->GetKoords(heroId);

						CDC tmpdc;
						tmpdc.CreateCompatibleDC(pDC);
						tmpdc.SelectObject(heroPic);

						pDC->TransparentBlt(decoPosX+16*2, decoPosY+6*2, 32*2, 29*2, &tmpdc, koord.x, koord.y, 32, 29, TRANS_GRE);
						tmpdc.DeleteDC();
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

	if (((xxx == 4) && (ebene == 1)) ||
		((xxx > 1) && (ebene == 2))) {
		CText* text = pField->GetFirstText(richtOppo);
		if (text) {
			centerFrontWall = m_pWallPic->GetCenterFromFrontWall(xxx, ebene);
			centerFrontWall.x += posWall.x;
			centerFrontWall.y += posWall.y;
			WriteOnWall(pDC, centerFrontWall, text, ebene);
		}
	}

}

void CRaumView::WriteOnWall(CDC* pDC, CPoint pos, CText* text, int ebene) {
	m_pPictures->DrawSpecialFont(pDC, pos, text->GetText(), ebene == 1 ? 20 : 12);
}


void CRaumView::DrawMonsterGroup(CDC* pDC, CDC* cdc, int xxx, int ebene, COMPASS_DIRECTION richt, CField* pField) {
	CGrpMonster* pGrpMon = (CGrpMonster*)pField->GetMonsterGroup();
	if (pGrpMon)
	{
		DrawMonster(pDC, cdc, xxx, ebene, richt, pGrpMon->GetMonsterByRelSubPos(LINKSFRONT, richt));
		DrawMonster(pDC, cdc, xxx, ebene, richt, pGrpMon->GetMonsterByRelSubPos(RECHTSFRONT, richt));
		DrawMonster(pDC, cdc, xxx, ebene, richt, pGrpMon->GetMonsterByRelSubPos(LINKSBACK, richt));
		DrawMonster(pDC, cdc, xxx, ebene, richt, pGrpMon->GetMonsterByRelSubPos(RECHTSBACK, richt));
		DrawMonster(pDC, cdc, xxx, ebene, richt, pGrpMon->GetMonsterByRelSubPos(MITTE, richt));
	}
}

void CRaumView::DrawMonster(CDC* pDC, CDC* cdc, int xxx, int ebene, COMPASS_DIRECTION richt, CMonster* pMonster) {
	if (!pMonster) return;

	CBitmap* bmpMonster;
	BITMAP bmpInfoMonster, bmpInfoWall;
	double faktor = m_pPictures->getFaktor(ebene);
	bool inside = (ebene == 0) && (xxx == 4);
	CPoint p = m_pWallPic->GetWallPos(xxx, ebene);
	// monster pos an wallpos orientieren
	CBitmap* bmpWall = m_pWallPic->GetWallPic(xxx, ebene, false);
	bmpWall->GetBitmap(&bmpInfoWall);
	// P: Unten Mitte der Mauer
	p.x += bmpInfoWall.bmWidth;
	p.y += bmpInfoWall.bmHeight * 2; // = untere Kante des Monsters!
	SUBPOS subPos = CHelpfulValues::GetRelativeSubPosPassive(pMonster->HoleSubPosition(), richt);

	if (pMonster->isAlive())
	{
		bmpMonster = m_pMonsterPic->GetBitmap(pMonster, richt);
		if (bmpMonster == NULL) return; // todo passiert, wenn Monster nicht da sind

	}
	else {
		bmpMonster = NULL;
	}

	if (bmpMonster) {
		//get original size of bitmap
		bmpMonster->GetBitmap(&bmpInfoMonster);

		p.x = p.x - (int)(bmpInfoMonster.bmWidth * faktor);
		p.y = p.y - (int)(bmpInfoMonster.bmHeight * faktor * 2);

		CPoint pos = CHelpfulValues::CalcSubPosition(p, subPos, faktor);

		cdc->SelectObject(bmpMonster);
		DrawInArea(pos.x, pos.y, bmpInfoMonster.bmWidth, bmpInfoMonster.bmHeight, faktor, pDC, cdc, pMonster->transCol);
	}
}

/*void test(CDC* pDC, int x, int y) {
	y = y - 55;
	pDC->Ellipse(x - 5, y - 5, x + 5, y + 5);
}*/

void CRaumView::DrawOnFloor(CDC* pDC, CDC* cdc, int xxx, int ebene, CField* pField) {
	BITMAP bmpDecoInfo;

	std::deque<CActuator*> actuators = pField->GetActuator((COMPASS_DIRECTION)0);  // Boden hat immer POsition 0.
	for (CActuator* actuator : actuators) {
		if (actuator->GetGraphic() == 3 || actuator->GetGraphic() == 1 || actuator->GetGraphic() == 4) {
			DrawSquarePressurePad(pDC, cdc, xxx, ebene);
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
		if (decoBmp)
		{
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

}

void CRaumView::DrawOneOfPile(CDC* pDC, CDC* cdc, int xxx, int ebene, SUBPOS_ABSOLUTE itemSubPos, COMPASS_DIRECTION heroDir, CItem* item, bool center) {
	int xx = wallXFactor[xxx]; // 0,1,2,3,4 => -2,2,-1,1,0
	CBitmap* bmp = NULL;
	CItem::ItemType typ = item->getItemType();
	if (typ == CItem::ItemType::MiscItem) {
		CMiscellaneous* miscItem = (CMiscellaneous*)item;
		bmp = m_pItem3DPic->GetMiscBitmap(miscItem->GetType(), miscItem->GetSubtype());
	}
	else if (typ == CItem::ItemType::WeaponItem) {
		bmp = m_pItem3DPic->GetWeaponBitmap(((CWeapon*)item)->GetType(), item->IsFlying());
	}
	else if (typ == CItem::ItemType::ClothItem) {
		bmp = m_pItem3DPic->GetClothBitmap(((CCloth*)item)->GetType(), item->IsFlying());
	}
	else if (typ == CItem::ItemType::PotionItem) {
		bmp = m_pItem3DPic->GetPotionBitmap(((CPotion*)item)->GetType()); // todo cast notwendig?
	}
	else if (typ == CItem::ItemType::ScrollItem) {
		bmp = m_pItem3DPic->GetScrollBitmap();
	}
	else if (typ == CItem::ItemType::ContainerItem) {
		bmp = m_pItem3DPic->GetContainerBitmap(center);
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


void CRaumView::DrawPile(CDC* pDC, CDC* cdc, int xxx, int ebene, SUBPOS_ABSOLUTE itemSubPos, COMPASS_DIRECTION heroDir, std::deque<CItem*> pile, bool center) {
	for (CItem* item : pile) {
		DrawOneOfPile(pDC, cdc, xxx, ebene, itemSubPos, heroDir, item, center);
	}
}

void CRaumView::DrawMagicMissile(CDC* pDC, CDC* cdc, int xxx, int ebene, SUBPOS_ABSOLUTE itemSubPos, COMPASS_DIRECTION heroDir, std::deque<CMagicMissile*> magicMissiles) {
	int xx = wallXFactor[xxx]; // 0,1,2,3,4 => -2,2,-1,1,0
	CBitmap* bmp;	
	CMagicMissile* magicMissile = magicMissiles.back();
	bool isInside = (ebene == 0) && (xxx == 4);
	
	bmp = m_pMagicMissilePic->GetMagicMissileBitmap(magicMissile->GetType(), magicMissile->IsExploding(), isInside, magicMissile->GetSize());
	if (bmp) {
		// todo refaktorieren mit Throw... viel DOppelcode!
		// todo exploding in mitte?
		BITMAP bmpInfo;
		bmp->GetBitmap(&bmpInfo);
		cdc->SelectObject(bmp);

		if (!isInside) {
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
				
					/*for (int aebene = 0; aebene <= 4; aebene++) {
						CPoint xPos = CHelpfulValues::CalcRelSubFloorPosition(bmpInfo, m_pItem3DPic->GetFloorMiddle(xxx, aebene), subPos, faktor, xx, aebene);
						pDC->Ellipse(xPos.x - 3, xPos.y - 3, xPos.x + 3, xPos.y + 3);
					}*/
				
					if (!magicMissile->IsExploding()) {
						if (pos.y != 0) {
							pos.y = 250 - pos.y / 2;
						}
					}
					else {
						CPoint posWall = m_pWallPic->GetWallPos(xxx, ebene);
						CPoint posMitte = m_pWallPic->GetCenterFromFrontWall(xxx, ebene);	
						pos.x = posWall.x + posMitte.x - (int)(bmpInfo.bmWidth * faktor);
						pos.y = posWall.y + posMitte.y - (int)(bmpInfo.bmHeight * faktor);
					}
					DrawInArea(pos.x, pos.y, bmpInfo.bmWidth, bmpInfo.bmHeight, faktor, pDC, cdc, TRANS_ORA);
				}
			}
		}
		else if (magicMissile->IsExploding()) { // Fliegende nicht zeichnen wenn auf dem Spieler (beim zaubern)
			// inside
			CPoint pos = m_pWallPic->GetWallPos(4, 0);
			pDC->TransparentBlt(pos.x, pos.y,
				MainAreaWidth, MainAreaHeight, cdc, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, TRANS_ORA);

		}
	}
}


void CRaumView::DrawInArea(int x, int y, int w, int h, double faktor, CDC* pDC, CDC* cdc, COLORREF col) {
	int realWidth = int(w * 2 * faktor);
	int realHeight = int(h * 2 * faktor);
	int rechterRand = realWidth + x;
	int reducedWidth = realWidth;
	int zuvielrechts = 0;
	if (rechterRand > MainAreaWidth)
	{
		zuvielrechts = rechterRand - MainAreaWidth;
		reducedWidth -= (int)(zuvielrechts);
	}

	if (reducedWidth > 0)
	{
		pDC->TransparentBlt(x, y,
			reducedWidth, realHeight,
			cdc, 0, 0, w - zuvielrechts / 2, h, col);
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

				if (((ebene != 0) || (xx != 0)))
				{
					if (fieldType == FeldTyp::TRICKWALL)
					{
						CTrickWall* pTrickWall = pField->HoleTrickWall();
						if (pTrickWall->GetState() == CTrickWall::Closed)
							DrawWall(pDC, &compCdc, xxx, ebene, heroDir, pField);
					}
					if (fieldType == FeldTyp::WALL) 
					{
						DrawWall(pDC, &compCdc, xxx, ebene, heroDir, pField);
					}
				}
				if (fieldType == FeldTyp::DOOR)
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
				else if (fieldType == FeldTyp::EMPTY) {
					// Platten, Pfützen, Fussabdrücke, ...
					DrawOnFloor(pDC, &compCdc, xxx, ebene, pField);
				}

				if (fieldType != FeldTyp::WALL) {
					for (int pos = 0; pos < 4; pos++)
					{
						std::deque<CItem*> pile = pField->GetItem((SUBPOS_ABSOLUTE)pos);
						if (pile.size() > 0) {
							DrawPile(pDC, &compCdc, xxx, ebene, (SUBPOS_ABSOLUTE)pos, heroDir, pile, false);
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
				if (fieldType == FeldTyp::TELEPORT) {
					CTeleporter* tele = pField->HoleTeleporter();
					if (tele && tele->isVisible()) {
						DrawTeleporter(pDC, &compCdc, xxx, ebene, tele);
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

VEKTOR CRaumView::Betrete(VEKTOR toPos, boolean &collision)
{
	CField* pField = m_pMap->GetField(toPos);
	FeldTyp iTyp = pField->HoleTyp();
	CGrpHeld* pGrpHelden = m_pMap->GetHeroes();
	CGrpMonster* pGrpMonster = pField->GetMonsterGroup();
	VEKTOR fromPos = pGrpHelden->GetVector();
	if (iTyp == FeldTyp::WALL) {
		collision = true;
		return fromPos;
	}
	else if (iTyp == FeldTyp::DOOR)
	{
		CDoor* pDoor = pField->HoleDoor();
		if (pDoor->getState() != CDoor::OPEN && pDoor->getState() != CDoor::DESTROYED)
		{
			collision = true;
			return fromPos;
		}
		if (pGrpMonster) return fromPos;
	}
	else if (iTyp == FeldTyp::TRICKWALL) {
		CTrickWall* pTrickwall = pField->HoleTrickWall();
		if (pTrickwall->GetState() != CTrickWall::Opened) {
			collision = true;
			return fromPos;
		}
	}
	else if (iTyp == FeldTyp::EMPTY ) {
		collision = false;
		if (pGrpMonster) return fromPos;
	}
	else if (iTyp == FeldTyp::PIT) {
		collision = false;
		//FallingHeroes(toPos);
		//return toPos;
	}
	else if (iTyp == FeldTyp::TELEPORT) {
		collision = false;
		/*CTeleporter* pTeleport = pField->HoleTeleporter();
		if (pTeleport->isOpen()) {
			toPos = pTeleport->Trigger(m_pDoc, m_pMap, toPos, true);
		}*/ // triggert später!
	}
	else if (iTyp == FeldTyp::STAIRS) {
		collision = false;
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

void CRaumView::FallingHeroes(VEKTOR heroPos) {
	CField* pField = m_pMap->GetField(heroPos);
	CPit* pit = pField->HolePit();
	if (pit)
	{
		if (pit->GetState() == CPit::Opened) {
			heroPos.x += (m_pMap->GetOffset(heroPos.z).x - m_pMap->GetOffset(heroPos.z + 1).x);
			heroPos.y += (m_pMap->GetOffset(heroPos.z).y - m_pMap->GetOffset(heroPos.z + 1).y);
			heroPos.z++;
			CGrpHeld* pGrpHelden = m_pMap->GetHeroes();
			pGrpHelden->Laufen(heroPos, true);
			pGrpHelden->FallingDamage();
			m_pDoc->PlayDMSound("C:\\Users\\micha\\source\\repos\\DungeonMaster\\sound\\DMCSB-SoundEffect-FallingandDying.mp3");
		}
	}
}


void CRaumView::TeleportAll(VEKTOR heroPos) {
	CField* field = m_pMap->GetField(heroPos);
	CTeleporter* pTeleporter = field->HoleTeleporter();
	if (pTeleporter) {
		if (pTeleporter->getScope() == TeleporterAttributes::Scope::Items_Party ||
			pTeleporter->getScope() == TeleporterAttributes::Scope::All) {

			pTeleporter->Trigger(m_pDoc, m_pMap, heroPos, false);
		}

	}
}

void CRaumView::MoveMonsters(VEKTOR monsterPos) {
	CField* field = m_pMap->GetField(monsterPos);
	CGrpMonster* pGrpMon = field->GetMonsterGroup();
	if (pGrpMon)
	{
		if (!pGrpMon->Altern(field)) {
			// Gruppe ausgestorben!
			std::deque<CItem*> inventory = pGrpMon->DropInventory();
			if (!inventory.empty()) {
				for (CItem* pItem : inventory) {
					field->PutItem(pItem, pGrpMon->GetLastPos());
				}
				inventory.clear();
			}
			field->RemoveMonsterGroup();
		}
		else {
			CPit* pit = field->HolePit();
			if (pit) {
				if (pit->GetState() == CPit::Opened) {
					monsterPos.x += (m_pMap->GetOffset(monsterPos.z).x - m_pMap->GetOffset(monsterPos.z + 1).x);
					monsterPos.y += (m_pMap->GetOffset(monsterPos.z).y - m_pMap->GetOffset(monsterPos.z + 1).y);
					monsterPos.z++;
					pGrpMon->FallingDamage();
				}
			}
			if (pGrpMon->AnyoneReady())
			{
				VEKTOR target = MonsterMoveOrAttack(pGrpMon);
				if (target.x != monsterPos.x || target.y != monsterPos.y) {
					CField* targetField = m_pMap->GetField(target);
					field->SetMonsterGroup(NULL);
					targetField->SetMonsterGroup(pGrpMon);
					pGrpMon->MoveDone();
				}
			}
		}
		
	}
}

void CRaumView::MoveDoors(VEKTOR position) {
	CField* field = m_pMap->GetField(position);
	CGrpHeld* pGrpHeroes = m_pMap->GetHeroes();
	CGrpMonster* pGrpMonsters = field->GetMonsterGroup();
	boolean monsterBelowDoor = pGrpMonsters != NULL;
	boolean playerBelowDoor = CHelpfulValues::VectorEqual(pGrpHeroes->GetVector(), position);
	CDoor* pDoor = field->HoleDoor();
	if (pDoor) {
		if ((pDoor->getState() == CDoor::DoorState::OPENING) ||
			(pDoor->getState() == CDoor::DoorState::CLOSING))
		{
			if (pDoor->ContinueMoving(monsterBelowDoor | playerBelowDoor)) {
				m_pDoc->PlayDMSound("C:\\Users\\micha\\source\\repos\\DungeonMaster\\sound\\DMCSB-SoundEffect-RunningIntoAWall.mp3");
				if (playerBelowDoor) {
					pGrpHeroes->FallingDamage();
				}
				else if (monsterBelowDoor) {
					pGrpMonsters->FallingDamage();
					pGrpMonsters->Scare();
				}
			}
			else {
				m_pDoc->PlayDMSound("C:\\Users\\micha\\source\\repos\\DungeonMaster\\sound\\DMCSB-SoundEffect-Door.mp3");
			}
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
			for (CMagicMissile* magicMissile : magicMissiles)
				magicMissile->ResethasMoved();
		}
	}
}

void CRaumView::MoveMagicMissiles(VEKTOR position, SUBPOS_ABSOLUTE posAbs) {
	CField* field = m_pMap->GetField(position);
	std::deque<CMagicMissile*> magicMissiles = field->GetMagicMissile(posAbs);
	if (!magicMissiles.empty()) {
		for (CMagicMissile* magicMissile : magicMissiles) 
			MoveMagicMissile(position, posAbs, magicMissile);
	}
}

void CRaumView::MoveMagicMissile(VEKTOR position, SUBPOS_ABSOLUTE posAbs, CMagicMissile* topMissile) {
	// todo refaktorieren mit moveItems
	CField* field = m_pMap->GetField(position);
	if (!topMissile->HasMovedThisTick()) {

		SUBPOS_ABSOLUTE newPos = CHelpfulValues::FindNextSubposWithoutFieldChange(posAbs, topMissile->m_flyForce);
		if (topMissile->IsExploding() && newPos == posAbs) {
			if (topMissile->GetType() == CMagicMissile::MagicMissileType::Poison || topMissile->GetType() == CMagicMissile::MagicMissileType::Dust) {
				// Gift- und Staubwolke verschwinden langsam
				if (topMissile->GetStrength() > 1) {
					topMissile->DecreaseStrength();
					return; // heroPos;
				}
				else {
					field->TakeMissile(posAbs, topMissile); // out of energy, gone
					delete topMissile;
				}
			}
			else {
				CGrpHeld* pGrpHeld = m_pMap->GetHeroes();
				if (CHelpfulValues::VectorEqual(position, pGrpHeld->GetVector()))
				{
					pGrpHeld->DoDamage(topMissile->GetStrength() * 10, position, true);
				}
				field->TakeMissile(posAbs, topMissile);
				delete topMissile;
			}
		}
		else if (newPos == OUTSIDE) {
			// Feld verlassen
			CField* newField = m_pMap->GetField(position.x + sign(topMissile->m_flyForce.x), position.y + sign(topMissile->m_flyForce.y), position.z);
			COMPASS_DIRECTION direction = topMissile->GetDirection();

			if (!newField->BlockedToWalk()) {
				// todo prüfen topMissile = field->TakeMissile(posAbs);
				field->TakeMissile(posAbs, topMissile);
				newField = ChangeFieldWithTeleporter(newField, posAbs, direction);
				topMissile->SetDirection(direction);
				newField = ChangeFieldWithStairs(newField, topMissile, posAbs);
				// westlich von west ist ost => anders rum subpos suchen
				newPos = CHelpfulValues::FindNextSubposWithoutFieldChange(posAbs, VEKTOR{ -topMissile->m_flyForce.x, -topMissile->m_flyForce.y, 0 });

				newField->CastMissile(topMissile, newPos);
				topMissile->SetDone();
				return; //newField->HolePos();
			}
			else {
				CDoor* pDoor = newField->HoleDoor();
				if (pDoor) {
					// Bei Tür noch bewegen, und dann Bumm - Bei Wand sofort.
					field->TakeMissile(posAbs, topMissile);
					topMissile->SetDirection(direction);
					newPos = CHelpfulValues::FindNextSubposWithoutFieldChange(posAbs, VEKTOR{ -topMissile->m_flyForce.x, -topMissile->m_flyForce.y, 0 });
					newField->CastMissile(topMissile, newPos);
				}
				topMissile->Explode();
				if (topMissile->GetType() == CMagicMissile::Fireball)
				{
					m_pDoc->PlayDMSound("C:\\Users\\micha\\source\\repos\\DungeonMaster\\sound\\DMCSB-SoundEffect-ExplodingFireball.mp3");
				}
				else if (topMissile->GetType() == CMagicMissile::Poison || topMissile->GetType() == CMagicMissile::PoisonBlob || topMissile->GetType() == CMagicMissile::AntiMagic) {
					m_pDoc->PlayDMSound("C:\\Users\\micha\\source\\repos\\DungeonMaster\\sound\\DMCSB-SoundEffect-ExplodingSpell.mp3");
				}
				topMissile->SetDone();
				if (pDoor) {
					if (topMissile->GetType() == CMagicMissile::Fireball || topMissile->GetType() == CMagicMissile::Lightning  && pDoor->destroyedByFireball()) {
						pDoor->SetState(CDoor::DESTROYED);
					}
					if (topMissile->GetType() == CMagicMissile::OpenDoor && pDoor->hasButton() && pDoor->getState() == CDoor::CLOSED)
					{
						pDoor->Toggle();
					}

				}
			}
		}
		else {
			// todo prüfen topMissile = field->TakeMissile(posAbs);
			field->TakeMissile(posAbs, topMissile);
			if (topMissile->IsFlying()) {
				topMissile->ReduceSpeed();
				field->CastMissile(topMissile, newPos);
				return; //heroPos;
			}
			else {
				delete topMissile;
			}
		}
	}
	return; // VEKTOR{ 0, 0, 0 };
}


void CRaumView::CheckMissileCollisions(VEKTOR heroPos) {

	CField* field = m_pMap->GetField(heroPos);
	for (int s = 0; s < 4; s++) {
		SUBPOS_ABSOLUTE posAbs = (SUBPOS_ABSOLUTE)s;
		std::deque<CMagicMissile*> magicMissiles = field->GetMagicMissile(posAbs);
		if (!magicMissiles.empty()) {
			CMagicMissile* topMissile = magicMissiles.back(); // todo prüfen, reicht es, nur das oberste anzuschauen, gibt es > 1 fliegende Missiles je Feld
			if ((!topMissile->IsExploding()) && (
				topMissile->GetType() == CMagicMissile::MagicMissileType::PoisonBlob || 
				topMissile->GetType() == CMagicMissile::MagicMissileType::Poison || 
				topMissile->GetType() == CMagicMissile::MagicMissileType::Fireball || 
				topMissile->GetType() == CMagicMissile::MagicMissileType::Lightning || 
				topMissile->GetType() == CMagicMissile::MagicMissileType::AntiMagic)) {

				CGrpMonster* pGroupMonster = field->GetMonsterGroup();
				if (pGroupMonster) {
					CMonster* pHittedMonster = pGroupMonster->GetMonsterByAbsSubPos(posAbs);
					if (pHittedMonster) {
						CMonsterInfos* monsterInfos = GetMonsterInfos(); 
						CMonsterConst mc = monsterInfos->GetMonsterInfo(pGroupMonster->GetType());
						if (mc.non_material == (topMissile->GetType() == CMagicMissile::MagicMissileType::AntiMagic))
						{
							topMissile->Explode();
							if (topMissile->GetType() == CMagicMissile::MagicMissileType::Fireball ||
								topMissile->GetType() == CMagicMissile::MagicMissileType::Lightning)
							{
								m_pDoc->PlayDMSound("C:\\Users\\micha\\source\\repos\\DungeonMaster\\sound\\DMCSB-SoundEffect-ExplodingFireball.mp3");
							}
							else {
								m_pDoc->PlayDMSound("C:\\Users\\micha\\source\\repos\\DungeonMaster\\sound\\DMCSB-SoundEffect-ExplodingSpell.mp3");
							}
							topMissile->SetDone();
							pGroupMonster->DoDamage(topMissile->GetStrength() * (rand() % 6 + 1), heroPos, true);
						}
					}
					else {
						// todo kann auch spieler treffen!
					}
				}
			}
		}
	}
}

void CRaumView::CheckFlyingItemCollisions(VEKTOR heroPos) {
	CField* field = m_pMap->GetField(heroPos);
	for (int s = 0; s < 4; s++) {
		SUBPOS_ABSOLUTE posAbs = (SUBPOS_ABSOLUTE)s;
		std::deque<CItem*> items = field->GetItem(posAbs);
		if (!items.empty()) {
			CItem* topItem = items.back(); // todo prüfen, reicht es, nur das oberste anzuschauen, gibt es > 1 fliegende Items je Feld
			if (topItem->IsFlying()) {

				CGrpMonster* pGroupMonster = field->GetMonsterGroup();
				if (pGroupMonster) {
					CMonster* pHittedMonster = pGroupMonster->GetMonsterByAbsSubPos(posAbs);
					if (pHittedMonster) {
						CMonsterInfos* monsterInfos = GetMonsterInfos();
						CMonsterConst mc = monsterInfos->GetMonsterInfo(pGroupMonster->GetType());
						if (!mc.non_material)
						{
							pGroupMonster->DoDamage((rand() % 6 + 1), heroPos, true);
							topItem->Stop();
						}
					}
					else {
						// todo kann auch spieler treffen!
					}
				}
			}
		}
	}
}

void CRaumView::CheckOtherDelays(VEKTOR fieldPos) {
	CField* field = m_pMap->GetField(fieldPos);
	CTeleporter* tele = field->HoleTeleporter();
	if (tele) {
		if (!tele->openDelayDone()) {
			tele->decreaseOpenDelay();
			if (tele->openDelayDone()) {
				tele->Trigger(m_pDoc, m_pMap, fieldPos, true);
			}
		}
		if (!tele->closeDelayDone()) {
			tele->decreaseCloseDelay();
		}
	}
	CTrickWall* twall = field->HoleTrickWall();
	if (twall) {
		if (!twall->openDelayDone()) {
			twall->decreaseOpenDelay();
		}
		if (!twall->closeDelayDone()) {
			twall->decreaseCloseDelay();
		}
	}
	CPit* pit = field->HolePit();
	if (pit) {
		if (!pit->openDelayDone()) {
			pit->decreaseOpenDelay();
			if (pit->openDelayDone()) {
				// todo FallingHeroes(fieldPos);
			}
		}
		if (!pit->closeDelayDone()) {
			pit->decreaseCloseDelay();
		}
	}
}


void CRaumView::MoveItems(VEKTOR itemPos) {
	CField* field = m_pMap->GetField(itemPos);

	for (int s = 0; s < 4; s++) {
		SUBPOS_ABSOLUTE posAbs = (SUBPOS_ABSOLUTE)s;
		std::deque<CItem*> pile = field->GetItem(posAbs);
		if (!pile.empty()) {
			for (CItem* pItem : pile) {
				if (pItem->IsFlying() && !pItem->HasMovedThisTick()) {
					// fliegendes Item gefunden
					SUBPOS_ABSOLUTE newPos = CHelpfulValues::FindNextSubposWithoutFieldChange(posAbs, pItem->m_flyForce);

					if (newPos == OUTSIDE) {
						// Feld verlassen
						CField* newField = m_pMap->GetField(itemPos.x + sign(pItem->m_flyForce.x), itemPos.y + sign(pItem->m_flyForce.y), itemPos.z);
						if (!newField->BlockedToWalk()) {
							pItem = field->TakeItem(posAbs);
							COMPASS_DIRECTION direction = pItem->GetDirection();
							newField = ChangeFieldWithTeleporter(newField, posAbs, direction);
							pItem->SetDirection(direction);
							newField = ChangeFieldWithStairs(newField, pItem, posAbs);
							// westlich von west ist ost => anders rum subpos suchen
							if (pItem->IsFlying()) // todo unnötioge frage?
								newPos = CHelpfulValues::FindNextSubposWithoutFieldChange(posAbs, VEKTOR{ -pItem->m_flyForce.x, -pItem->m_flyForce.y, 0 });
							else
								newPos = posAbs;
							newField->PutItem(pItem, newPos);
						}
						else {
							// nicht bewegen, sondern stehen bleiben (unten)
							pItem->m_flyForce = { 0,0,0 };
						}
					}
					else {
						pItem = field->TakeItem(posAbs);
						pItem->ReduceSpeed();
						field->PutItem(pItem, newPos);
					}
				}
				if (!pItem->IsFlying()) {
					CPit* pit = field->HolePit();
					if (pit) {
						if (pit->GetState() == CPit::Opened) {
							pItem = field->TakeItem(posAbs);
							itemPos.x += (m_pMap->GetOffset(itemPos.z).x - m_pMap->GetOffset(itemPos.z + 1).x);
							itemPos.y += (m_pMap->GetOffset(itemPos.z).y - m_pMap->GetOffset(itemPos.z + 1).y);
							itemPos.z++;
							CField* newField = m_pMap->GetField(itemPos);
							newField->PutItem(pItem, posAbs);
						}
					}
				}
			}

		}
	}
}

CField* CRaumView::ChangeFieldWithTeleporter(CField* &pField, SUBPOS_ABSOLUTE& subPos, COMPASS_DIRECTION& direction) {
	CTeleporter* tp = pField->HoleTeleporter();

	if (tp && tp->isOpen()) {
		COMPASS_DIRECTION dir = tp->getTargetDirection();
		if (tp->getRotationType() == TeleporterAttributes::RotationType::Absolute) {
			switch (tp->getRotation()) {
			case 0:
				direction = NORTH; break;
			case 90:
				direction = EAST; break;
			case 180:
				direction = SOUTH; break;
			case 270:
				direction = WEST; break;
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

		pField = m_pMap->GetField( tp->getTargetField());
	}
	return pField;
}
CField* CRaumView::ChangeFieldWithStairs(CField* pField, CMovingObject* pItem, SUBPOS_ABSOLUTE& subPos) {
	CStairs* stair = pField->HoleStairs();
	if (stair) {
		// In Treppe: Flug zu Ende
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
			else if (sourceDir < targetDir) {
				for (int t = 0; t < (targetDir - sourceDir); t++)
					subPos = CHelpfulValues::RightFrom(subPos);
			}
		} else {
			subPos = CHelpfulValues::FindNextSubposWithoutFieldChange(subPos, VEKTOR{ -pItem->m_flyForce.x, -pItem->m_flyForce.y, 0 });
		}
		pItem->m_flyForce = { 0,0,0 };
	}
	return pField;
}


void CRaumView::MoveAnythingNearby() {
	VEKTOR held = m_pMap->GetHeroes()->GetVector();
	FallingHeroes(held);
	for (int i = max(held.x - 4, 0); i < min(held.x + 4, m_pMap->GetMaxWidth(held.z)); i++) {
		for (int j = max(held.y - 4, 0); j < min(held.y + 4, m_pMap->GetMaxHeight(held.z)); j++) {
			VEKTOR pos = { i, j, held.z };
			TeleportAll(pos);
			MoveMonsters(pos);
			MoveDoors(pos);
			PrepareMoveObjects(pos);
			CheckFlyingItemCollisions(pos);
			MoveItems(pos);
			CheckMissileCollisions(pos);
			for (int s = 0; s < 4; s++) {
				SUBPOS_ABSOLUTE posAbs = (SUBPOS_ABSOLUTE)s;
				MoveMagicMissiles(pos, posAbs);
			}
		}
	}
}

void CRaumView::TriggerPassiveActuators(VEKTOR fieldPos, VEKTOR heroPos) {
	CField* field = m_pMap->GetField(fieldPos);
	std::deque<CActuator*> actuatorsAtPosition;

	for (int direction = 0; direction < 4; direction++) {
		// Alle Aktuatoren sammeln, egal welche Position. Aber je Position nur den jeweils ersten.
		std::deque<CActuator*> actuators = field->GetActuator((COMPASS_DIRECTION)direction);
		if (!actuators.empty()) {		
			actuatorsAtPosition.push_back(actuators[0]);
		}
	}

	if (!actuatorsAtPosition.empty()) {
		TriggerPassiveActuator(heroPos, field, actuatorsAtPosition[0]);
		field->StoreCurrentWeight(heroPos);
	}

}

void CRaumView::TriggerPassiveActuator(VEKTOR heroPos, CField* field, CActuator* actuator) {
	if (!actuator->delayDone()) {
		actuator->decreaseDelay();
		return;
	}

	VEKTOR target = actuator->GetActionTarget() == CActuator::ActionTarget::Remote ? actuator->GetTarget() : field->HolePos();
	CField* pTargetField = m_pMap->GetField(target);
	double critWeight = actuator->GetCriticalWeigth();
	bool isWall = field->HoleTyp() == FeldTyp::WALL;
	bool criticalWeightBreached = !isWall && field->CriticalWeightBreached(heroPos, critWeight);
	bool criticalWeightGone = !isWall && field->CriticalWeightGone(heroPos, critWeight);
	switch (actuator->GetType()) { // TODO: Unterscheidung 1,2,3 monster / items / etc
	case CActuator::PressurePadTPCI:
	case CActuator::PressurePadTPC:
	case CActuator::PressurePadP:
		if (criticalWeightBreached || criticalWeightGone) {
			TriggerTarget(pTargetField, actuator, criticalWeightBreached);
			actuator->resetDelay();
			//if (actuator->GetType() != CActuator::PressurePadP) // wtf?
			//{ 
			field->RotateActuators(actuator->GetPosition());
			//}
		}
		break;
	case CActuator::Gate:
		if (field->BlockedToWalk()) { // Wall => Switch, no Pressure Pad
			if (actuator->GetType()  == CActuator::Hold) return;
		}
		TriggerTarget(pTargetField, actuator, true);
		actuator->resetDelay();
		field->RotateActuators(actuator->GetPosition());
		break;
	}
}

void CRaumView::TriggerTarget(CField* pTargetField, CActuator* actuator, boolean criticalWeightBreached) {
	CActuator::ActionTypes type = actuator->GetActionType();

	TriggerDoor(pTargetField, type, criticalWeightBreached);
	TriggerPit(pTargetField, type, criticalWeightBreached);
	TriggerTrickwall(pTargetField, type, criticalWeightBreached);
	TriggerTeleport(pTargetField, type, criticalWeightBreached, true);
	TriggerMissileShooter(pTargetField, actuator, criticalWeightBreached);
}

void CRaumView::TriggerTrickwall(CField* pTargetField, CActuator::ActionTypes type, boolean criticalWeightBreached)
{
	CTrickWall* pTWall = pTargetField->HoleTrickWall();
	if (pTWall) {
		switch (type)
		{
		case CActuator::Set:
			if (criticalWeightBreached) {
				pTWall->Open(0);
			}
			break;
		case CActuator::Toggle:
			if (criticalWeightBreached) {
				pTWall->Toggle();
			}
			break;
		case CActuator::Clear:
			if (criticalWeightBreached) {
				pTWall->Close(0);
			}
			break;
		case CActuator::Hold:
			pTWall->Toggle();
			break;
		}
	}
}

void CRaumView::TriggerPit(CField* pTargetField, CActuator::ActionTypes type, boolean criticalWeightBreached) {
	CPit* pPit = pTargetField->HolePit();
	if (pPit) {
		switch (type)
		{
		case CActuator::Set:
			if (criticalWeightBreached) {
				pPit->Open(0);
			}
			break;
		case CActuator::Toggle:
			if (criticalWeightBreached) {
				pPit->Toggle();
			}
			break;
		case CActuator::Clear:
			if (criticalWeightBreached) {
				pPit->Close(0); 
			}
			break;
		case CActuator::Hold:
			pPit->Toggle();
			break;
		}
	}
}

void CRaumView::TriggerMissileShooter(CField* pTargetField, CActuator* actuator, boolean criticalWeightBreached) {
	if (actuator->GetType() == 8)
	{
		CActuator::ActionTypes type = actuator->GetActionType();
		switch (type)
		{
		case CActuator::Set:
			if (criticalWeightBreached) {
				actuator->Activate();
			}
			break;
		case CActuator::Toggle:
			if (criticalWeightBreached) {
				if (actuator->IsActive())
				{
					actuator->Deactivate();
				}
				else {
					actuator->Activate();
				}
			}
			break;
		case CActuator::Clear:
			if (criticalWeightBreached) {
				actuator->Deactivate();
			}
			break;
		case CActuator::Hold:
			actuator->Activate();
			break;
		}
	}
	
}

void CRaumView::TriggerDoor(CField* pTargetField, CActuator::ActionTypes type, boolean criticalWeightBreached) {
	CDoor* pDoor = pTargetField->HoleDoor(); // todo das kann nicht nur eine Tür treffen!
	if (pDoor != NULL) {
		switch (type)
		{
		case CActuator::Set:
			if (criticalWeightBreached) {
				pDoor->Open();
			}
			break;
		case CActuator::Toggle:
			if (criticalWeightBreached) {
				pDoor->Toggle();
			}
			break;
		case CActuator::Clear:
			if (criticalWeightBreached) {
				pDoor->Close(); // TODO ???
			}
			break;
		case CActuator::Hold:
			pDoor->Toggle(); // toggle für stein auf platte - loop?
			break;
		}
	}
}

void CRaumView::TriggerTeleport(CField* pTargetField, CActuator::ActionTypes type, boolean criticalWeightBreached, boolean triggerRotate) {
	CGrpHeld* pGrpHeroes = m_pMap->GetHeroes();
	VEKTOR heroPos = pGrpHeroes->GetVector(); // Namen angleichen - HolePos etc
	CTeleporter* pTeleport = pTargetField->HoleTeleporter(); 
	VEKTOR newPos = heroPos;
	if (pTeleport != NULL) {
		switch (type)
		{
		case CActuator::Set:
			if (criticalWeightBreached) {
				pTeleport->setOpen(CTeleporter::Active, 0);
				pTeleport->Trigger(m_pDoc, m_pMap, pTargetField->HolePos(), triggerRotate);
			}
			break;
		case CActuator::Toggle:
			if (criticalWeightBreached) {
				pTeleport->toggleOpen();
				if (pTeleport->isOpen()) {
					pTeleport->Trigger(m_pDoc, m_pMap, pTargetField->HolePos(), triggerRotate);
				}
			}
			break;
		case CActuator::Clear:
			if (criticalWeightBreached) {
				pTeleport->setOpen(CTeleporter::Inactive, 0); 
			}
			break;
		case CActuator::Hold:
			pTeleport->Trigger(m_pDoc, m_pMap, pTargetField->HolePos(), triggerRotate); // todo prüfen 
			break;
		}
	}
}

void CRaumView::TriggerActuatorsNearby() {
	VEKTOR held = m_pMap->GetHeroes()->GetVector();
	for (int i = max(held.x - 4, 0); i < min(held.x + 4, m_pMap->GetMaxWidth(held.z)); i++) {
		for (int j = max(held.y - 4, 0); j < min(held.y + 4, m_pMap->GetMaxHeight(held.z)); j++) {
			TriggerPassiveActuators(VEKTOR{ i, j, held.z }, held);
			CheckOtherDelays(VEKTOR{ i, j, held.z });
			// todo: Teleporter passiv triggern = prüfen, wer auf dem feld ist, und falls aktiv teleportieren
			// dafür restliche trigger alle raus !
		}
	}
}

VEKTOR CRaumView::MonsterMoveOrAttack(CGrpMonster* pGrpMon) {
	// Prüfen: Held angreifbar? Erstmal nur Nahkampf!
	CGrpHeld* pGrpHeroes = m_pMap->GetHeroes();
	VEKTOR heroPos = pGrpHeroes->GetVector();
	VEKTOR monPos = pGrpMon->GetVector();
	VEKTOR targetPos;
	if (pGrpMon->GetVector().z != heroPos.z) return monPos; // Falsche Etage, nix tun!

	if (pGrpMon->IsScared()) {
		targetPos = pGrpMon->HoleZielFeld(RUECKWAERTS);
		boolean collision = false;
		Betrete(targetPos, collision);
		pGrpMon->ScaredAction(targetPos, collision);
	}
	else {
		// Versuch, in Blickrichtung zu gehen, ggf. Angriff!
		targetPos = pGrpMon->HoleZielFeld(VORWAERTS);
		CField* targetField = m_pMap->GetField(targetPos);
		COMPASS_DIRECTION heroRicht = pGrpHeroes->GetDirection();

		int xDist = monPos.x - heroPos.x;
		int yDist = monPos.y - heroPos.y;
		int absDist = abs(xDist) + abs(yDist);
		if (targetPos.x == heroPos.x && targetPos.y == heroPos.y) {
			CMonster* attackingMonster = pGrpMon->AttackHero(monPos, heroPos);
			if (attackingMonster)
			{
				switch (pGrpMon->GetType()) {
				case MonsterTyp::SKELETON:
					m_pDoc->PlayDMSound("C:\\Users\\micha\\source\\repos\\DungeonMaster\\sound\\DMCSB-SoundEffect-Attack(Skeleton-AnimatedArmour-PartySlash).mp3");
				case MonsterTyp::SCREAMER:
					m_pDoc->PlayDMSound("C:\\Users\\micha\\source\\repos\\DungeonMaster\\sound\\DMCSB-SoundEffect-Attack(Screamer-Oitu).mp3"); break;
				case MonsterTyp::ROCKPILE:
					m_pDoc->PlayDMSound("C:\\Users\\micha\\source\\repos\\DungeonMaster\\sound\\DMCSB-SoundEffect-Attack(Rockpile).mp3"); break;
				case MonsterTyp::MAGENTA_WORM:
					m_pDoc->PlayDMSound("C:\\Users\\micha\\source\\repos\\DungeonMaster\\sound\\DMCSB-SoundEffect-Attack(MagentaWorm).mp3"); break;
				case MonsterTyp::MUMMY:
				case MonsterTyp::GHOST:
					m_pDoc->PlayDMSound("C:\\Users\\micha\\source\\repos\\DungeonMaster\\sound\\DMCSB-SoundEffect-Attack(Mummy-Ghost).mp3"); break;
				case MonsterTyp::GIGGLER:
					m_pDoc->PlayDMSound("C:\\Users\\micha\\source\\repos\\DungeonMaster\\sound\\DMCSB-SoundEffect-Attack(Giggler).mp3"); break;
				case MonsterTyp::TROLIN:
					m_pDoc->PlayDMSound("C:\\Users\\micha\\source\\repos\\DungeonMaster\\sound\\DMCSB-SoundEffect-Attack(Trolin-StoneGolem)-TouchingWall.mp3"); break;
				case MonsterTyp::PAINRAT:
					m_pDoc->PlayDMSound("C:\\Users\\micha\\source\\repos\\DungeonMaster\\sound\\DMCSB-SoundEffect-Attack(PainRat-RedDragon).mp3"); break;
				}
				pGrpHeroes->DamageFrom(attackingMonster, pGrpMon->GetVector(), false);

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
					if (pDoor->getState() != CDoor::OPEN && pDoor->getState() != CDoor::DESTROYED)
						return monPos; // Tür im Weg
				}

				if (absDist > targetDist)
				{
					// Kommt näher => Move!

					pGrpMon->Laufen(targetPos, false);
					switch (pGrpMon->GetType()) {
					case MonsterTyp::SKELETON:
						m_pDoc->PlayDMSound("C:\\Users\\micha\\source\\repos\\DungeonMaster\\sound\\DMCSB-SoundEffect-Move(Skeleton).mp3"); break;
					case MonsterTyp::SCREAMER:
					case MonsterTyp::ROCKPILE:
					case MonsterTyp::MAGENTA_WORM:
					case MonsterTyp::PAINRAT:
						m_pDoc->PlayDMSound("C:\\Users\\micha\\source\\repos\\DungeonMaster\\sound\\DMCSB-SoundEffect-Move(Screamer-Rockpile-MagentaWorm-PainRat-Ruster-GiantScorpion-Oitu).mp3"); break;
					case MonsterTyp::MUMMY:
					case MonsterTyp::GIGGLER:
					case MonsterTyp::TROLIN:
						m_pDoc->PlayDMSound("C:\\Users\\micha\\source\\repos\\DungeonMaster\\sound\\DMCSB-SoundEffect-Move(Mummy-Trolin-StoneGolem-Giggler-Vexirk-Demon).mp3"); break;
					case MonsterTyp::GHOST:
						break;
					}
					

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
	m_pChampionPortraits = new CChampionPortrait(pDC);

	
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

void CRaumView::DoActionForChosenHero(CGrpHeld* pGrpHero, int ActionId) {
	VEKTOR monPos = pGrpHero->HoleZielFeld(VORWAERTS);
	CHeld* pHero = (CHeld*)pGrpHero->GetHeroForAction();
	CGrpMonster* pVictims = GetMonsterGroup(monPos);
	CAttackInfos* attackInfos = GetAttackInfos();
	CMonsterInfos* monsterInfos = GetMonsterInfos();
	CField* field = GetMap()->GetField(monPos);
	int diff = GetMap()->GetLevelDifficulty(monPos.z);
	if (pHero) {
		if (pHero->isAlive()) {
			CItem* item = pHero->GetItemCarrying(1);
			VEKTOR myPos = pGrpHero->GetVector();
			CWeapon* weapon = NULL;
			CString attackType;
			if (item && item->getItemType() == CItem::ItemType::WeaponItem) {
				weapon = (CWeapon*)item;
				attackType = weapon->GetAttributes().style[ActionId - 1].type;
			}
			else {
				/*CWeaponAttributes att;
				att.fixAttributes.damage = 1;
				weapon = new CWeapon(HANDINDEX, att);*/
				attackType = "N"; // Punch / Kick / Warcry
			}
			if (attackType == "") 
			{
				return;
			}
			
			CAttackConst ac = attackInfos->GetAttack(attackType);

			if (attackType == "throw")
			{
				SUBPOS_ABSOLUTE abspos = pHero->HoleSubPosition();
				SUBPOS pos = CHelpfulValues::GetRelativeSubPosPassive(abspos, pGrpHero->GetDirection());
				if (pGrpHero->ThrowItemInHeroHand(pHero, field, pos)) {
					m_pDoc->PlayDMSound("C:\\Users\\micha\\source\\repos\\DungeonMaster\\sound\\DMCSB-SoundEffect-Attack(Skeleton-AnimatedArmour-PartySlash).mp3");
					pGrpHero->setPhaseDelay(2);
					pGrpHero->setPhase(SHOW_DAMAGE);
				}
			}
			else {

				if (pVictims) {
					if ((attackType == "N") && (ActionId == 3)) {
						// Warcry
						pVictims->Scare();
						pGrpHero->setPhaseDelay(2);
						pGrpHero->setPhase(SHOW_DAMAGE);
					}
					else {
						// Nahkampf!
						CMonsterConst mc = monsterInfos->GetMonsterInfo(pVictims->GetType());
						int dmg = pHero->CalcDmg(weapon, ac, mc, diff);
						if (dmg > 0) {
							pVictims->DoDamage(dmg, myPos, false); // true = Schaden an alle
							pHero->AttackModeWithDmg(dmg);
							pGrpHero->setPhaseDelay(2);
							pGrpHero->setPhase(SHOW_DAMAGE);
						}
						else {
							pGrpHero->setPhaseDelay(2);
							pGrpHero->setPhase(CHOOSE_HERO);
						}
					}
					/*
					int itemIndex = -1;
					if (item && item->getItemType() == CItem::ItemType::WeaponItem) {
						itemIndex = item->getIndex();
					}
					else if (item == NULL) {
						itemIndex = HANDINDEX;
					}
					if (itemIndex >= 0) {
						CAttackConst ac = attackInfos->GetAttack(itemIndex);
						int dmg = pHero->CalcDmg(ac, pVictims, myPos.z);
						pVictims->DoDamage(dmg, myPos, false); // true = Schaden an alle
						pHero->AttackModeWithDmg(dmg);
						m_iPhase = 3;
						m_iPhaseDelay = 2;
					}*/
				}
				else {
					CDoor* pDoor = field->HoleDoor();
					if (pDoor && pDoor->destroyedByForce() && pDoor->getState() == CDoor::CLOSED)
					{
						pDoor->SetState(CDoor::DESTROYED);
					}
					// kein Gegner!
					pGrpHero->setPhase(CHOOSE_HERO);
				}
			}
			pHero->setDelay(max(2, ac.fatigue));
		}
	}

}

CBitmap* CRaumView::GetHeroPic(int heroId) {
	CBitmap* heroPic = m_pChampionPortraits->GetChampions();
	CPoint koord = m_pChampionPortraits->GetKoords(heroId);

	/*CDC* pDC = GetDC();
	CDC tmpdc;
	tmpdc.CreateCompatibleDC(pDC);
	tmpdc.SelectObject(heroPic);

	pDC->TransparentBlt(0, 0, 32 * 2, 29 * 2, &tmpdc, koord.x, koord.y, 32, 29, TRANS_GRE);
	tmpdc.DeleteDC();*/

	return heroPic;
}