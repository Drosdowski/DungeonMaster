// DMDoc.cpp : implementation of the CDMDoc class
//

#include "stdafx.h"
#include "DM.h"
#include <math.h>

#include "DmView.h"
#include "Raumview.h"
#include "DMDoc.h"
#include "SpecialTile\Decoration.h"
#include "Mobs\Held.h"
#include "Mobs\MobGroups\GrpHeld.h"

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
	m_pGrpHelden = new CGrpHeld();
	
	m_iWunschRichtung = 0;
	
	((CDMApp*)AfxGetApp())->SetDoc(this);
	

}

CDMDoc::~CDMDoc()
{
	((CDMApp*)AfxGetApp())->SetDoc(NULL);

	delete m_pGrpHelden;

}

BOOL CDMDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
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
	bool bLaufbereit = m_pGrpHelden->Laufbereit();
	VEKTOR pos;

	switch(m_iWunschRichtung)
	{
	case LINKS_DREHEN:
		m_pRaumView->TriggerMoveAnimation();
		m_pGrpHelden->Drehen(LINKS);
		break;
	case RECHTS_DREHEN:
		m_pRaumView->TriggerMoveAnimation();
		m_pGrpHelden->Drehen(RECHTS);
		break;
	case LINKS_STRAFE:
	case RUECKWAERTS:
	case RECHTS_STRAFE:
	case VORWAERTS:
		if (bLaufbereit)
			pos = m_pGrpHelden->HoleZielFeld(m_iWunschRichtung);

			if (m_pRaumView->Betrete(pos))
			{
				m_pGrpHelden->Kollision();
				PlayDMSound("C:\\Source\\C++\\DM\\sound\\DMCSB-SoundEffect-RunningIntoAWall.mp3");
			}
			else
			{
				m_pRaumView->TriggerMoveAnimation();
				m_pGrpHelden->Laufen(pos);
			}
			break;
	}
	m_iWunschRichtung = 0;
}

void CDMDoc::SetzeRichtung(int iRichtung)
{
	m_iWunschRichtung = iRichtung;
}

void CDMDoc::InitGruppe(CPictures* pPictures, const int nr)
{
	m_pGrpHelden->InitHeld(pPictures, nr);
}

int CDMDoc::HoleGruppenRichtung() 
{
	return m_pGrpHelden->HoleRichtung();
}

VEKTOR CDMDoc::HoleGruppenPosition()   
{
	return m_pGrpHelden->HolePosition();
}
	
void CDMDoc::PlayDMSound(std::string file) {
	// std::string file = "C:\\Source\\C++\\DM\\sound\\DMCSB-SoundEffect-Attack(Skeleton-AnimatedArmour-PartySlash).mp3";
	std::string cmd = "open \"" + file + "\" type mpegvideo alias mp3";
	mciSendString("close mp3", NULL, 0, NULL);
	mciSendString(cmd.c_str(), NULL, 0, NULL);
	mciSendString("play mp3", NULL, 0, NULL);

}
