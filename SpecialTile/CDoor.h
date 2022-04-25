#pragma once
#include "..\Attributes\CDoorAttributes.h"

class CDoor
{
public:
	enum DoorState {
		OPEN = 0,
		CLOSING = 1,
		OPENING = 2,
		CLOSED =3
	};
	
	CDoor(CDoorAttributes attribute, bool doorFrameEastAndWest);

	DoorState getState() { return m_state; }
	CDoorAttributes::DoorType getType() { return m_attributes.type; }
	bool hasButton() { return m_attributes.button; }
	bool Visible(int heroDir);
	int getDoorBottomHeight() { return m_bottomHeight; }
	bool getDoorFrameEastAndWest() { return m_doorFrameEastAndWest; }
	void Toggle();
	void ContinueMoving();
	void Open();
	void Close();

private:
	DoorState m_state;
	CDoorAttributes m_attributes;
	int m_bottomHeight = 0;
	bool m_doorFrameEastAndWest; // Wall at 00 / 02
	const int fullHeight = 88;
	const int movingHeight = 22;
};

