#include "stdafx.h"
#include "Decoration.h"

CFieldDecoration::CFieldDecoration(FloorDecorationType  type) {
	m_Type = type;
	m_State = 0;
}

CFieldDecoration::~CFieldDecoration() {
}

FloorDecorationType CFieldDecoration::GetDecoType() {
	return m_Type;
}

int CFieldDecoration::GetState() {
	return m_State;
}

void CFieldDecoration::SetState(int state) {
	m_State = state;
}

