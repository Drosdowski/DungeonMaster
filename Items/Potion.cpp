#include "stdafx.h"
#include "Potion.h"

#include <cassert>

CPotion::CPotion(int index, CPotionAttributes attributes) : CItem(index, PotionItem) {
	m_attribute = attributes;
}

CPotion::~CPotion() {
}

int CPotion::GetOffsetForGroup() {
	if (m_attribute.type == CPotionAttributes::PotionType::Empty) return 3;
	if (m_attribute.type <= CPotionAttributes::PotionType::Ful &&
		m_attribute.type >= CPotionAttributes::PotionType::Ya) return m_attribute.type - 12;
	return m_attribute.type + 22;
}

int CPotion::GetSheetForGroup() {
	if (m_attribute.type == CPotionAttributes::PotionType::Empty) return 6;
	if (m_attribute.type <= CPotionAttributes::PotionType::Ful &&
		m_attribute.type >= CPotionAttributes::PotionType::Ya) return 5;
	return 4;

}

CItem::ItemGroup CPotion::GetGroup() {
	return Flask;
}

void CPotion::MakePotion(CPotionAttributes attributes) {
	m_attribute = attributes;
}
