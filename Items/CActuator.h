#pragma once
class CActuator
{
public:
	CActuator(int index, VEKTOR actionTarget, ActionTypes actionTypes);
	~CActuator();

private:
	int m_index;
	VEKTOR m_actionTarget;
	ActionTypes m_actionType;

};

