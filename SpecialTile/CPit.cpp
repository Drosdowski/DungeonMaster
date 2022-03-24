#include "stdafx.h"
#include "CPit.h"


CPit::CPit(PitType type, PitState state) {
	m_type = type;
	m_state = state;
}

CPit::~CPit() {

};

void CPit::Open() {
	m_state = PitState::Opened;
}

void CPit::Close() {
	m_state = PitState::Closed;
}

void CPit::Toggle() {
	if (m_state == PitState::Opened)
		m_state = PitState::Closed; 
	else 
		m_state = PitState::Opened;
}