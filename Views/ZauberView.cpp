// ZauberView.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "ZauberView.h"
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


void CZauberView::Zeichnen(CPictures* pPictures, CDC * pDC, int iActiveWizard, int runeTableId, int* runeIds)
{
	CDC tmpdc;
	tmpdc.CreateCompatibleDC(pDC);

	tmpdc.SelectObject(pPictures->GetWizardTabs(iActiveWizard));
	pDC->BitBlt(466, 80, 174, 17, &tmpdc, 0, 0, SRCCOPY);

	tmpdc.SelectObject(pPictures->GetRunes(runeTableId));
	pDC->BitBlt(466,97,174,59,&tmpdc,0,0,SRCCOPY);

	for (int i = 1; i < 5; i++) {
		if (runeIds[i] != 0) {
			tmpdc.SelectObject(pPictures->GetRunes(i));
			// 174 / 6 = 29
			pDC->BitBlt(469 + (i - 1) * 28, 124, 24, 21, &tmpdc, 4 + (runeIds[i] - 1) * 28, 3, SRCCOPY);
		}
	}
	
	tmpdc.DeleteDC();
}

