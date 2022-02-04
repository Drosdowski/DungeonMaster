#pragma once
class CStairs
{
public:
	enum StairType {
		DOWN = 0,
		UP = 1
	};

	CStairs(StairType type);
	~CStairs();

	StairType GetType() { return m_Type; }

private:
	StairType m_Type;
};

