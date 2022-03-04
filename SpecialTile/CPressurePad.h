#pragma once
class CPressurePad
{
public:
	
	enum PressurePadState
	{
		UNPRESSED = 0,
		PRESSED = 1,
		PRESSED_AND_LOCKED = 2
	};	

	enum PressurePadType {
		Square = 0,
		SMall = 1
	};

	CPressurePad(PressurePadType type);
	~CPressurePad();


private:
	PressurePadType m_type;

};

