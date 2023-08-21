#include "stdafx.h"
#include "Text.h"

CText::CText(int index, CTextAttributes attributes) {
	m_attribute = attributes;
}

CText::~CText() {
}

CString CText::GetText() {
	CString text = m_attribute.text; 
	text.Replace("_YOU", "YOU ");
	text.Replace("_THE", "THE ");
	text.Replace("_AND", "AND ");
	return text;
}

