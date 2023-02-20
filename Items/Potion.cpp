#include "stdafx.h"
#include "Potion.h"

#include <cassert>

CPotion::CPotion(int index, CPotionAttributes attributes) : CItem(index, Potion) {
	m_attribute = attributes;
}

CPotion::~CPotion() {

}

int CPotion::GetOffsetForGroup() {
	return 0;
}

int CPotion::GetSheetForGroup() {
	return 0;
}

CItem::ItemGroup CPotion::GetGroup() {
	return Flask;
}