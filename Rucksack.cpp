// Rucksack.cpp : implementation file
//

#include "stdafx.h"
#include "Pictures\CPictures.h"
#include "Rucksack.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRucksack

CRucksack::CRucksack()
{
	m_iModusExtend = MOD_EXT_NORMAL;

	KLASSE[1] = "FIGHTER";
    KLASSE[2] = "NINJA";
	KLASSE[3] = "PRIEST";
	KLASSE[4] = "WIZARD";
}

CRucksack::~CRucksack()
{
}


/////////////////////////////////////////////////////////////////////////////
// CRucksack message handlers

void CRucksack::Zeichnen(CDC * pDC, CPictures* pPictures) // TODO das ganze zeug dringend raus hier !!!
{
	CDC tmpdc;
	tmpdc.CreateCompatibleDC(pDC);
	tmpdc.SelectObject(pPictures->GetRucksack());
	pDC->BitBlt(0,64,460,270,&tmpdc,0,64,SRCCOPY);
	
	if (m_iModusExtend == MOD_EXT_AUGE)
		pDC->BitBlt(22,88,34,36,&tmpdc,0,338,SRCCOPY);
	
	tmpdc.DeleteDC();
}

void CRucksack::OnLButtonDown(CDC* pDC, UINT nFlags, CPoint point)
{
	if (InRect(point,22,88,56,124))
		m_iModusExtend = MOD_EXT_AUGE;

}

void CRucksack::OnLButtonUp(CDC* pDC, UINT nFlags, CPoint point)
{
	//if (InRect(point,22,88,56,124))
	m_iModusExtend = MOD_EXT_NORMAL;
}

void CRucksack::ZeichneHungerDurst(CDC* pDC, int i, int j)
{
	pDC->FillSolidRect(CRect(230,206,230+i,218), SCHWARZ);
	COLORREF col;
	if (i>50)
		col = DUNKELBRAUN;
	else if (i>15)
		col = GELB;
	else
		col = ROT;
	pDC->FillSolidRect(CRect(226,202,226+i,214), col);

	pDC->FillSolidRect(CRect(230,252,230+j,264), SCHWARZ);
	if (j>50)
		col = BLAU;
	else if (j>15)
		col = GELB;
	else
		col = ROT;
	pDC->FillSolidRect(CRect(226,248,226+j,260), col);

}

void CRucksack::ZeichneHpStMa(CDC* pDC, WERTE hp, WERTE st, WERTE ma)
{
	pDC->SetTextColor(HELLGRAU);
	pDC->SetBkColor(GANZDUNKELGRAU);
	
	CString str;
	str.Format("%i / %i", hp.Aktuell, hp.Max);
	pDC->TextOut(120,284,str);
	str.Format("%i / %i", st.Aktuell, st.Max);
	pDC->TextOut(120,300,str);
	str.Format("%i / %i", ma.Aktuell, ma.Max);
	pDC->TextOut(120,316,str);
}


void CRucksack::ZeichneSkills(CDC * pDC, long sExp[5], VITALS sVitals)
{
	pDC->SetTextColor(HELLGRAU);
	pDC->SetBkColor(GANZDUNKELGRAU);
	CString strZeile, strTitel,strKlasse;

	pDC->FillSolidRect(210,170,226,142,GANZDUNKELGRAU);
	for (int i=1; i<5; i++)
	{
		if (sExp[i]>0)
		{
			strTitel = Titel(sExp[i]);
			strKlasse = KLASSE[i];
			strZeile.Format("%s %s",strTitel,strKlasse);
			pDC->TextOut(230,160+i*16,strZeile);
		}
	}
}

CString CRucksack::Titel(long exp)
{
	int e = int(exp/50);
	switch (e)
	{
	case 0:
		return ""; break;
	case 1:
		return "NOVICE"; break;
	case 2:
		return "APPRENTICE"; break;
	case 3:
		return "JOURNEYMAN"; break;
	case 4:
		return "ARTISAN"; break;
	case 5:
		return "ADEPT"; break;
	case 6: 
		return "EXPERT"; break;
	default:
		CString str;
		str.Format("%i. MASTER",e-4);
		return str; break;
	} 
	// bitmap
}

void CRucksack::SetzeModusExtend(int iModusExtend)
{
	m_iModusExtend = iModusExtend;
}
