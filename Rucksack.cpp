// Rucksack.cpp : implementation file
//

#include "stdafx.h"
#include "CScreenCoords.h"
#include "Rucksack.h"
#include "Items/CMiscellaneous.h"
#include "Mobs/Held.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRucksack

CRucksack::CRucksack(CHeld* pHero)
{
	m_iModusExtend = MOD_EXT_NORMAL;
	m_pOwner = pHero;

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


void CRucksack::OnLButtonDown(CDC* pDC, UINT nFlags, CPoint point)
{
	if (CScreenCoords::CheckHitEye(point))
		m_iModusExtend = MOD_EXT_AUGE;
	else if (CScreenCoords::CheckHitMouth(point))
	{
		CMiscellaneous* item = m_pOwner->GetItemInHand();
		if (item && item->GetGroup() == CMiscellaneous::ItemGroup::Food) {
			m_pOwner->Essen(50);
			m_pOwner->EmptyHand();
			delete item; // destroy permanently!
			::SystemParametersInfo(SPI_SETCURSORS, 0, 0, SPIF_SENDCHANGE);
		}
	}
	else {
		int slot = CScreenCoords::CheckHitBackpackSlots(point);
		if (slot > 0) {

		}
	}

}

void CRucksack::OnLButtonUp(CDC* pDC, UINT nFlags, CPoint point)
{
	m_iModusExtend = MOD_EXT_NORMAL;
}


CString CRucksack::m_title(long exp)
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
