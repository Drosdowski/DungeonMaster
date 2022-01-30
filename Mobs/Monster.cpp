// Monster.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "resource.h"
#include "Pictures\CPictures.h"
#include "DMDoc.h"
#include "Monster.h"
#include <CHelpfulValues.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMonster

CMonster::CMonster(CPictures* pPictures, CDC* pDC): CCharacter()
{
	m_pPictures = pPictures;
	m_attacking = false;
	
	m_iReceivedDmg = 0;

	pCdc.CreateCompatibleDC(pDC);
}



CMonster::~CMonster()
{
	DeleteDC(pCdc);
}


BEGIN_MESSAGE_MAP(CMonster, CView)
	//{{AFX_MSG_MAP(CMonster)
		// HINWEIS - Der Klassen-Assistent fügt hier Zuordnungsmakros ein und entfernt diese.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Zeichnung CMonster 

void CMonster::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// ZU ERLEDIGEN: Code zum Zeichnen hier einfügen
}

/////////////////////////////////////////////////////////////////////////////
// Diagnose CMonster

#ifdef _DEBUG
void CMonster::AssertValid() const
{
	CView::AssertValid();
}

void CMonster::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CMonster 

bool CMonster::Altern()
{
	bool alive = CCharacter::Altern();
	// erstmal konstant, später abhängig 
	// von max-Werten 
	if (alive)
	{
		if (m_iReceivedDmg > 0) {
			// damage
			WerteTemporaerAendern(-m_iReceivedDmg, 0, 0);			
			m_iReceivedDmg = 0;
			if (Hp() <= 0) return false; // tot!
		}
		else {
			// restore
			//  WerteTemporaerAendern(1, 1, 1);
		}
		if (m_attacking) {
			EndAttack();
		}
	}
	return alive;
}


void CMonster::ZeichneMonster(CDC* pDC, int bmpTAG, int iEntfernung, int xrel, bool invers) {
	CBitmap bmp;
	BITMAP bmpInfo;

	bmp.LoadBitmap(bmpTAG);

	//get original size of bitmap
	bmp.GetBitmap(&bmpInfo);
	double faktor = m_pPictures->getFaktor(iEntfernung);

	// Bild Mitte: 225 / 78
	int posX = 225 - bmpInfo.bmWidth * faktor + (xrel * 156);
	int posY = 100 + bmpInfo.bmHeight * (1 - faktor) / 2;

	pCdc.SelectObject(bmp);
	if (invers) {
		pCdc.StretchBlt(0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, &pCdc, bmpInfo.bmWidth, 0, -bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);
		pDC->TransparentBlt(posX, posY, bmpInfo.bmWidth * faktor * 2, bmpInfo.bmHeight * faktor * 2, &pCdc, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, transCol);
	}
	else {
		pDC->TransparentBlt(posX, posY, bmpInfo.bmWidth * faktor * 2, bmpInfo.bmHeight * faktor * 2, &pCdc, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, transCol);
	}
	//pCdc.SelectObject(m_pPictures->m_pBmpHintergrund);
}

int CMonster::GetIDB(int index) {
	return 0;
}

void CMonster::Zeichnen(CDC* pDC, int iEntfernung, int iRichtung, int xrel)
{
	int iRicht = (6 - m_chrDirection + iRichtung) % 4;
	bool drawLeftInvers = iRicht == 3;
	ZeichneMonster(pDC, GetIDB(iRicht), iEntfernung, xrel, drawLeftInvers);
}


bool CMonster::TurnTo(int iDirection) {
	if (m_chrDirection == CHelpfulValues::OppositeDirection(iDirection))
	{
		m_chrDirection = (m_chrDirection + 1) % 4;
		return false; // nicht angekommen
	} else {
		m_chrDirection = iDirection;
		return true; // angekommen
	}
}

int CMonster::CalcDmg(int ID, CGrpChar* pOpponents) {
	// TODO 1. Waffe
	// TODO 2. Gegnerrüstung
	// TODO 3. Random	
	return m_ApproxDmg;
}
