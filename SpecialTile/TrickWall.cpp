#include "stdafx.h"
#include "TrickWall.h"


CTrickWall::CTrickWall(TrickWallType type, TrickWallState state) : CDelayedTile() {
	m_type = type;
	m_state = state;
}

CTrickWall::~CTrickWall() {

};

void CTrickWall::Open(int delay) {
	m_state = TrickWallState::Opened;
	CDelayedTile::Open(delay); 
}

void CTrickWall::Close(int delay) {
	m_state = TrickWallState::Closed;
	CDelayedTile::Close(delay);
}

void CTrickWall::Toggle() {
	if (m_state == TrickWallState::Opened)
		m_state = TrickWallState::Closed;
	else
		m_state = TrickWallState::Opened;
}