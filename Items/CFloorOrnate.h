#pragma once
class CFloorOrnate
{
public:
	CFloorOrnate(FloorDecorationType type);
	~CFloorOrnate();

	FloorDecorationType GetType() { return m_type; }

private:
	FloorDecorationType m_type;  // 2 = moss, 8 = puddle, 6 = crack, 1 = SquarePressurePad !!!
};

