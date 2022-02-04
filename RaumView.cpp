// RaumView.cpp : implementation file
//


#include "stdafx.h"
#include "DmDoc.h"
#include "Feld.h"
#include "RaumView.h"
#include "SpecialTile\Decoration.h"
#include "CDungeonMap.h"
#include "Pictures\CPictures.h"
#include "Pictures\CDoorPic.h"
#include "Pictures\CWallPic.h"
#include "Pictures/CStairsPic.h"
#include "Pictures\CLeverPic.h"
#include "Pictures\CFountainPic.h"
#include "Pictures\Creatures\CMonsterPic.h"
#include "CHelpfulValues.h"
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


IMPLEMENT_DYNCREATE(CRaumView, CView)

CRaumView::CRaumView()
{
	m_BlackBrush.CreateSolidBrush(RGB(0,0,0));
	
	wallXFactor[0] = -2;
	wallXFactor[1] = 2;
	wallXFactor[2] = -1;
	wallXFactor[3] = 1;
	wallXFactor[4] = 0;

	m_bMirror = true;

	m_values = new CHelpfulValues();
	m_pDoc = NULL;
	m_pDoorPic = NULL;
	m_pWallPic = NULL;
	m_pStairsPic = NULL;
	m_pLeverPic = NULL;
	m_pPictures = NULL;
	m_pFountainPic = NULL;
	m_pMonsterPic = NULL;
}

CRaumView::~CRaumView()
{
	delete m_pMap;
	delete m_values;
	delete m_pDoorPic;
	delete m_pStairsPic;
	delete m_pWallPic;
	delete m_pLeverPic;
	delete m_pFountainPic;
	delete m_pMonsterPic;
}


BEGIN_MESSAGE_MAP(CRaumView, CView)
	//{{AFX_MSG_MAP(CRaumView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRaumView drawing

void CRaumView::OnDraw(CDC* pDC)
{
	// CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CRaumView diagnostics

#ifdef _DEBUG
void CRaumView::AssertValid() const
{
	CView::AssertValid();
}

void CRaumView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

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
			pDC->TransparentBlt(pos.x, pos.y, bmpInfo.bmWidth * 2, bmpInfo.bmHeight * 2, cdc, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, RGB(208, 144, 112));
		}
	}
}

void CRaumView::DrawStairsSide(CDC* pDC, CDC* cdc, int xxx, int ebene, int richt, CField* pField)
{

}

void CRaumView::DrawStairsFront(CDC* pDC, CDC* cdc, int xxx, int ebene, CField* pField)
{
	BITMAP bmpInfo;
	CPoint pos;
	CBitmap* bmp;
	CStairs* pStairs = pField->HoleStairs();
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
			pDC->TransparentBlt(pos.x, pos.y, bmpInfo.bmWidth * 2, bmpInfo.bmHeight * 2, cdc, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, RGB(208, 144, 112));
		}
	}

}


void CRaumView::DrawDoor(CDC* pDC, CDC* cdc, int xxx, int ebene, int richt, CField* pField) {
	BITMAP bmpInfo;

	int xx = wallXFactor[xxx];
	CDoor* door = pField->HoleDoor();

	CPoint wallPos = m_pWallPic->GetWallPos(xxx, ebene);

	bool doorVisible = door->Visible(richt);
	if (doorVisible && ebene > 0)
	{
		CBitmap* bmp = m_pDoorPic->GetDoorTopPic(ebene);
			if (bmp) {
				cdc->SelectObject(bmp);
				CPoint pos = m_pDoorPic->GetDoorTopPos(xxx, ebene, wallPos);
				bmp->GetBitmap(&bmpInfo);

				DrawInArea(pos.x, pos.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 1, pDC, cdc, RGB(208, 144, 112));
			}
		DrawFrame(pDC, cdc, xxx, ebene, true); // left Frame
		DrawFrame(pDC, cdc, xxx, ebene, false); // right Frame
		bmp = m_pDoorPic->GetDoorFrontPic(door->getType(), ebene);
		if (bmp) {
			cdc->SelectObject(bmp);
			CPoint pos = m_pDoorPic->GetDoorFrontPos(xxx, ebene, wallPos);
			bmp->GetBitmap(&bmpInfo);
			int reducedWidth = min(bmpInfo.bmWidth, (MainAreaWidth - pos.x) / 2);
			int reducedHeight = bmpInfo.bmHeight - door->getDoorBottomHeight();
			pDC->TransparentBlt(pos.x, pos.y, reducedWidth * 2, reducedHeight * 2, cdc, 0, door->getDoorBottomHeight(), reducedWidth, reducedHeight, RGB(208, 144, 112));
		}
	}
	else if (!doorVisible && (ebene == 0) && (xx == 0)) {
		// innenrahmen!
		CBitmap* bmp = m_pDoorPic->GetDoorFrontPic(0, ebene);
		if (bmp) {
			cdc->SelectObject(bmp);
			CPoint pos = m_pDoorPic->GetDoorFrontPos(xxx, ebene, wallPos);
			bmp->GetBitmap(&bmpInfo);
			DrawInArea(pos.x, pos.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 1, pDC, cdc, RGB(208, 144, 112)); // TODO farbe auslagern

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

	pDC->TransparentBlt(pos.x, pos.y, bmpInfo.bmWidth * 2, bmpInfo.bmHeight * 2, cdc, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, RGB(255, 0, 255));

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

			DrawInArea(decoPosX, decoPosY, bmpDecoInfo.bmWidth, bmpDecoInfo.bmHeight, faktor, pDC, cdc, RGB(208, 144, 112));

		}
	}
	// Deko auf SIDE Wand zeichnen
	if (xx != 0)
		if (sideDeco->GetDecoType() != None)
		{
			if (ebene > 0 && xxx < 4) {
				CBitmap* decoBmp;
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

					DrawInArea(decoPosX, decoPosY, bmpDecoInfo.bmWidth, bmpDecoInfo.bmHeight, faktor, pDC, cdc, RGB(208, 144, 112));
				}
			}
		}
}

void CRaumView::DrawMonster(CDC* pDC, CDC* cdc, int xxx, int ebene, int richt, CField* pField) {
	CGrpMonster* pGrpMon = (CGrpMonster*)pField->GetMonsterGroup();
	if (pGrpMon)
	{
		int xx = wallXFactor[xxx];

		for (int i = 1; i < 5; i++)
		{		
			CMonster* monster = pGrpMon->GetMonsterByRelSubPos(i, richt); 
			if (monster && monster->Hp() > 0) // todo staubwolke hier berücksichtigen
			{
				CBitmap* bmp = m_pMonsterPic->GetBitmap(monster, richt);
				BITMAP bmpInfo;

				//get original size of bitmap
				bmp->GetBitmap(&bmpInfo);
				double faktor = m_pPictures->getFaktor(ebene);

				SUBPOS subPos = CHelpfulValues::GetRelativeSubPos(monster->HoleSubPosition(), richt);
				CPoint pos = CHelpfulValues::CalcSubPosition(bmpInfo, subPos, faktor, xx);		

				cdc->SelectObject(bmp);
				DrawInArea(pos.x, pos.y, bmpInfo.bmWidth, bmpInfo.bmHeight, faktor, pDC, cdc, monster->transCol);
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

	int x = m_pDoc->m_pGrpHelden->HolePosition().x;
	int y = m_pDoc->m_pGrpHelden->HolePosition().y;
	int z = m_pDoc->m_pGrpHelden->HolePosition().z;

	int richt = m_pDoc->m_pGrpHelden->HoleRichtung();
	int stx = m_values->m_stx[richt];
	int sty = m_values->m_sty[richt];

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
				
				if (fieldType == CField::FeldTyp::WALL && ((ebene != 0) || (xxx != 0)))
				{
					DrawWall(pDC, &compCdc, xxx, ebene, richt, pField);
				}
				else if (fieldType == CField::FeldTyp::DOOR )
				{
					DrawDoor(pDC, &compCdc, xxx, ebene, richt, pField);
				}
				else if (fieldType == CField::FeldTyp::STAIRS)
				{

					DrawStairsFront(pDC, &compCdc, xxx, ebene, pField);
				}
				else if (ebene > 0 && xxx > 1)
				{
					DrawMonster(pDC, &compCdc, xxx, ebene, richt, pField);
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

bool CRaumView::Betrete(VEKTOR pos)
{
	CField* pField = m_pMap->GetField(pos);
	CField::FeldTyp iTyp = pField->HoleTyp();
	if (iTyp == CField::FeldTyp::WALL)
		return true;
	else if (iTyp == CField::FeldTyp::DOOR)
	{
		CDoor* pDoor = pField->HoleDoor();
		if (pDoor->getState() != CDoor::DoorState::OPEN)
			return true;
	}
	else if (iTyp == CField::FeldTyp::EMPTY) {
		CGrpMonster* pGrpMonster = pField->GetMonsterGroup();
		if (pGrpMonster) return true;
	}
	else if (iTyp == CField::FeldTyp::STAIRS) {
		return true;
	}
	else // hier div. Abfragen für Teleporter, u.ä. 
	{
		
	}
	return false;
}

void CRaumView::MoveAnythingNearby() {
	VEKTOR held = m_pDoc->m_pGrpHelden->GetPos();
	for (int i = max(held.x - 4, 0); i < min(held.x + 4, m_pMap->GetMaxWidth(held.z)); i++) {
		for (int j = max(held.y - 4, 0); j < min(held.y + 4, m_pMap->GetMaxHeight(held.z)); j++) {
			CField* field = m_pMap->GetField(i, j, held.z);
			CGrpMonster* pGrpMon = field->GetMonsterGroup();
			if (pGrpMon)
			{
				if (!pGrpMon->Altern()) {
					// Gruppe ausgestorben!
					field->RemoveMonsterGroup();
				} else if (pGrpMon->IstBereit())
				{
					VEKTOR target = MonsterMoveOrAttack(pGrpMon);
					if (target.x != i || target.y != j) {
						CField* targetField = m_pMap->GetField(target);
						field->SetMonsterGroup(NULL);
						targetField->SetMonsterGroup(pGrpMon);
					}
					pGrpMon->ActionDone();
				}
			}
			CDoor* pDoor = field->HoleDoor();
			if (pDoor) {
				if ((pDoor->getState() == CDoor::DoorState::OPENING) ||
					(pDoor->getState() == CDoor::DoorState::CLOSING))
				{
					pDoor->Toggle();
				}
			}
		}
	}

}

VEKTOR CRaumView::MonsterMoveOrAttack(CGrpMonster* pGrpMon) {
	// Prüfen: Held angreifbar? Erstmal nur Nahkampf!
	VEKTOR heroPos = m_pDoc->m_pGrpHelden->GetPos();
	VEKTOR monPos = pGrpMon->GetPos();
	if (pGrpMon->GetPos().z != heroPos.z) return monPos; // Falsche Etage, nix tun!

	// Versuch, in Blickrichtung zu gehen, ggf. Angriff!
	VEKTOR target = pGrpMon->HoleZielFeld(VORWAERTS);
	CField* targetField = m_pMap->GetField(target);

	int heroRicht = m_pDoc->m_pGrpHelden->HoleRichtung();

	int xDist = monPos.x - heroPos.x;
	int yDist = monPos.y - heroPos.y;
	int absDist = abs(xDist) + abs(yDist);
	if (target.x == heroPos.x && target.y == heroPos.y) {
		pGrpMon->AttackHero(m_pDoc->m_pGrpHelden);
		m_pDoc->PlayDMSound("C:\\Source\\C++\\DM\\sound\\DMCSB-SoundEffect-Attack(Skeleton-AnimatedArmour-PartySlash).mp3");

		m_pDoc->m_pGrpHelden->DamageFrom(pGrpMon, false);
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
		
	if ((target.x != monPos.x || target.y != monPos.y) && 
		(targetField->HoleTyp() == CField::FeldTyp::EMPTY && targetField->GetMonsterGroup() == NULL) ||
		(targetField->HoleTyp() == CField::FeldTyp::DOOR && targetField->GetMonsterGroup() == NULL)) // TODO nur Open!
		// Feld vorhanden - Monster drauf?
		// TODO: prüfen, ob Monster da sind, ggf. Merge

		if (absDist > (abs(target.x - heroPos.x) + abs(target.y - heroPos.y)))
		{
			// Kommt näher => Move!

			pGrpMon->Laufen(target);
			m_pDoc->PlayDMSound("C:\\Source\\C++\\DM\\sound\\DMCSB-SoundEffect-Move(Skeleton).mp3");

			return target;
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

void CRaumView::InitDungeon(CDMDoc* pDoc, CDC* pDC, CPictures* pPictures)
{
	m_pDoc = pDoc;
	m_pPictures = pPictures;
	m_pDoorPic = new CDoorPic(pDC);
	m_pWallPic = new CWallPic(pDC);
	m_pStairsPic = new CStairsPic(pDC);
	m_pLeverPic = new CLeverPic(pDC);
	m_pFountainPic = new CFountainPic(pDC);
	m_pMonsterPic = new CMonsterPic(pDC);
	m_pMap = new CDungeonMap();
	m_pMap->DemoMap();	
}

void CRaumView::OnTrigger()
{
	// Hier werden sämtliche Trigger angestoßen: Schalter, Türen, etc.

	int x = m_pDoc->m_pGrpHelden->HolePosition().x;
	int y = m_pDoc->m_pGrpHelden->HolePosition().y;
	int z = m_pDoc->m_pGrpHelden->HolePosition().z;

	int richt = m_pDoc->m_pGrpHelden->HoleRichtung();
	int addx = x + m_values->m_sty[richt];
	int addy = y - m_values->m_stx[richt];
	CField* feld = m_pMap->GetField(addx, addy, z);
	int iFeld = feld->HoleTyp();

	// Testweise. Space = Wand vor Spieler erzeugen/löschen

	if (iFeld == CField::FeldTyp::WALL)
	{
		CFieldDecoration* deco = (feld->HoleDeko(CHelpfulValues::OppositeDirection(richt)));
		if (deco->GetDecoType() == Switch) {
			deco->SetState(1 - deco->GetState());
			m_pDoc->PlayDMSound("C:\\Source\\C++\\DM\\sound\\DMCSB-SoundEffect-Switch.mp3");
		} else if	(deco->GetDecoType() == Fountain) {
			m_pDoc->m_pGrpHelden->DrinkFountain();
		}
	}
	else if (iFeld == CField::FeldTyp::DOOR)
	{
		CDoor* door = feld->HoleDoor();
		if (door) {
			door->Toggle();
			m_pDoc->PlayDMSound("C:\\Source\\C++\\DM\\sound\\DMCSB-SoundEffect-Door.mp3");

		}
	}
	else
		feld->SetType(CField::FeldTyp::WALL);
}

