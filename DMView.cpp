// DMView.cpp : implementation of the CDMView class
//

#include "stdafx.h"
#include "DM.h"

#include "DMDoc.h"
#include "DMView.h"
#include "RaumView.h"
#include "ZauberView.h"
#include "CDungeonMap.h"
#include "Pictures\CPictures.h"
#include "Pictures/Items3D/CItem3DPic.h"
#include "Mobs\MobGroups\GrpHeld.h"
#include "Mobs\MobGroups\GrpMonster.h"
#include "Mobs\Held.h"
#include "ColorCursor/ColorCursor.h"
#include <CScreenCoords.h>

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
	// TODO: add construction code here
	m_pRaumView = new CRaumView();
	m_pZauberView = new CZauberView();
	m_bSleep = false;
	m_bPause = false;
	m_iModus = MOD_LAUFEN;
	lastModus = MOD_LAUFEN;
	m_iDir =0;
	((CDMApp*)AfxGetApp())->SetView(this);

	/*CFont* pFont;
	
	pFont->CreateFont(8,0,0,0,FW_NORMAL,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_MODERN, NULL); 
	SetFont(pFont);*/
}

CDMView::~CDMView()
{
	delete m_pRaumView;
	delete m_pZauberView;
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
	int action = CScreenCoords::CheckHitAction(point, actionPhase);
	if (action > 0 && actionPhase == 1)
	{
		grpHelden->ChooseHeroForAction(action);
	}
	else if (action != 0 && actionPhase == 2) {
		if (action == -1) // pass
		{
			grpHelden->PassAction();
		}
		else {
			VEKTOR pos = grpHelden->HoleZielFeld(VORWAERTS);
			CGrpMonster* grpMonster = m_pRaumView->GetMonsterGroup(pos);
			grpHelden->DoActionForChosenHero(action, grpMonster);
		}
		UpdateGrafik();
	}

}

void CDMView::ParseClickHeroes(CPoint point) {
	CGrpHeld* grpHelden = m_pRaumView->GetHeroes();
	int heroID = CScreenCoords::CheckHitHeroes(point);
	if (heroID > 0)
	{
		grpHelden->Aktiviere(heroID);
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
		if (grpHelden)
		{
			SUBPOS itemPos = CScreenCoords::CheckHitFloor(point);
			
			ParseClickWizard(point);
			ParseClickAction(point);
			ParseClickHeroes(point);
			if (itemPos != MITTE) {
				CBitmap* bmp = m_pRaumView->Get3DPics()->GetApple();
				HBITMAP hBmp = (HBITMAP)bmp->GetSafeHandle();
				HCURSOR hCursor = CColorCursor::CreateCursorFromBitmap(hBmp, TRANS_ORA, 0, 0);
				SetCursor(hCursor);
			}
		}

		if (CScreenCoords::CheckHitDeco(point)) {
			m_pRaumView->OnTrigger();
		}
		
	}
	else if (m_iModus == MOD_RUCKSACK)
	{
		CDC* pDC = GetDC();

		if (CScreenCoords::CheckHitMainScr(point))
			grpHelden->OnLButtonDown(pDC, nFlags, point);
	}
	CView::OnLButtonDown(nFlags, point);
}

void CDMView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CDMDoc* pDoc = (CDMDoc*) GetDocument();
	CDC* pDC = GetDC();
	CGrpHeld* grpHelden = m_pRaumView->GetHeroes();

	switch (m_iModus)
	{
	case MOD_LAUFEN:
		if (grpHelden->SetzeModus(	pDC, RUCKSACK))
	
		/*if (pDoc->m_pHeld[iIndex ] != NULL)
			{*/
			m_iModus = MOD_RUCKSACK;
				//pDoc->m_pHeld[iIndex ]->RucksackZeichnen(pDC);
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
				pDoc->InitGruppe(m_pPictures, nChar-48);
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
			CDC* pDC = GetDC();
			m_pRaumView->GetHeroes()->UpdateRucksack(pDC, m_pPictures);
		}
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CDMView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}

//////////////////////////////////////////////////////////////////////
// Zeichenmethoden


void CDMView::PfeilZeichnen(CDC* pDC, int i)
{
	CDC tmpdc;
	tmpdc.CreateCompatibleDC(pDC);
	tmpdc.SelectObject(m_pPictures->GetInversePfeile());
	switch (i)
	{
	case VORWAERTS:
		pDC->BitBlt(526,248,54,42,&tmpdc,62,3,SRCCOPY);
		break;
	case RUECKWAERTS:
		pDC->BitBlt(526,292,54,42,&tmpdc,62,47,SRCCOPY);
		break;
	case LINKS_STRAFE:
		pDC->BitBlt(468,292,56,42,&tmpdc,4,47,SRCCOPY);
		break;
	case RECHTS_STRAFE:
		pDC->BitBlt(582,292,56,42,&tmpdc,118,47,SRCCOPY);
		break;
	case LINKS_DREHEN:
		pDC->BitBlt(468,248,56,42,&tmpdc,4,3,SRCCOPY);
		break;
	case RECHTS_DREHEN:
		pDC->BitBlt(582,248,56,42,&tmpdc,118,3,SRCCOPY);
		break;
	}
	tmpdc.DeleteDC();
}

void CDMView::HeldenGrafikZeichnen(CGrpHeld* pGrpHelden, CDC* pDC, CPictures* pPictures)
{
	pGrpHelden->Zeichnen(pDC, pPictures, m_iModus);
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


void CDMView::UpdateGrafik()
{
	CDC* pDC = GetDC();

	CDMDoc* pDoc = GetDocument();
	CDC* pDC_=new CDC();
	pDC_->CreateCompatibleDC(pDC);
	CBitmap tmpbmp;
	tmpbmp.CreateCompatibleBitmap(pDC, 640, 400);
	pDC_->SelectObject(tmpbmp);

	if (!m_bPause)
		if (!m_bSleep)
		{
			m_pRaumView->Zeichnen(pDC_);
			if (m_iDir>0)
				PfeilZeichnen(pDC_, m_iDir);
		}
		else
			// You are asleep
			;
	else
		// Game frozen
		;

	CGrpHeld* pGrpHeroes = m_pRaumView->GetHeroes();
	if (pGrpHeroes != NULL) 
	{		
		HeldenGrafikZeichnen(pGrpHeroes, pDC_, m_pPictures);

		int phase = pGrpHeroes->GetActionPhase();
		if (phase == 1) {
			WaffenZeichnen(pDC_, pGrpHeroes);
		}
		else if (phase == 2) {
			ActionAreaZeichnen(pDC_);			
		}
		else if (phase == 3) {
			CHeld* pHeld = pGrpHeroes->GetAttackingHero();
			if (pHeld)
			{
				ActionDamageZeichnen(pDC_, pHeld->m_dealingDmg);
			}
		}
		int iActiveWizard = pGrpHeroes->GetActiveWizard();
		if (iActiveWizard > 0)
			ZauberReiterZeichnen(pDC_, iActiveWizard);
	
	}

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

		m_pRaumView->MoveAnythingNearby();

		if (m_iModus == MOD_LAUFEN)
		{
			if (m_iDir > 0)
			{
				pDoc->Laufen();
				m_iDir = 0;
			}
			UpdateGrafik();
		}
		else if (m_iModus == MOD_RUCKSACK)
		{
			CDC* pDC = GetDC();
			m_pRaumView->GetHeroes()->UpdateRucksack(pDC, m_pPictures);
		}
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

		m_pRaumView->GetHeroes()->OnLButtonUp(pDC, nFlags, point);
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


