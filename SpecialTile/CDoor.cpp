#include "stdafx.h"
#include "CDoor.h"

CDoor::CDoor(CDoorAttributes attribute, DoorDecorationType ornate, bool doorFrameEastAndWest) {
	m_attributes = attribute;
	m_state = CLOSED;
	m_bottomHeight = 0;
	m_doorFrameEastAndWest = doorFrameEastAndWest;
	m_ornate = ornate;
}

/// <summary>
/// Moves the door if moving in any direction
/// </summary>
/// <param name="someoneBelowDoor">Player or MonsterGroup</param>
/// <returns>anyone hit bit the door?</returns>
bool CDoor::ContinueMoving(int heightOfSomeoneBelowDoor) {
	switch (m_state) {
	case (OPEN):
		m_state = CLOSING;
		break;
	case (OPENING):
		m_bottomHeight += movingHeight;
		if (m_bottomHeight >= fullHeight) {
			m_state = OPEN;
			m_bottomHeight = fullHeight;
		}
		break;
	case (CLOSING):
		if (heightOfSomeoneBelowDoor * movingHeight >= m_bottomHeight && m_bottomHeight < fullHeight) {
			// collision!
			m_state = OPENING;
			return true;
		} else {
			m_bottomHeight -= movingHeight;
			if (m_bottomHeight <= 0) {
				m_state = CLOSED;
				m_bottomHeight = 0;
			}
		}
		break;
	case (CLOSED):
		m_state = OPENING;
		break;
	}
	return false;
}

void CDoor::Toggle() {
	if (m_state != DESTROYED) {
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

void CDoor::SetState(int value) {
	// für LoadMap
	m_state = (DoorState)value;
	if (m_state == OPEN) {
		m_bottomHeight = fullHeight;
	}
	else {
		m_bottomHeight = 0;
	}

}