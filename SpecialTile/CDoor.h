#pragma once
class CDoor
{
public:
	enum DoorState {
		OPEN = 0,
		CLOSING = 1,
		OPENING = 2,
		CLOSED =3
	};
	enum DoorType {
		Iron = 0,
		Wood = 1
	};

	CDoor(DoorType type, bool doorFrameEastAndWest);

	DoorState getState() { return m_state; }
	DoorType getType() { return m_type; }
	bool Visible(int heroDir);
	int getDoorBottomHeight() { return m_bottomHeight; }
	bool getDoorFrameEastAndWest() { return m_doorFrameEastAndWest; }
	void Toggle();
	void ContinueMoving();
	void Open();
	void Close();

private:
	DoorState m_state;
	DoorType m_type;
	int m_bottomHeight = 0;
	bool m_doorFrameEastAndWest; // Wall at 00 / 02
	const int fullHeight = 88;
	const int movingHeight = 22;
};

