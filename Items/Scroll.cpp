#include "stdafx.h"
#include "Scroll.h"

CScroll::CScroll(int index, CScrollAttributes attributes) : CItem(index, ScrollItem) {
	m_attribute = attributes;
}

CScroll::~CScroll() {
}

const char* CScroll::GetText() {
	return m_attribute.text;
}

void CScroll::SetOpen(bool value) {
	m_attribute.open = value;
}

int CScroll::GetOffsetForGroup(bool active) {
	if (m_attribute.open && active) {
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