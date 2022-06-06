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
	resetRuneTable();
}

CZauberView::~CZauberView()
{
	if (spell != NULL) delete spell;
}

void CZauberView::resetRuneTable() {
	m_iRuneTable = 1;
	if (spell != NULL) delete spell;
	spell = new int[5];
}

void CZauberView::Zeichnen(CPictures* pPictures, CDC * pDC, int iActiveWizard)
{
	CDC tmpdc;
	tmpdc.CreateCompatibleDC(pDC);

	tmpdc.SelectObject(pPictures->GetWizardTabs(iActiveWizard));
	pDC->BitBlt(466, 80, 174, 17, &tmpdc, 0, 0, SRCCOPY);

	tmpdc.SelectObject(pPictures->GetRunes(m_iRuneTable));
	pDC->BitBlt(466,97,174,59,&tmpdc,0,0,SRCCOPY);
	
	tmpdc.DeleteDC();
}

void CZauberView::DrawRunes(CPictures* pPictures, CDC* pDC) {
	CDC tmpdc;
	tmpdc.CreateCompatibleDC(pDC);
	for (int i = 0; i < 5; i++) {
		if (spell[i] != NULL) {
			tmpdc.SelectObject(pPictures->GetRunes(i));
			pDC->BitBlt(468 + i*29, 100, 25, 53, &tmpdc, 0, 0, SRCCOPY);
		}
	}
	tmpdc.DeleteDC();
}
