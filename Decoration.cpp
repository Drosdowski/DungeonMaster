#include "stdafx.h"
#include "Decoration.h"

CFieldDecoration::CFieldDecoration(DecorationType type) {
	m_Type = type;
	m_State = 0;
}

CFieldDecoration::~CFieldDecoration() {
}

DecorationType CFieldDecoration::GetDecoType() {
	return m_Type;
}

int CFieldDecoration::GetState() {
	return m_State;
}

void CFieldDecoration::SetState(int state) {
	m_State = state;
}

