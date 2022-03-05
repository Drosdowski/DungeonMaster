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
	int GetLastWeight() { return m_lastWeight; }
	void ResetWeight() { m_lastWeight = 0; }
	void AddWeight(int weight) { m_lastWeight += weight; }

private:
	int m_index;
	int m_position;
	int m_type;
	VEKTOR m_actionTarget[4];
	ActionTypes m_actionType[4];
	int m_lastWeight;

};

