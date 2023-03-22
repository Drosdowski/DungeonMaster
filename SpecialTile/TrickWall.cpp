#include "stdafx.h"
#include "TrickWall.h"


CTrickWall::CTrickWall(TrickWallType type, TrickWallState state) {
	m_type = type;
	m_state = state;
}

CTrickWall::~CTrickWall() {

};

void CTrickWall::Open() {
	m_state = TrickWallState::Opened;
}

void CTrickWall::Close() {
	m_state = TrickWallState::Closed;
}

void CTrickWall::Toggle() {
	if (m_state == TrickWallState::Opened)
		m_state = TrickWallState::Closed;
	else
		m_state = TrickWallState::Opened;
}