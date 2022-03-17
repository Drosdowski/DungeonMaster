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

CZauberView::CZauberView()
{
}

CZauberView::~CZauberView()
{
}


void CZauberView::Zeichnen(CPictures* pPictures, CDC * pDC, int iActiveWizard)
{
	CDC tmpdc;
	tmpdc.CreateCompatibleDC(pDC);

	tmpdc.SelectObject(pPictures->GetWizardTabs(iActiveWizard));
	pDC->BitBlt(466, 80, 174, 17, &tmpdc, 0, 0, SRCCOPY);

	tmpdc.SelectObject(pPictures->GetRunes(1));
	pDC->BitBlt(466,97,174,59,&tmpdc,0,0,SRCCOPY);
	
	tmpdc.DeleteDC();
}
