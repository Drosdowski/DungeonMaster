// ZauberView.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "DMView.h"
#include "ZauberView.h"
#include "Mobs\MobGroups\GrpHeld.h"	// todo raus!
#include "Pictures\CPictures.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZauberView

IMPLEMENT_DYNCREATE(CZauberView, CView)

CZauberView::CZauberView()
{
}

CZauberView::~CZauberView()
{
}


BEGIN_MESSAGE_MAP(CZauberView, CView)
	//{{AFX_MSG_MAP(CZauberView)
		// HINWEIS - Der Klassen-Assistent fügt hier Zuordnungsmakros ein und entfernt diese.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Zeichnung CZauberView 

void CZauberView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// ZU ERLEDIGEN: Code zum Zeichnen hier einfügen
}

/////////////////////////////////////////////////////////////////////////////
// Diagnose CZauberView

#ifdef _DEBUG
void CZauberView::AssertValid() const
{
	CView::AssertValid();
}

void CZauberView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CZauberView 

bool CZauberView::setActiveCaster(int ID, CGrpHeld* pGrpHelden)
{	
	if (ID <= pGrpHelden->m_iAnzHelden)
	{
		pGrpHelden->m_iAktiverZauberer = ID;
		return true;
	}	
	return false;
}

void CZauberView::Zeichnen(CPictures* pPictures, CDC * pDC)
{
	CDC tmpdc;
	tmpdc.CreateCompatibleDC(pDC);
	tmpdc.SelectObject(pPictures->GetMagicBG());

	pDC->BitBlt(466,80,174,66,&tmpdc,0,0,SRCCOPY);
	
	tmpdc.DeleteDC();
}
