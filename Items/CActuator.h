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

	CActuator(int index, int position, VEKTOR actionTarget, ActionTypes actionTypes, int type);
	~CActuator();
 
	int GetType() { return m_type; }
	VEKTOR GetActionTarget(int position) { return m_actionTarget[position]; }
	ActionTypes GetActionType(int position) { return m_actionType[position]; }
	int GetCriticalWeigth() { return 100; } // todo wo steht das?

private:
	int m_index;
	int m_position;
	int m_type;
	VEKTOR m_actionTarget[4];
	ActionTypes m_actionType[4];

};
