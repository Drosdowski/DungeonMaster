#pragma once
class CTrickWall
{
public:
	enum TrickWallType {
		Standard = 0,
		Imaginary = 1
	};

	enum TrickWallState {
		Closed = 0,
		Opened = 1
	};

	CTrickWall(TrickWallType type, TrickWallState state);
	~CTrickWall();

	TrickWallType GetType() { return m_type; }
	TrickWallState GetState() { return m_state; }

	void Open();
	void Close();
	void Toggle();

private:
	TrickWallType m_type;
	TrickWallState m_state;
};
