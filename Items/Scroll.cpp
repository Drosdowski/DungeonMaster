#include "stdafx.h"
#include "Scroll.h"

CScroll::CScroll(int index, CScrollAttributes* attributes) : CItem(index, ScrollItem) {
	m_attribute = attributes;
}

CScroll::~CScroll() {
	delete m_attribute;
}

const char* CScroll::GetText() {
	return m_attribute->text;
}

void CScroll::SetOpen(bool value) {
	m_attribute->open = value;
}

int CScroll::GetOffsetForGroup() {
	if (m_attribute->open) {
		return 30;
	}
	else {
		return 31;
	}
}

int CScroll::GetSheetForGroup() {	
	return 0;

}

CItem::ItemGroup CScroll::GetGroup() {
	return Scroll;
}