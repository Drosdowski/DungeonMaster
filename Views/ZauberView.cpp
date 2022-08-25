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
	if (m_spell != NULL) delete m_spell;
}

void CZauberView::resetRuneTable() {
	m_iRuneTable = 1;
	if (m_spell != NULL) delete m_spell;
	m_spell = new int[5];
}

void CZauberView::Zeichnen(CPictures* pPictures, CDC * pDC, int iActiveWizard)
{
	CDC tmpdc;
	tmpdc.CreateCompatibleDC(pDC);

	tmpdc.SelectObject(pPictures->GetWizardTabs(iActiveWizard));
	pDC->BitBlt(466, 80, 174, 17, &tmpdc, 0, 0, SRCCOPY);

	tmpdc.SelectObject(pPictures->GetRunes(m_iRuneTable));
	pDC->BitBlt(466,97,174,59,&tmpdc,0,0,SRCCOPY);

	for (int i = 1; i < 5; i++) {
		if (m_spell[i] != 0) {
			int runeId = m_spell[i];
			tmpdc.SelectObject(pPictures->GetRunes(i));
			// 174 / 6 = 29
			pDC->BitBlt(469 + (i - 1) * 28, 124, 24, 21, &tmpdc, 4 + (runeId - 1) * 28, 3, SRCCOPY);
		}
	}
	
	tmpdc.DeleteDC();
}

void CZauberView::storeRune(int index) {
	m_spell[m_iRuneTable] = index;
	if (m_iRuneTable == 1) {
		for (int i = 2; i < 5; i++)
			m_spell[i] = 0;
	}
	nextRuneTable();
};

void CZauberView::nextRuneTable() {
	if (m_iRuneTable < 4)
		m_iRuneTable++;
	else
		m_iRuneTable = 1;
}

int CZauberView::GetPower() {
	if (m_iRuneTable > 1) {
		return m_spell[1];
	}
	else {
		return 0;
	}

}
