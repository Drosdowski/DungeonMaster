#include "stdafx.h"
#include "Container.h"
#include "Weapon.h"
#include "CMiscellaneous.h"
#include "Cloth.h"
#include "Potion.h"
#include "Scroll.h"

CContainer::CContainer(int index, CContainerAttributes attributes) : CItem(index, ContainerItem) {
	m_attribute = attributes;
}

CContainer::~CContainer() {
	for (int i = 0; i < 8; i++) {
		CItem* item = m_subItems[i];
		if (item)
		{
			if (item->getItemType() == CItem::ItemType::WeaponItem)
				delete (CWeapon*)item;
			else if (item->getItemType() == CItem::ItemType::MiscItem)
				delete (CMiscellaneous*)item;
			else if (item->getItemType() == CItem::ItemType::ClothItem)
				delete (CCloth*)item;
			else if (item->getItemType() == CItem::ItemType::PotionItem)
				delete (CPotion*)item;
			else if (item->getItemType() == CItem::ItemType::ScrollItem)
				delete (CScroll*)item;
			else if (item->getItemType() == CItem::ItemType::ContainerItem)
				delete (CContainer*)item;
			else
				delete item;
		}
	}
}

void CContainer::SetOpen(bool value) {
	m_attribute.open = value;
}

int CContainer::GetOffsetForGroup() {
	if (m_attribute.open) {
		return 17;
	}
	else {
		return 16;
	}
}

int CContainer::GetSheetForGroup() {
	return 4;

}

CItem::ItemGroup CContainer::GetGroup() {
	return Container;
}

double CContainer::GetWeight() {
	double weight = 5;
	for (int i = 0; i < 8; i++) {
		CItem* item = m_subItems[i];
		if (item)
		{
			if (item->getItemType() == CItem::ItemType::WeaponItem)
				weight += ((CWeapon*)item)->GetWeight();
			else if (item->getItemType() == CItem::ItemType::MiscItem)
				weight += ((CMiscellaneous*)item)->GetWeight();
			else if (item->getItemType() == CItem::ItemType::ClothItem)
				weight += ((CCloth*)item)->GetWeight();
			else if (item->getItemType() == CItem::ItemType::PotionItem)
				weight += ((CPotion*)item)->GetWeight();
			else if (item->getItemType() == CItem::ItemType::ScrollItem)
				weight += ((CScroll*)item)->GetWeight();
			else if (item->getItemType() == CItem::ItemType::ContainerItem)
				weight += ((CContainer*)item)->GetWeight();
			else
				weight += item->GetWeight();
		}
	}
	return round(weight);
}

CItem* CContainer::SwitchItemAt(int index, CItem* item)
{
	CItem* carryingBefore = m_subItems[index];
	m_subItems[index] = item;
	if (item->getItemType() == CItem::ScrollItem) {
		CScroll* pScroll = (CScroll*)item;
		pScroll->SetOpen(0);
	}
	else if (item->getItemType() == CItem::ContainerItem) {
		CContainer* pContainer = (CContainer*)item;
		pContainer->SetOpen(false);
	}

	return carryingBefore;
}