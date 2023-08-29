#pragma once
#include "DelayedTile.h"
class CPit : public CDelayedTile
{
public:
	enum PitType {
		Standard = 0,
		Invisible = 1,
		Imaginary = 2
	};

	enum PitState {
		Closed = 0,
		Opened = 1
	};

	CPit(PitType type, PitState state);
	~CPit();

	PitType GetType() { return m_type; }
	PitState GetState(); 

	void Open(int delay);
	void Close(int delay);
	void Toggle();

private:
	PitType m_type;
	PitState m_state;
};

