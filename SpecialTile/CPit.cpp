#include "stdafx.h"
#include "CPit.h"


CPit::CPit(PitType type, PitState state) : CDelayedTile() {
	m_type = type;
	m_state = state;
}

CPit::~CPit() {

};

void CPit::Open(int delay) {
	m_state = PitState::Opened;
	CDelayedTile::Open(delay);
}

void CPit::Close(int delay) {
	m_state = PitState::Closed;
	CDelayedTile::Close(delay);
}

void CPit::Toggle() {
	if (m_state == PitState::Opened)
		m_state = PitState::Closed; 
	else 
		m_state = PitState::Opened;
}

CPit::PitState CPit::GetState() {
	if (m_state == Opened && openDelayDone() || m_state == Closed && !closeDelayDone())
		return Opened;
	else
		return Closed;
}

void CPit::SetState(int value) {
	// für LoadMap
	m_state = (PitState)value;
}