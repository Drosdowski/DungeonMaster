// Rucksack.cpp : implementation file
//

#include <typeinfo>
#include "stdafx.h"
#include "CScreenCoords.h"
#include "Rucksack.h"
#include "Items/CMiscellaneous.h"
#include "Items/Weapon.h"
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
		CItem* item = m_pOwner->GetItemInHand();
		CWeapon* weapon = NULL;
		if (item->getItemType() == CItem::ItemType::MiscItem) {
			CMiscellaneous* misc = (CMiscellaneous*)item;
			if (misc && misc->GetGroup() == CMiscellaneous::ItemGroup::Consumable) {
				if (misc->GetType() == CMiscellaneousAttributes::MiscItemType::Water) {
					if (misc->GetSubtype() > 0) {
						m_pOwner->Trinken(50);
						misc->SetSubtype(misc->GetSubtype() - 1);
					}
				}
				else {
					m_pOwner->Essen(50);
					m_pOwner->EmptyHand();
					delete item; // destroy permanently!
				}
			}
		}
	}
	else {
		int slot = CScreenCoords::CheckHitBackpackSlots(point);
		if (slot >= 0) {
			CItem* itemInHand = m_pOwner->GetItemInHand();
			CItem* newItemInHand = NULL;
			CItem* itemCarryingAtPos = m_pOwner->GetItemCarrying(slot);
			if ((itemInHand == NULL) || (itemInHand && itemInHand->CheckGroup(slot, itemInHand->GetType()))) {
				// todo: group check!
				if (itemInHand) {
					newItemInHand = m_pOwner->SwitchItemAt(slot, itemInHand);
				}
				else {
					newItemInHand = itemCarryingAtPos;
				}
				if (newItemInHand == NULL) {
					m_pOwner->EmptyHand();
				}
				else {
					m_pOwner->TakeItemInHand(newItemInHand);
					m_pOwner->RemoveItemCarrying(slot);
				}
			}
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
