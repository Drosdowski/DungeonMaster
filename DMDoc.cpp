// DMDoc.cpp : implementation of the CDMDoc class
//

#include "stdafx.h"
#include "DM.h"
#include <math.h>

#include "Views\Raumview.h"
#include "XMLParser\CDungeonMap.h"
#include "DMDoc.h"
#include "Items\FloorDecoration.h"
#include "Mobs\Held.h"
#include "Mobs\MobGroups\GrpHeld.h"
#include "CalculationHelper\CHelpfulValues.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDMDoc

IMPLEMENT_DYNCREATE(CDMDoc, CDocument)

BEGIN_MESSAGE_MAP(CDMDoc, CDocument)
	//{{AFX_MSG_MAP(CDMDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDMDoc construction/destruction


CDMDoc::CDMDoc()
{
	m_iWunschRichtung = 0;
	
	((CDMApp*)AfxGetApp())->SetDoc(this);
	
}

CDMDoc::~CDMDoc()
{
	((CDMApp*)AfxGetApp())->SetDoc(NULL);
}

BOOL CDMDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// (SDI documents will reuse this document)

	return TRUE;
}

void CDMDoc::SetRaumView(CRaumView* pRaumView) {
	m_pRaumView = pRaumView;
}

/////////////////////////////////////////////////////////////////////////////
// CDMDoc serialization

void CDMDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDMDoc diagnostics

#ifdef _DEBUG
void CDMDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDMDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDMDoc commands


void CDMDoc::Laufen()
{
	VEKTOR posTarget, posFrom, posFinal;
	CGrpHeld* pGrpHeroes = m_pRaumView->GetHeroes();
	boolean collision = false;
	posFrom = pGrpHeroes->GetVector();
	bool bLaufbereit = m_pRaumView->GetHeroes()->Laufbereit();

	switch(m_iWunschRichtung)
	{
	case LINKS_DREHEN:
	case RECHTS_DREHEN:
		if (bLaufbereit)
		{
			m_pRaumView->TriggerMoveAnimation();
			if (m_pRaumView->OnStairs()) {
				// auf Treppe drehen = Treppe nutzen!
				posFinal = m_pRaumView->Betrete(posFrom, collision);
				pGrpHeroes->Laufen(posFinal, false);
			}
			else {
				if (m_iWunschRichtung == LINKS_DREHEN)
					pGrpHeroes->DrehenRelativ(LINKS);
				else
					pGrpHeroes->DrehenRelativ(RECHTS);
			}
		}
		break;
	case LINKS_STRAFE:
	case RUECKWAERTS:
	case RECHTS_STRAFE:
	case VORWAERTS:
		if (bLaufbereit)
		{
			if (m_pRaumView->OnStairs() && m_iWunschRichtung == RUECKWAERTS) {
				// Sonderregel: Treppe rückwärts läuft nicht gegen die Wand hinter der Gruppe, sondern rauf/runter
				posFinal = m_pRaumView->Betrete(posFrom, collision);
				m_pRaumView->TriggerMoveAnimation();
				pGrpHeroes->Laufen(posFinal, false);
			}
			else {

				posTarget = pGrpHeroes->HoleZielFeld(m_iWunschRichtung);
				posFinal = m_pRaumView->Betrete(posTarget, collision);
				if (collision)
				{
					pGrpHeroes->Kollision(m_iWunschRichtung);
					PlayDMSound("C:\\Users\\micha\\source\\repos\\DungeonMaster\\sound\\DMCSB-SoundEffect-RunningIntoAWall.mp3");
				}
				else if (posFinal.x != posFrom.x || posFinal.y != posFrom.y || posFinal.z != posFrom.z)
				{
					m_pRaumView->TriggerMoveAnimation();
					pGrpHeroes->Laufen(posFinal, false);
				}
			}
		}
		break;
	}
	m_iWunschRichtung = 0;
}


void CDMDoc::SetzeRichtung(int iRichtung)
{
	m_iWunschRichtung = iRichtung;
}

void CDMDoc::InitGruppe(const int nr)
{
	CGrpHeld* pGrpHelden = m_pRaumView->GetHeroes();
	pGrpHelden->InitHeld(nr);
}

int CDMDoc::HoleGruppenRichtung() 
{
	return m_pRaumView->GetHeroes()->GetDirection();
}

VEKTOR CDMDoc::HoleGruppenPosition()   
{
	return m_pRaumView->GetHeroes()->GetVector();
}
	
void CDMDoc::PlayDMSound(std::string file) {
	// std::string file = "C:\\Source\\C++\\DM\\sound\\DMCSB-SoundEffect-Attack(Skeleton-AnimatedArmour-PartySlash).mp3";
	std::string cmd = "open \"" + file + "\" type mpegvideo alias mp3";
	mciSendString("close mp3", NULL, 0, NULL);
	mciSendString(cmd.c_str(), NULL, 0, NULL);
	mciSendString("play mp3", NULL, 0, NULL);

}
