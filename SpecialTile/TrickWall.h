#pragma once
#include "DelayedTile.h"
class CTrickWall : public CDelayedTile
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
	TrickWallState GetState();

	void Open(int delay);
	void Close(int delay);
	void Toggle();


private:
	TrickWallType m_type;
	TrickWallState m_state;

};

