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

	CActuator(int index, VEKTOR actionTarget, ActionTypes actionTypes, int type);
	~CActuator();

	int GetType() { return m_type; }
	VEKTOR GetActionTarget() { return m_actionTarget; }
	ActionTypes GetActionType() { return m_actionType; }

private:
	int m_index;
	int m_type;
	VEKTOR m_actionTarget;
	ActionTypes m_actionType;

};

