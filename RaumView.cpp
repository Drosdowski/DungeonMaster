// RaumView.cpp : implementation file
//


#include "stdafx.h"
#include <stack>
#include "CHelpfulValues.h"
#include "DmDoc.h"
#include "Feld.h"
#include "Items/CMiscellaneous.h"
#include "RaumView.h"
#include "CDungeonMap.h"
#include "SpecialTile/CStairs.h"
#include "SpecialTile/CPit.h"
#include "Items\Decoration.h"
#include "Items\CFloorOrnate.h"
#include "Pictures\CPictures.h"
#include "Pictures\CDoorPic.h"
#include "Pictures\CWallPic.h"
#include "Pictures/CStairsPic.h"
#include "Pictures/CPitPic.h"
#include "Pictures\CLeverPic.h"
#include "Pictures/CPressurePadPic.h"
#include "Pictures/CFloorOrnatePic.h"
#include "Pictures\CFountainPic.h"
#include "Pictures\Creatures\CMonsterPic.h"
#include "Pictures\Items3D\CItem3DPic.h"
#include "Mobs\Monster.h"
#include "Mobs\MobGroups\GrpMonster.h"
#include "Mobs\MobGroups\GrpHeld.h"

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
	m_pDoc = NULL;
	m_pDoorPic = NULL;
	m_pWallPic = NULL;
	m_pStairsPic = NULL;
	m_pPitPic = NULL;
	m_pPressurePadPic = NULL;
	m_pOrnatePic = NULL;
	m_pLeverPic = NULL;
	m_pPictures = NULL;
	m_pFountainPic = NULL;
	m_pMonsterPic = NULL;
	m_pItem3DPic = NULL;
}

CRaumView::~CRaumView()
{
	delete m_pMap;
	delete m_values;
	delete m_pDoorPic;
	delete m_pStairsPic;
	delete m_pPitPic;
	delete m_pWallPic;
	delete m_pPressurePadPic;
	delete m_pOrnatePic;
	delete m_pLeverPic;
	delete m_pFountainPic;
	delete m_pMonsterPic;
	delete m_pItem3DPic;
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

void CRaumView::DrawFloorPit(CDC *pDC, CDC* cdc, int xxx, int ebene, CPit* pit) {
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

void CRaumView::DrawStairsFront(CDC* pDC, CDC* cdc, int xxx, int ebene, CStairs* pStairs)
{
	BITMAP bmpInfo;
	CPoint pos;
	CBitmap* bmp;
	if (pStairs == NULL) return;

	if (pStairs->GetType() == CStairs::UP) {
		bmp = m_pStairsPic->GetStairUpFrontPic(xxx, ebene);
		pos = m_pStairsPic->GetStairsUpFrontPos(xxx, ebene, m_pWallPic->GetWallPos(xxx, ebene));
	} else {
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


void CRaumView::DrawDoor(CDC* pDC, CDC* cdc, int xxx, int ebene, int richt, CDoor* pDoor) {
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

void CRaumView::DrawWall(CDC* pDC, CDC* cdc, int xxx, int ebene, int richt, CField* pField) {
	BITMAP bmpDecoInfo;
	BITMAP bmpInfo;

	CBitmap* bmp = m_pWallPic->GetWallPic(xxx, ebene, m_bMirror);
	int xx = wallXFactor[xxx];

	CFieldDecoration* frontDeco = pField->HoleDeko(CHelpfulValues::OppositeDirection(richt));
	CFieldDecoration* sideDeco;
	if (xx > 0)
	{
		sideDeco = pField->HoleDeko((4 + 2 - richt) % 4);
	}
	else if (xx < 0) {
		sideDeco = pField->HoleDeko((4 - richt) % 4);
	}
	else {
		sideDeco = NULL;
	}
	
	cdc->SelectObject(bmp);
	CPoint pos = m_pWallPic->GetWallPos(xxx, ebene);
	double faktor = m_pPictures->getFaktor(ebene);

	bmp->GetBitmap(&bmpInfo);

	pDC->TransparentBlt(pos.x, pos.y, bmpInfo.bmWidth * 2, bmpInfo.bmHeight * 2, cdc, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, TRANS_VIO);

	// Deko auf FRONT Wand zeichnen
	if (frontDeco->GetDecoType() != None)
	{
		CBitmap* decoBmp = NULL;
		if (((xxx == 4) && (ebene == 1)) ||
			((xxx > 1) && (ebene == 2)) ||
			(ebene == 3)) {
			if (frontDeco->GetDecoType() == Switch) {
				decoBmp = m_pLeverPic->GetLeverFront(frontDeco->GetState());
			}
			else if (frontDeco->GetDecoType() == Fountain) {
				decoBmp = m_pFountainPic->GetFountainFront();
			}
		}

		CPoint center = m_pWallPic->GetCenterFromFrontWall(xxx, ebene);
		if (decoBmp && center.x > 0 && center.y > 0) {
			cdc->SelectObject(decoBmp);
			decoBmp->GetBitmap(&bmpDecoInfo);
			int decoPosX = pos.x + center.x - (int)(bmpDecoInfo.bmWidth * faktor);
			int decoPosY = pos.y + center.y - (int)(bmpDecoInfo.bmHeight * faktor);

			DrawInArea(decoPosX, decoPosY, bmpDecoInfo.bmWidth, bmpDecoInfo.bmHeight, faktor, pDC, cdc, TRANS_ORA);

		}
	}
	// Deko auf SIDE Wand zeichnen
	if (xx != 0)
		if (sideDeco->GetDecoType() != None)
		{
			if (ebene > 0 && xxx < 4) {
				CBitmap* decoBmp = NULL;
				if (frontDeco->GetDecoType() == Switch) {
					decoBmp = m_pLeverPic->GetLeverSide(sideDeco->GetState(), (xx > 0));
				}
				else if (frontDeco->GetDecoType() == Fountain) {
					decoBmp = m_pFountainPic->GetFountainSide(xx > 0);
				}

				CPoint center = m_pWallPic->GetCenterFromSideWall(xxx, ebene);
				if (decoBmp && center.x > 0 && center.y > 0) {
					cdc->SelectObject(decoBmp);
					decoBmp->GetBitmap(&bmpDecoInfo);
					int decoPosX = pos.x + center.x; // die Mitte für die linke Seite ist links im Bild, also nix abziehen
					if (xx > 0)
						decoPosX -= (int)(bmpDecoInfo.bmWidth * 2 * faktor);
					int decoPosY = (int)(pos.y + center.y - bmpDecoInfo.bmHeight * faktor);

					DrawInArea(decoPosX, decoPosY, bmpDecoInfo.bmWidth, bmpDecoInfo.bmHeight, faktor, pDC, cdc, TRANS_ORA);
				}
			}
		}
}

void CRaumView::DrawMonsterGroup(CDC* pDC, CDC* cdc, int xxx, int ebene, int richt, CField* pField) {
	CGrpMonster* pGrpMon = (CGrpMonster*)pField->GetMonsterGroup();
	if (pGrpMon)
	{
		int xx = wallXFactor[xxx];

		DrawMonster(pDC, cdc, xx, ebene, richt, pGrpMon->GetMonsterByRelSubPos(LINKSHINTEN, richt));
		DrawMonster(pDC, cdc, xx, ebene, richt, pGrpMon->GetMonsterByRelSubPos(RECHTSHINTEN, richt));
		DrawMonster(pDC, cdc, xx, ebene, richt, pGrpMon->GetMonsterByRelSubPos(LINKSVORNE, richt));
		DrawMonster(pDC, cdc, xx, ebene, richt, pGrpMon->GetMonsterByRelSubPos(RECHTSVORNE, richt));
	}
}

void CRaumView::DrawMonster(CDC* pDC, CDC* cdc, int xx, int ebene, int richt, CMonster* pMonster) {
	if (pMonster && pMonster->Hp() > 0) // todo staubwolke hier berücksichtigen
	{
		CBitmap* bmp = m_pMonsterPic->GetBitmap(pMonster, richt);
		BITMAP bmpInfo;

		//get original size of bitmap
		bmp->GetBitmap(&bmpInfo);
		double faktor = m_pPictures->getFaktor(ebene);

		SUBPOS subPos = CHelpfulValues::GetRelativeSubPosPassive(pMonster->HoleSubPosition(), richt);
		CPoint pos = CHelpfulValues::CalcSubPosition(bmpInfo, subPos, faktor, xx);

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
	
	std::stack<CActuator*> actuators = pField->GetActuator((SUBPOS_ABSOLUTE)0);  // Boden hat immer POsition 0.
	while (!actuators.empty()) {
		CActuator* actuator = actuators.top();
		if (actuator->GetType() == 3) {
			DrawSquarePressurePad(pDC, cdc, xxx, ebene, actuator);
		}
		actuators.pop();
	}

	CFloorOrnate* floorDeco = pField->HoleFloorDeco(); // Feld Deko immer an Pos 0
	if (floorDeco) // && floorDeco->GetType() != None)
	{
		CBitmap* decoBmp = NULL;
		if (floorDeco->GetType() == Moss) {
			decoBmp = m_pOrnatePic->GetMossPic(ebene, xxx);
		} 
		else if (floorDeco->GetType() == Puddle) {
			decoBmp = m_pOrnatePic->GetPuddlePic(ebene, xxx);
		}
		//CPoint center = m_pItem3DPic->GetFloorMiddle(xxx, ebene);
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

void CRaumView::DrawPile(CDC* pDC, CDC* cdc, int xxx, int ebene, SUBPOS_ABSOLUTE itemSubPos, int heroDir, std::stack<CMiscellaneous*> pile) {
	// TODO - besser als "nur oberstes Malen... "
	CMiscellaneous* misc = pile.top();
	if (misc) {
		int xx = wallXFactor[xxx]; // 0,1,2,3,4 => -2,2,-1,1,0
	
		CBitmap* bmp;
		if (misc->GetType() == CMiscellaneous::ItemType::Apple)
			bmp = m_pItem3DPic->GetApple();
		else
			bmp = m_pItem3DPic->GetBread();

		BITMAP bmpInfo;
		bmp->GetBitmap(&bmpInfo);
		double faktor = m_pPictures->getFaktor(ebene);

		CPoint floorMiddlePos = m_pItem3DPic->GetFloorMiddle(xxx, ebene);
		if (floorMiddlePos.x > 0 || floorMiddlePos.y > 0) {
			SUBPOS subPos = CHelpfulValues::GetRelativeSubPosPassive(itemSubPos, heroDir); // todo subpos angleichen
			if (ebene > 0 || subPos == LINKSHINTEN || subPos == RECHTSHINTEN)
			{			
				if (subPos == LINKSHINTEN || subPos == RECHTSHINTEN)
				{
					faktor = m_pPictures->getFaktor(ebene+1);
				}
				CPoint pos = CHelpfulValues::CalcRelSubFloorPosition(bmpInfo, floorMiddlePos, subPos, faktor, xx, ebene);
				if (misc->IsFlying() && pos.y != 0) {
					pos.y = 250 - pos.y / 2; 
				}
				cdc->SelectObject(bmp);
				DrawInArea(pos.x, pos.y, bmpInfo.bmWidth, bmpInfo.bmHeight, faktor, pDC, cdc, TRANS_ORA);
				/*test(pDC, 130, 370);
				test(pDC, 150, 325);
				test(pDC, 165, 300);
				test(pDC, 177, 280);
				test(pDC, 185, 265);
				test(pDC, 191, 255);

				test(pDC, 320, 370);
				test(pDC, 300, 325);
				test(pDC, 285, 300);
				test(pDC, 273, 280);
				test(pDC, 265, 265);
				test(pDC, 259, 255);*/
			}
		}
	}
}


void CRaumView::DrawInArea(int x, int y, int w, int h, double faktor, CDC* pDC, CDC* cdc, COLORREF col) {
	int rechterRand = (int)(w * 2 * faktor + x);
	int reducedWidth = w;
	if (rechterRand > MainAreaWidth)
	{
		reducedWidth -= (int)((rechterRand - MainAreaWidth) / (2 * faktor));
	}

	if (reducedWidth > 0)
	{
		pDC->TransparentBlt(x, y,
			(int)(reducedWidth * 2 * faktor), (int)(h * 2 * faktor),
			cdc, 0, 0, reducedWidth, h, col);
	}
}

void CRaumView::Zeichnen(CDC* pDC)
{
	CDC compCdc;
	compCdc.CreateCompatibleDC(pDC);

//	lpDDSPrimary->BltFast( 0, 0, lpDDSOffOne, NULL, DDBLTFAST_WAIT);

	compCdc.SelectObject(m_pPictures->GetHintergrund());

	pDC->BitBlt(0, 0, 640, 400, &compCdc, 0, 0, SRCCOPY);
	if (m_bMirror) {
		pDC->StretchBlt(0, 64, MainAreaWidth, 269, &compCdc, MainAreaWidth, 64, -MainAreaWidth, 269, SRCCOPY);
	}

	int x = m_pMap->GetHeroes()->HolePosition().x;
	int y = m_pMap->GetHeroes()->HolePosition().y;
	int z = m_pMap->GetHeroes()->HolePosition().z;

	int heroDir = m_pMap->GetHeroes()->HoleRichtung();
	int stx = m_values->m_stx[heroDir];
	int sty = m_values->m_sty[heroDir];

	for (int ebene = 3; ebene >= 0; ebene--)
	{
		for (int xxx = 0; xxx <= 4; xxx++)
		{
			if (ebene > 1 || xxx > 1)
			{ // nur für Ebene 2&3 sind Außenwerte -2 / 2 zu zeichnen - far left  & far right
				int xx = wallXFactor[xxx]; // 0,1,2,3,4 => -2,2,-1,1,0
				int addx = x + ebene * sty + xx * stx;
				int addy = y - ebene * stx + xx * sty;
				CField* pField = m_pMap->GetField(addx,addy,z);
				int fieldType = pField->HoleTyp();
							
				// TODO prüfe z -1 ob PIT
				if (fieldType == FeldTyp::WALL && ((ebene != 0) || (xx != 0)))
				{
					DrawWall(pDC, &compCdc, xxx, ebene, heroDir, pField);
				}
				else if (fieldType == FeldTyp::DOOR )
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
						pit->GetState() == CPit::PitState::Open) {
						DrawFloorPit(pDC, &compCdc, xxx, ebene, pit);
					}

				}
				else if (fieldType == FeldTyp::EMPTY) {
					// Platten, Pfützen, Fussabdrücke, Pit, ...
					DrawOnFloor(pDC, &compCdc, xxx, ebene, pField);
				}

				if (fieldType != FeldTyp::WALL) {
					for (int pos = 0; pos < 4; pos++)
					{
						std::stack<CMiscellaneous*> pile = pField->GetMisc((SUBPOS_ABSOLUTE)pos);
						if (pile.size() > 0) {
							DrawPile(pDC, &compCdc, xxx, ebene, (SUBPOS_ABSOLUTE)pos, heroDir, pile);
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
		if (pit->GetState() == CPit::PitState::Open) {
			CGrpHeld* pGrpHelden = m_pMap->GetHeroes();
			toPos.z++;
			pGrpHelden->FallingDamage();
			// todo sound
		}
		return toPos;
	}
	else if (iTyp == FeldTyp::STAIRS) {
		CStairs* stairs = pField->HoleStairs();
		if (stairs->GetType() == CStairs::StairType::DOWN)
		{
			toPos.z++;			
		}
		else {
			toPos.z--;
		}
		toPos.x += (m_pMap->GetOffset(fromPos.z).x - m_pMap->GetOffset(toPos.z).x);
		toPos.y += (m_pMap->GetOffset(fromPos.z).y - m_pMap->GetOffset(toPos.z).y);
		// neue Richtung: Blick auf das einzige EMPTY Feld neben Hero

		for (int i = -1; i <= 1; i += 2) {
			if (!m_pMap->GetField(toPos.x + i, toPos.y, toPos.z)->HoleTyp() == FeldTyp::WALL) {
				CGrpHeld* pGrpHelden = m_pMap->GetHeroes();
				pGrpHelden->SetzeRichtung((i == -1) ? 3 : 1);
			}
			if (!m_pMap->GetField(toPos.x, toPos.y + i, toPos.z)->HoleTyp() == FeldTyp::WALL) {
				CGrpHeld* pGrpHelden = m_pMap->GetHeroes();
				pGrpHelden->SetzeRichtung((i == -1) ? 0 : 2);
			}

		}

		return toPos;
	}
	else // hier div. Abfragen für Teleporter, u.ä. 
	{
		
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
		else if (pGrpMon->IstBereit())
		{
			VEKTOR target = MonsterMoveOrAttack(pGrpMon);
			if (target.x != heroPos.x || target.y != heroPos.y) {
				CField* targetField = m_pMap->GetField(target);
				field->SetMonsterGroup(NULL);
				targetField->SetMonsterGroup(pGrpMon);
			}
			pGrpMon->ActionDone();
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
			pDoor->Toggle();
		}
	}
}

void CRaumView::PrepareMoveItems(VEKTOR heroPos) {
	CField* field = m_pMap->GetField(heroPos);
	// Flag setzen, Item muss sich ggf. noch bewegen
	for (int s = 0; s < 4; s++) {
		SUBPOS_ABSOLUTE posAbs = (SUBPOS_ABSOLUTE)s;
		std::stack<CMiscellaneous*> pile = field->GetMisc(posAbs);
		if (!pile.empty()) {
			CMiscellaneous* topItem = pile.top();
			topItem->ResethasMoved();
		}
	}
}

void CRaumView::MoveItems(VEKTOR heroPos) {
	CField* field = m_pMap->GetField(heroPos);
	
	for (int s = 0; s < 4; s++) {
		SUBPOS_ABSOLUTE posAbs = (SUBPOS_ABSOLUTE)s;
		std::stack<CMiscellaneous*> pile = field->GetMisc(posAbs);
		if (!pile.empty()) {
			CMiscellaneous* topItem = pile.top(); // todo prüfen, reicht es, nur das oberste anzuschauen, gibt es > 1 fliegende Items je Feld
			if (topItem->IsFlying() && !topItem->HasMovedThisTick()) {
				// fliegendes Item gefunden
				SUBPOS_ABSOLUTE newPos = CHelpfulValues::FindNextSubposWithoutFieldChange(posAbs, topItem->m_flyForce);

				if (newPos == MIDDLE) {
					// Feld verlassen
					CField* newField = m_pMap->GetField(heroPos.x + sign(topItem->m_flyForce.x), heroPos.y + sign(topItem->m_flyForce.y), heroPos.z);
					if (!newField->Blocked()) {
						// westlich von west ist ost => anders rum subpos suchen
						topItem = field->TakeMisc(posAbs);
						newPos = CHelpfulValues::FindNextSubposWithoutFieldChange(posAbs, VEKTOR{ -topItem->m_flyForce.x, -topItem->m_flyForce.y, 0 });
						newField->PutMisc(topItem, newPos);
					}
					else {
						// nicht bewegen, sondern stehen bleiben (unten)
						topItem->m_flyForce = { 0,0,0 };
					}
				}
				else {
					topItem = field->TakeMisc(posAbs);
					topItem->ReduceSpeed();
					field->PutMisc(topItem, newPos);
				}
			}
		}
	}
}

void CRaumView::MoveAnythingNearby() {
	VEKTOR held = m_pMap->GetHeroes()->GetPos();
	for (int i = max(held.x - 4, 0); i < min(held.x + 4, m_pMap->GetMaxWidth(held.z)); i++) {
		for (int j = max(held.y - 4, 0); j < min(held.y + 4, m_pMap->GetMaxHeight(held.z)); j++) {
			VEKTOR heroPos = { i, j, held.z };
			MoveMonsters(heroPos);
			MoveDoors(heroPos);
			PrepareMoveItems(heroPos);
			MoveItems(heroPos);
		}
	}
}

void CRaumView::TriggerActuators(VEKTOR fieldPos, VEKTOR heroPos) {
	CField* field = m_pMap->GetField(fieldPos);
	std::stack<CActuator*> actuators = field->GetActuator((SUBPOS_ABSOLUTE)0);
	while (!actuators.empty()) {
		CActuator* actuator = actuators.top();
		TriggerActuator(heroPos, field, actuator, (SUBPOS_ABSOLUTE)0);
		actuators.pop();
	}
}

void CRaumView::TriggerActuator(VEKTOR heroPos, CField* field , CActuator* actuator, SUBPOS_ABSOLUTE pos) {
	bool criticalWeightChanged = field->CriticalWeightChange(heroPos, actuator->GetCriticalWeigth()); // todo parameter optimieren?
	
	if (criticalWeightChanged) {
		switch (actuator->GetType()) {
		case 3:
			VEKTOR target = actuator->GetActionTarget(pos);
			CActuator::ActionTypes type = actuator->GetActionType(pos);
			// TODO: type auswerten!
			CField* pTargetField = m_pMap->GetField(target);
			CDoor* pDoor = pTargetField->HoleDoor(); // todo das kann nicht nur eine Tür treffen!
			switch (type)
			{
			case CActuator::Set:
				if (pDoor != NULL) {
					pDoor->Open();
				}
				break;
			case CActuator::Toggle:
				if (pDoor != NULL) {
					pDoor->Toggle();
				}
				break;
			case CActuator::Clear:
				if (pDoor != NULL) {
					pDoor->Close(); // TODO ???
				}
				break;
			}
			break;
		}
	}

}

void CRaumView::TriggerActuatorsNearby() {
	VEKTOR held = m_pMap->GetHeroes()->GetPos();
	for (int i = max(held.x - 4, 0); i < min(held.x + 4, m_pMap->GetMaxWidth(held.z)); i++) {
		for (int j = max(held.y - 4, 0); j < min(held.y + 4, m_pMap->GetMaxHeight(held.z)); j++) {
			TriggerActuators(VEKTOR{ i, j, held.z }, held);
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

	int heroRicht = m_pMap->GetHeroes()->HoleRichtung();

	int xDist = monPos.x - heroPos.x;
	int yDist = monPos.y - heroPos.y;
	int absDist = abs(xDist) + abs(yDist);
	if (targetPos.x == heroPos.x && targetPos.y == heroPos.y) {
		CMonster* attackingMonster = pGrpMon->AttackHero(monPos, heroPos);
		if (attackingMonster)
		{
			m_pDoc->PlayDMSound("C:\\Source\\C++\\DM\\sound\\DMCSB-SoundEffect-Attack(Skeleton-AnimatedArmour-PartySlash).mp3");

			m_pMap->GetHeroes()->DamageFrom(attackingMonster, pGrpMon->HolePosition(), false);
		}
		return monPos;
	}
	else {
		pGrpMon->EndAttack(); // Attacke ggf. beenden
	}
	if (absDist == 1) {
		// Steht neben Held, falsch gedreht -> drehen!
		pGrpMon->TurnToHero(heroPos);
		return monPos;
	}
	// Nein: Bewege näher / drehe hin
	// todo: schlauer bewegungsalgorithmus!
		
	if ((targetPos.x != monPos.x || targetPos.y != monPos.y) && 
		(targetField->HoleTyp() == FeldTyp::EMPTY && targetField->GetMonsterGroup() == NULL) ||
		(targetField->HoleTyp() == FeldTyp::DOOR && targetField->GetMonsterGroup() == NULL)) // TODO nur Open!
		// Feld vorhanden - Monster drauf?
		// TODO: prüfen, ob Monster da sind, ggf. Merge

		if (absDist > (abs(targetPos.x - heroPos.x) + abs(targetPos.y - heroPos.y)))
		{
			// Kommt näher => Move!

			pGrpMon->Laufen(targetPos);
			m_pDoc->PlayDMSound("C:\\Source\\C++\\DM\\sound\\DMCSB-SoundEffect-Move(Skeleton).mp3");

			return targetPos;
		}
	// TODO stairs
	if (abs(xDist) >= abs(yDist)) {
		if (xDist > 0) {
			// Monster steht tendenziel rechts vom mir -> versuch nach links zu gehen (+drehen)
			// TODO
		}
	}

	return monPos;

}


void CRaumView::TriggerMoveAnimation() {
	m_bMirror = !m_bMirror;
}

bool CRaumView::OnStairs() {
	return m_pMap->GetField(m_pMap->GetHeroes()->HolePosition())->HoleTyp() == FeldTyp::STAIRS;
}

void CRaumView::InitDungeon(CDMDoc* pDoc, CDC* pDC, CPictures* pPictures)
{
	m_pDoc = pDoc;
	m_pPictures = pPictures;
	m_pDoorPic = new CDoorPic(pDC);
	m_pWallPic = new CWallPic(pDC);
	m_pStairsPic = new CStairsPic(pDC);
	m_pPitPic = new CPitPic(pDC);
	m_pLeverPic = new CLeverPic(pDC);
	m_pPressurePadPic = new CPressurePadPic(pDC);
	m_pOrnatePic = new CFloorOrnatePic(pDC);
	m_pFountainPic = new CFountainPic(pDC);
	m_pMonsterPic = new CMonsterPic(pDC);
	m_pItem3DPic = new CItem3DPic(pDC);
	m_pMap = new CDungeonMap();
	m_pMap->DemoMap();	
}

void CRaumView::OnTrigger()
{
	// Hier werden sämtliche Trigger angestoßen: Schalter, Türen, etc.

	int x = m_pMap->GetHeroes()->HolePosition().x;
	int y = m_pMap->GetHeroes()->HolePosition().y;
	int z = m_pMap->GetHeroes()->HolePosition().z;

	int richt = m_pMap->GetHeroes()->HoleRichtung();
	int addx = x + m_values->m_sty[richt];
	int addy = y - m_values->m_stx[richt];
	CField* feld = m_pMap->GetField(addx, addy, z);
	int iFeld = feld->HoleTyp();

	// Testweise. Space = Wand vor Spieler erzeugen/löschen

	if (iFeld == FeldTyp::WALL)
	{
		CFieldDecoration* deco = (feld->HoleDeko(CHelpfulValues::OppositeDirection(richt)));
		if (deco->GetDecoType() == Switch) {
			deco->SetState(1 - deco->GetState());
			m_pDoc->PlayDMSound("C:\\Source\\C++\\DM\\sound\\DMCSB-SoundEffect-Switch.mp3");
		} else if	(deco->GetDecoType() == Fountain) {
			m_pMap->GetHeroes()->DrinkFountain();
		}
	}
	else if (iFeld == FeldTyp::DOOR)
	{
		CDoor* door = feld->HoleDoor();
		if (door) {
			door->Toggle();
			m_pDoc->PlayDMSound("C:\\Source\\C++\\DM\\sound\\DMCSB-SoundEffect-Door.mp3");

		}
	}
	//else
		//feld->SetType(FeldTyp::WALL);
}

