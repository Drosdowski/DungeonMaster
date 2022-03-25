#include "stdafx.h"
#include "CDoor.h"

CDoor::CDoor(DoorType type, bool doorFrameEastAndWest) {
	m_type = type;
	m_state = CLOSED;
	m_bottomHeight = 0;
	m_doorFrameEastAndWest = doorFrameEastAndWest;
}

void CDoor::ContinueMoving() {
	switch (m_state) {
	case (OPEN):
		m_state = CLOSING;
		// m_bottomHeight = fullHeight - movingHeight;
		break;
	case (OPENING):
		m_bottomHeight += movingHeight;
		if (m_bottomHeight == fullHeight) {
			m_state = OPEN;
		}
		break;
	case (CLOSING):
		m_bottomHeight -= movingHeight;
		if (m_bottomHeight == 0) {
			m_state = CLOSED;
		}
		break;
	case (CLOSED):
		m_state = OPENING;
		//m_bottomHeight = movingHeight;
		break;
	}
}

void CDoor::Toggle() {
	switch (m_state) {
	case (OPEN):
	case (OPENING):
		m_state = CLOSING;
		break;
	case (CLOSING):
	case (CLOSED):
		m_state = OPENING;
		break;
	}
}

void CDoor::Open() {
	if (m_state == CLOSED)
		m_state = OPENING;
}
void CDoor::Close() {
	if (m_state == OPEN)
		m_state = CLOSING;
}

bool CDoor::Visible(int heroRicht) {
	return (getDoorFrameEastAndWest() != (heroRicht % 2 != 0));
}