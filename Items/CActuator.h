#pragma once
class CActuator
{
public:
	enum ActionTypes {
		Set,
		Clear,
		Toggle,
		Hold
	};

	CActuator(int index, VEKTOR actionTarget, ActionTypes actionTypes);
	~CActuator();

private:
	int m_index;
	VEKTOR m_actionTarget;
	ActionTypes m_actionType;

};

