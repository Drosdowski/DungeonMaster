#pragma once
class CStairs
{
public:
	enum StairType {
		DOWN = 0,
		UP = 1
	};

	CStairs(StairType type, bool m_eastWest);
	~CStairs();

	StairType GetType() { return m_Type; }
	bool Visible(int heroDir);

private:
	StairType m_Type;
	bool m_eastWest;
};

