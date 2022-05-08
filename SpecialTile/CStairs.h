#pragma once
class CStairs
{
public:
	enum StairType {
		DOWN = 0,
		UP = 1
	};

	CStairs(StairType type, COMPASS_DIRECTION stairExit);
	~CStairs();

	StairType GetType() { return m_Type; }
	bool Visible(int heroDir);
	COMPASS_DIRECTION StairExit() { return m_stairExit;  };

private:
	StairType m_Type;
	COMPASS_DIRECTION m_stairExit;
};

