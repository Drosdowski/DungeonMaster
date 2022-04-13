#include "stdafx.h"
#include "FloorDecoration.h"

CFloorDecoration::CFloorDecoration(FloorDecorationType  type) {
	m_Type = type;
	m_State = 0;
}

CFloorDecoration::~CFloorDecoration() {
}

FloorDecorationType CFloorDecoration::GetDecoType() {
	return m_Type;
}

int CFloorDecoration::GetState() {
	return m_State;
}

void CFloorDecoration::SetState(int state) {
	m_State = state;
}

