// Rucksack.cpp : implementation file
//

#include <typeinfo>
#include "stdafx.h"
#include "CalculationHelper/CScreenCoords.h"
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

CRucksack::CRucksack()
{
	m_iModusExtend = MOD_EXT_NORMAL;

	KLASSE[0] = "FIGHTER";
    KLASSE[1] = "NINJA";
	KLASSE[2] = "PRIEST";
	KLASSE[3] = "WIZARD";
}

CRucksack::~CRucksack()
{
}


/////////////////////////////////////////////////////////////////////////////
// CRucksack message handlers


void CRucksack::handleLButtonDown(CDC* pDC, CPoint point, CHeld* pOwner)
{
	if (CScreenCoords::CheckHitEye(point))
		m_iModusExtend = MOD_EXT_AUGE;
	else if (CScreenCoords::CheckHitMouth(point))
	{
		CItem* item = pOwner->GetItemInHand();
		CWeapon* weapon = NULL;
		if (item->getItemType() == CItem::ItemType::MiscItem) {
			CMiscellaneous* misc = (CMiscellaneous*)item;
			if (misc && misc->GetGroup() == CMiscellaneous::ItemGroup::Consumable) {
				if (misc->GetType() == CMiscellaneousAttributes::MiscItemType::Water) {
					if (misc->GetSubtype() > 0) {
						pOwner->Trinken(50);
						misc->SetSubtype(misc->GetSubtype() - 1);
					}
				}
				else {
					pOwner->Essen(50);
					pOwner->EmptyHand();
					delete item; // destroy permanently!
				}
			}
		}
	}
	else {
		int slot = CScreenCoords::CheckHitBackpackSlots(point);
		if (slot >= 0) {
			CItem* itemInHand = pOwner->GetItemInHand();
			CItem* newItemInHand = NULL;
			CItem* itemCarryingAtPos = pOwner->GetItemCarrying(slot);
			if ((itemInHand == NULL) || (itemInHand && itemInHand->CheckGroup(slot, itemInHand->GetGroup()))) {
				// todo: group check!
				if (itemInHand) {
					newItemInHand = pOwner->SwitchItemAt(slot, itemInHand);
				}
				else {
					newItemInHand = itemCarryingAtPos;
				}
				if (newItemInHand == NULL) {
					pOwner->EmptyHand();
				}
				else {
					pOwner->TakeItemInHand(newItemInHand);
					pOwner->RemoveItemCarrying(slot);
				}
			}
		}
	}

}

void CRucksack::handleLButtonUp()
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
}

void CRucksack::SetzeModusExtend(int iModusExtend)
{
	m_iModusExtend = iModusExtend;
}
