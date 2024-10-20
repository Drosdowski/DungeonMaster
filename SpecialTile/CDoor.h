#pragma once
#include "..\Attributes\DoorAttributes.h"

class CDoor
{
public:
	enum DoorState {
		OPEN = 0,
		CLOSING = 1,
		OPENING = 2,
		CLOSED = 4,  // maps needs 0 / 4.
		DESTROYED = 5
	};

	CDoor(CDoorAttributes attribute, DoorDecorationType ornate, bool doorFrameEastAndWest);

	DoorState getState() { return m_state; }
	void SetState(int value);
	bool hasButton() { return m_attributes.button; }
	bool Visible(int heroDir);
	int getDoorBottomHeight() { return m_bottomHeight; }
	DoorDecorationType getOrnate() { if (m_attributes.ornateId > 0) return m_ornate; else return PlainDoor; }
	bool getDoorFrameEastAndWest() { return m_doorFrameEastAndWest; }
	void Toggle();
	bool ContinueMoving(int heightOfSomeoneBelowDoor);
	void Open();
	void Close();

	CDoorAttributes::DoorType getType() { return m_attributes.type; }
	bool destroyedByFireball() { return m_attributes.fireball; }
	bool destroyedByForce() { return m_attributes.force; }


private:
	DoorState m_state;
	DoorDecorationType m_ornate;
	CDoorAttributes m_attributes;
	int m_bottomHeight = 0;
	bool m_doorFrameEastAndWest; // Wall at 00 / 02
	const int fullHeight = 88;
	const int movingHeight = 22;
};

