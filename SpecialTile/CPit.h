#pragma once
class CPit
{
public:
	enum PitType {
		Standard = 0,
		Invisible = 1,
		Imaginary = 2
	};

	enum PitState {
		Closed = 0,
		Open = 1
	};

	CPit(PitType type, PitState state);
	~CPit();

	PitType GetType() { return m_type; }
	PitState GetState() { return m_state; }


private:
	PitType m_type;
	PitState m_state;
};

