// DMView.cpp : implementation of the CDMView class
//
#include "stdafx.h"
#include "DM.h"

#include <winuser.rh>

#include "..\DMDoc.h"
#include "DMView.h"
#include "RaumView.h"
#include "ZauberView.h"
#include "CGroupView.h"
#include "..\CalculationHelper/CScreenCoords.h"
#include "..\CDungeonMap.h"
#include "..\Rucksack.h"
#include "..\Pictures\CPictures.h"
#include "..\Pictures/Items3D/CItem3DPic.h"
#include "..\Mobs\MobGroups\GrpHeld.h"
#include "..\Mobs\MobGroups\GrpMonster.h"
#include "..\Mobs\Held.h"
#include "..\ColorCursor/ColorCursor.h"
#include "..\CalculationHelper/CHelpfulValues.h"
#include "..\SpecialTile/CDoor.h"
#include "..\SpecialTile\CPit.h"
#include "..\Items/Item.h""
#include <cassert>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDMView

IMPLEMENT_DYNCREATE(CDMView, CView)

BEGIN_MESSAGE_MAP(CDMView, CView)
	//{{AFX_MSG_MAP(CDMView)
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_TIMER()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDMView construction/destruction

CDMView::CDMView()
{
	m_pPictures = NULL;
	m_pRaumView = new CRaumView();
	m_pZauberView = new CZauberView();
	m_pGroupView = new CGroupView();
	m_bSleep = false;
	m_bPause = false;
	m_iModus = MOD_LAUFEN;
	lastModus = MOD_LAUFEN;
	m_iDir = 0;
	((CDMApp*)AfxGetApp())->SetView(this);

	/*CFont* pFont;
	
	pFont->CreateFont(8,0,0,0,FW_NORMAL,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_MODERN, NULL); 
	SetFont(pFont);*/
}

CDMView::~CDMView()
{
	delete m_pRaumView;
	delete m_pZauberView;
	delete m_pGroupView;
	delete m_pPictures;
//	KillTimer(this, idTimer ); 
	((CDMApp*)AfxGetApp())->SetView(NULL);
}

BOOL CDMView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDMView drawing

void CDMView::OnDraw(CDC* pRealDC)
{
	CDMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}


/////////////////////////////////////////////////////////////////////////////
// CDMView diagnostics

#ifdef _DEBUG
void CDMView::AssertValid() const
{
	CView::AssertValid();
}

void CDMView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDMDoc* CDMView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDMDoc)));
	return (CDMDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDMView message handlers

void CDMView::ParseClickArrows(CPoint point) {
	CDMDoc* pDoc = (CDMDoc*)GetDocument();
	int newDir = CScreenCoords::CheckHitArrows(point);
	if (newDir > 0) {
		m_iDir = newDir;
		if ((m_iModus == MOD_LAUFEN) && (m_iDir > 0))
		{
			UpdateGrafik();
			pDoc->SetzeRichtung(m_iDir);
		}
	}
}

void CDMView::ParseClickWizard(CPoint point) {
	CGrpHeld* grpHelden = m_pRaumView->GetHeroes();
	int newWizard = CScreenCoords::CheckHitActiveWizard(point, grpHelden->GetActiveWizard());
	if (newWizard > 0)
	{
		if (grpHelden->SetActiveCaster(newWizard))
		{
			CDC* pDC = GetDC();
			ZauberReiterZeichnen(pDC, newWizard);
			UpdateGrafik();
		}
	}
}

void CDMView::ParseClickAction(CPoint point) {
	CGrpHeld* grpHelden = m_pRaumView->GetHeroes();

	int actionPhase = grpHelden->GetActionPhase();
	int actionNumber = CScreenCoords::CheckHitAction(point, actionPhase);
	if (actionNumber > 0 && actionPhase == 1)
	{
		grpHelden->ChooseHeroForAction(actionNumber);
	}
	else if (actionNumber != 0 && actionPhase == 2) {
		if (actionNumber == -1) // pass
		{
			grpHelden->PassAction();
		}
		else {
			VEKTOR monPos = grpHelden->HoleZielFeld(VORWAERTS);
			CGrpMonster* grpMonster = m_pRaumView->GetMonsterGroup(monPos);
			
			grpHelden->DoActionForChosenHero(actionNumber, grpMonster );
		}
		UpdateGrafik();
	}

}

void CDMView::ParseClickDoorButton(CPoint point, CField* FeldVorHeld) {

	CDoor* door = FeldVorHeld->HoleDoor();
	if (door && door->hasButton()) {
		if (CScreenCoords::CheckHitDoorButton(point)) {
			door->Toggle();
		}
	}
}


void CDMView::ParseClickPortrait(CPoint point) {
	int heroID = CScreenCoords::CheckHitHeroes(point);
	if (heroID > 0)
	{
		CGrpHeld* grpHelden = m_pRaumView->GetHeroes();
		grpHelden->Aktiviere(heroID);
	}
}

bool CDMView::ParseClickPortraitHands(CPoint point, bool backpackMode) {
	int handId = CScreenCoords::CheckHitPortraitHands(point);
	if (handId > 0) {
		// 1 2 3 4 5 6 7 8	HandId
		// 1 1 2 2 3 3 4 4  HeroId
		// 0 1 0 1 0 1 0 1  HandOfHeroId
		int heroId = (int)((handId + 1) / 2);
		int handOfHeroId = (handId - 1) % 2;					// TODO auslagern, und dann auch in Backpack nutzen!
		
		CGrpHeld* grpHelden = m_pRaumView->GetHeroes();
		CHeld* clickedHero = grpHelden->GetHero(heroId);
		if ((clickedHero == NULL) || (clickedHero->isActive() && backpackMode))
			return false; // Hände durch Portrait überdeckt.

		grpHelden->PutGetItem(handOfHeroId, heroId);
		
		return true;
	}
	else
		return false;
}

/// <summary>
/// Werfen
/// </summary>
/// <param name="point"></param>
void CDMView::ParseClickAir(CPoint point) {
	CGrpHeld* grpHelden = m_pRaumView->GetHeroes();
	CItem* pItemInHand = grpHelden->GetItemInHand();

	if (pItemInHand != NULL) {
		SUBPOS airRegionClicked = CScreenCoords::CheckHitAir(point);
		if (airRegionClicked != NONE) {
			CField* FeldVorHeld = m_pRaumView->GetMap()->GetField(grpHelden->HoleZielFeld(VORWAERTS));
			if (FeldVorHeld) {
				if (FeldVorHeld->Blocked()) {
					// skip, nix.
				}
				else 
				{
					int grpDir = grpHelden->GetDirection();
					SUBPOS_ABSOLUTE itemRegionReal = CHelpfulValues::GetRelativeSubPosActive(airRegionClicked, grpDir);
					VEKTOR force = CHelpfulValues::MakeVektor(grpDir, 6);
					m_pRaumView->GetMap()->GetField(grpHelden->GetPos())->ThrowItem(pItemInHand, itemRegionReal, force);
					grpHelden->EmptyHand();
				}
			}

		}
	}
}

bool CDMView::ParseClickActuator(CPoint point, std::deque<CActuator*> &actuators, COMPASS_DIRECTION dir, CSize size) {
	std::deque<CActuator*> actuatorsAtPosition;
	COMPASS_DIRECTION pos;
	for (CActuator* actuator : actuators) {
		// Alle Aktuatoren sammeln, die an der angeschauten Position sind.
		pos = actuator->GetPosition();
		if (pos == dir) {
			actuatorsAtPosition.push_back(actuator);
		}

	}
	if (actuatorsAtPosition.size() > 0)
		if (CScreenCoords::CheckHitDeco(point, size))
		{
			int type = actuatorsAtPosition.back()->GetType();
			CActuator* currentActuator = actuatorsAtPosition.back();
			CActuator::ActionTarget actionTarget = currentActuator->GetActionTarget();
			if (!currentActuator->IsActive()) return false;
			
			if (type == 1) {
				// Schalter 
				//VEKTOR target;
				// TODO Unklar - Logik korrekt? Target aus 2. Actuator nehmen, wenn 1. LOCAL ist, und 2. vorhanden und 2. remote.
				if (currentActuator->GetActionTarget() == CActuator::Local && currentActuator->Action()) {
					currentActuator = actuatorsAtPosition.front();
				}
				else if (currentActuator->GetActionTarget() == CActuator::Remote) {
					InvokeRemoteActuator(currentActuator);
				}
				else if (actuatorsAtPosition.size() > 1 && actionTarget == CActuator::Local) {
					assert(("too many actuators", actuatorsAtPosition.size() < 3));
					currentActuator = actuatorsAtPosition.front();
				}

				else assert(false); // todo ...

				return true; // RotateActuators
			}
			else if (type == 4) {
				// Item Receiver - Lock / ... ?
				CGrpHeld* grpHelden = m_pRaumView->GetHeroes();
				CItem* itemInHand = grpHelden->GetItemInHand();
				if (itemInHand) {
					int data = currentActuator->GetData();
					int neededItemId;
					if (data > 167) {
						neededItemId = data - 167;
					}
					else assert(false); // todo formel verstehen.
					if (neededItemId == itemInHand->GetType()) {
						// Match !
						if (currentActuator->GetActionTarget() == CActuator::Remote) {
							InvokeRemoteActuator(currentActuator);
						}
						else assert(false); // todo ...

						grpHelden->EmptyHand();
						delete (itemInHand);
						::SystemParametersInfo(SPI_SETCURSORS, 0, 0, SPIF_SENDCHANGE);
						if (currentActuator->IsOnceOnly()) {
							currentActuator->Deactivate();
						}
						return true; // RotateActuators
					}
				}
			}
			else {
				// Alkoven & co
				CGrpHeld* grpHelden = m_pRaumView->GetHeroes();
				CField* FeldVorHeld = m_pRaumView->GetMap()->GetField(grpHelden->HoleZielFeld(VORWAERTS));
				std::deque<CItem*> itemsInWall = FeldVorHeld->GetItem(SUBPOS_ABSOLUTE::NORTHWEST);
				CItem* itemInHand = grpHelden->GetItemInHand();
				if (itemInHand == NULL) {
					if (itemsInWall.size() > 0) {
						grpHelden->TakeItemInHand(FeldVorHeld->TakeItem(SUBPOS_ABSOLUTE::NORTHWEST));
					}
				}
				else {
					FeldVorHeld->PutItem(itemInHand, SUBPOS_ABSOLUTE::NORTHWEST);
					grpHelden->EmptyHand();
				}
			}
		}
	return false;
}

void CDMView::InvokeRemoteActuator(CActuator* activeActuator) {
	VEKTOR target = activeActuator->GetTarget();
	CField* pTargetField = m_pRaumView->GetMap()->GetField(target);
	CDoor* door;
	CPit* pit;

	switch (pTargetField->HoleTyp()) {
	case FeldTyp::DOOR:
		door = pTargetField->HoleDoor();
		if (activeActuator->GetActionType() == CActuator::Toggle) door->Toggle();
		if (activeActuator->GetActionType() == CActuator::Set) door->Open();
		if (activeActuator->GetActionType() == CActuator::Clear) door->Close();
		break;
	case FeldTyp::PIT:
		pit = pTargetField->HolePit();
		if (activeActuator->GetActionType() == CActuator::Toggle) pit->Toggle();
		if (activeActuator->GetActionType() == CActuator::Set) pit->Open();
		if (activeActuator->GetActionType() == CActuator::Clear) pit->Close();
		break;
	default:
		break;
	}
}

void CDMView::ParseClickFloor(CPoint point) {
	CGrpHeld* grpHelden = m_pRaumView->GetHeroes();
	CItem* pItemInHand = grpHelden->GetItemInHand();

	SUBPOS itemRegionClicked = CScreenCoords::CheckHitFloor(point);
	SUBPOS_ABSOLUTE itemRegionReal = CHelpfulValues::GetRelativeSubPosActive(itemRegionClicked, grpHelden->GetDirection());
	CItem* topItem = NULL;
	if (itemRegionClicked == LINKSVORNE || itemRegionClicked == RECHTSVORNE)
	{
		CField* FeldVorHeld = m_pRaumView->GetMap()->GetField(grpHelden->HoleZielFeld(VORWAERTS));
		if (FeldVorHeld && !FeldVorHeld->Blocked())
		{
			if (pItemInHand == NULL)
				topItem = FeldVorHeld->TakeItem(itemRegionReal);
			else {
				FeldVorHeld->PutItem(pItemInHand, itemRegionReal);
				grpHelden->EmptyHand();
			}

		}
	}
	else if (itemRegionClicked == LINKSHINTEN || itemRegionClicked == RECHTSHINTEN) {
		CField* FeldUnterHeld = m_pRaumView->GetMap()->GetField(grpHelden->GetPos());
		if (FeldUnterHeld)
		{
			if (pItemInHand == NULL)
				topItem = FeldUnterHeld->TakeItem(itemRegionReal);
			else {
				FeldUnterHeld->PutItem(pItemInHand, itemRegionReal);
				grpHelden->EmptyHand();
			}
		}
	}
	if (itemRegionClicked != NONE) {
		grpHelden->TakeItemInHand(topItem);
		ChangeMouseCursor();
	}

}


void CDMView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	//RAUM :0,64,460,270+64

	CDMDoc* pDoc = (CDMDoc*)GetDocument();
	CGrpHeld* grpHelden = m_pRaumView->GetHeroes();
	if (m_iModus == MOD_LAUFEN)
	{
		ParseClickArrows(point);
		if (grpHelden && grpHelden->GetNumberOfHeroes() > 0)
		{
			ParseClickFloor(point);
			ParseClickWizard(point);
			ParseClickAction(point);
			if (!ParseClickPortraitHands(point, false))
				ParseClickPortrait(point);
		
			// Unterscheiden: Anklicken oder werfen?
			CField* FeldVorHeld = m_pRaumView->GetMap()->GetField(grpHelden->HoleZielFeld(VORWAERTS));
			if (FeldVorHeld) {
				if (FeldVorHeld->Blocked()) {
					COMPASS_DIRECTION dir = CHelpfulValues::OppositeDirection( grpHelden->GetDirection());
					std::deque<CActuator*> actuators = (FeldVorHeld->GetActuator(dir));
					if (!actuators.empty()) {
						CSize size = m_pRaumView->GetSizeOfFrontDeco(FeldVorHeld, dir);

						if (ParseClickActuator(point, actuators, dir, size))
							FeldVorHeld->RotateActuators(dir);
					}
					ParseClickDoorButton(point, FeldVorHeld);

				}
				else {
					ParseClickAir(point);
				}
			}


		}

		/*if (CScreenCoords::CheckHitDeco(point)) { // todo aufräumen
			m_pRaumView->OnTrigger();
		}*/
		
	}
	else if (m_iModus == MOD_RUCKSACK)
	{
		CDC* pDC = GetDC();

		ParseClickPortraitHands(point, true);
		if (CScreenCoords::CheckHitMainScr(point)) {
			grpHelden->GetActiveHero()->GetRucksack()->OnLButtonDown(pDC, nFlags, point);
			ChangeMouseCursor();
		}
	}
	CView::OnLButtonDown(nFlags, point);
}

void CDMView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CDMDoc* pDoc = (CDMDoc*) GetDocument();
	CDC* pDC = GetDC();
	CGrpHeld* grpHelden = m_pRaumView->GetHeroes();
	if (grpHelden->GetActiveHero() == NULL) return;

	switch (m_iModus)
	{
	case MOD_LAUFEN:
		if (grpHelden->SetzeModus(pDC, RUCKSACK)) {
			m_iModus = MOD_RUCKSACK;
		}
		break;
		//	}
	case MOD_RUCKSACK:
		if (grpHelden->SetzeModus(	pDC, LAUFEN))
		{
			m_iModus = MOD_LAUFEN;
			UpdateGrafik();
		}
		break;
	}
	CView::OnRButtonDown(nFlags, point);
}


void CDMView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CDMDoc* pDoc = GetDocument();
	if (m_iDir ==0)
	{
		switch (nChar)
		{
			case 27:
				if (m_bPause) {
					m_bPause = false;
					m_iModus = lastModus;
				}
				else {
					m_bPause = true;
					lastModus = m_iModus;
					m_iModus = MOD_PAUSE;
				}
				break;
			case 32:
				if (cheatAktiv)
					m_pRaumView->OnTrigger();
				break;
			case 38:
			case 101:
				m_iDir = VORWAERTS;
				break;
			case 40:
			case 98:
				m_iDir = RUECKWAERTS;
				break;
			case 37:
			case 97:
				m_iDir = LINKS_STRAFE;
				break;
			case 39:
			case 99:
				m_iDir = RECHTS_STRAFE;
				break;
			case 100:
				m_iDir = LINKS_DREHEN;
				break;
			case 102:
				m_iDir = RECHTS_DREHEN;
				break;
			case 49:
			case 50:
			case 51:
			case 52:
				pDoc->InitGruppe(nChar-48);
				break;
			default:
				{
					CString str;
					str.Format("%i ",nChar);
					TRACE(str);
					break;
				}
		}

		if (m_iModus == MOD_LAUFEN)
		{
			if (m_iDir>0)
			{
				UpdateGrafik();
				pDoc->SetzeRichtung(m_iDir); // noch nicht laufen, nur anmelden
			}
		}
		else if (m_iModus == MOD_RUCKSACK)
		{
			UpdateGrafik();
		}
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CDMView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}

//////////////////////////////////////////////////////////////////////
// Zeichenmethoden



void CDMView::HeldenGrafikZeichnen(CGrpHeld* pGrpHelden, CDC* pDC, CPictures* pPictures)
{
	m_pGroupView->GroupZeichnen(pDC, pPictures, m_iModus, pGrpHelden);
}

void CDMView::ZauberReiterZeichnen(CDC* pDC, int iActiveWizard)
{	
	m_pZauberView->Zeichnen(m_pPictures, pDC, iActiveWizard);
}

void CDMView::ActionAreaZeichnen(CDC* pDC) {
	DrawBMP(pDC, m_pPictures->GetActionsArea(), 448, 150);
}

void CDMView::ActionDamageZeichnen(CDC* pDC, int dmg) {
	DrawBMP(pDC, m_pPictures->GetActionDamage(dmg), 448, 150);
}

void CDMView::WaffenZeichnen(CDC* pDC, CGrpHeld* pGrpHeroes) {
	CDC tmpdc;
	tmpdc.CreateCompatibleDC(pDC);

	for (int id = 1; id < 5; id++) {
		CHeld* held = pGrpHeroes->GetHero(id);
		if (held)
		{
			tmpdc.SelectObject(m_pPictures->GetOneHand());
			pDC->BitBlt(466 + 44 * (id - 1), 176, 44, 66, &tmpdc, 0, 0, SRCCOPY);
		}
	}
	
	tmpdc.DeleteDC();
}

void CDMView::DrawBMP(CDC* pDC, CBitmap* pBMP, int posX, int posY) {
	CDC tmpdc;
	tmpdc.CreateCompatibleDC(pDC);
	tmpdc.SelectObject(pBMP);
	BITMAP bmpInfo;
	pBMP->GetBitmap(&bmpInfo);
	pDC->TransparentBlt(posX, posY, bmpInfo.bmWidth * 2, bmpInfo.bmHeight * 2, &tmpdc, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);
	DeleteDC(tmpdc);
}

void CDMView::FrameZeichnen(CDC* pDC) {
	ChangeMouseCursor();
	
	CGrpHeld* pGrpHeroes = m_pRaumView->GetHeroes();

	if (pGrpHeroes != NULL)
	{
		HeldenGrafikZeichnen(pGrpHeroes, pDC, m_pPictures);

		int phase = pGrpHeroes->GetActionPhase();
		if (phase == 1) {
			WaffenZeichnen(pDC, pGrpHeroes);
		}
		else if (phase == 2) {
			ActionAreaZeichnen(pDC);
		}
		else if (phase == 3) {
			CHeld* pHeld = pGrpHeroes->GetAttackingHero();
			if (pHeld)
			{
				ActionDamageZeichnen(pDC, pHeld->GetDealingDamage());
			}
		}

		int iActiveWizard = pGrpHeroes->GetActiveWizard();
		if (iActiveWizard > 0)
			ZauberReiterZeichnen(pDC, iActiveWizard);
	}

	m_pPictures->PfeilZeichnen(pDC, m_iDir);

}

void CDMView::UpdateGrafik()
{
	CDC* pDC = GetDC();

	CDC* pDC_ = new CDC();
	pDC_->CreateCompatibleDC(pDC);
	CBitmap tmpbmp;
	tmpbmp.CreateCompatibleBitmap(pDC, 640, 400);
	pDC_->SelectObject(tmpbmp);

	FrameZeichnen(pDC_);

	if (!m_bPause)
		if (!m_bSleep)
		{
			if (m_iModus == MOD_LAUFEN)
				m_pRaumView->RaumZeichnen(pDC_);
			else if (m_iModus == MOD_RUCKSACK)
			{
				CGrpHeld* grpHelden = m_pRaumView->GetHeroes();
				m_pPictures->RucksackZeichnen(pDC_, grpHelden->GetActiveHero());
			}

		}
		else
			// You are asleep
			;
	else
		// Game frozen
		;

	pDC->BitBlt(0, 0, 640, 400, pDC_, 0, 0, SRCCOPY);
	delete pDC_;
	DeleteObject(tmpbmp);
}

void CDMView::OnTimer(UINT nIDEvent) 
{
	CDMDoc* pDoc = GetDocument();

	if (!m_bPause) {
		if (!m_pRaumView->GetHeroes()->Altern()) {
			// 
		}
		if (m_pRaumView->GetHeroes()->GetNumberOfHeroes() > 0) {
			m_pRaumView->MoveAnythingNearby();
			m_pRaumView->TriggerActuatorsNearby();
		}

		if (m_iDir > 0)
		{
			pDoc->Laufen();
			m_iDir = 0;
		}
		UpdateGrafik();
	}
	else {
		UpdateGrafik();
	}

	CView::OnTimer(nIDEvent);
}

void CDMView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (m_iModus == MOD_RUCKSACK)
	{
		CDC* pDC = GetDC();

		m_pRaumView->GetHeroes()->GetActiveHero()->GetRucksack()->OnLButtonUp(pDC, nFlags, point);
	}

	CView::OnLButtonUp(nFlags, point);
}

void CDMView::InitDungeon(CDMDoc* pDoc)
{
	CDC* pDC = GetDC();
	m_pPictures = new CPictures(pDC);
	m_pRaumView->InitDungeon(pDoc, pDC, m_pPictures);
	pDoc->SetRaumView(m_pRaumView);
}

void CDMView::ChangeMouseCursor() {
	CGrpHeld* heroes = m_pRaumView->GetHeroes();
	if (heroes) {
		CItem* item = heroes->GetItemInHand();
		if (item) {
			CDC* pDC = GetDC();
			CBitmap* bmp = m_pPictures->GetIconBitmap(pDC, item); //heroes->GetItemInHand()->GetPicByType(m_pRaumView->Get3DPics());
			if (bmp) {
				HBITMAP hBmp = (HBITMAP)bmp->GetSafeHandle();
				HCURSOR hCursor = CColorCursor::CreateCursorFromBitmap(hBmp, TRANS_GRA, 16, 16);
				SetSystemCursor(hCursor, OCR_NORMAL);
				delete bmp;
				return;
			}
		}
	}
	::SystemParametersInfo(SPI_SETCURSORS, 0, 0, SPIF_SENDCHANGE);
}