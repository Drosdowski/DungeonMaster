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
	enum ActionTarget {
		Remote,
		Local
	};

	CActuator(int index, int position, VEKTOR target, ActionTypes actionTypes, ActionTarget actionTarget, int type, int graphic);
	~CActuator();
 
	int GetType() { return m_type; }
	VEKTOR GetTarget(int position) { return m_target[position]; }
	ActionTypes GetActionType(int position) { return m_actionType[position]; }
	ActionTarget GetActionTarget(int position) { return m_actionTarget[position]; }
	int GetCriticalWeigth() { return 100; } // todo wo steht das?
	int GetGraphic() { return m_graphic; }

private:
	int m_index;
	int m_position;
	int m_type;
	int m_graphic;
	VEKTOR m_target[4];
	ActionTypes m_actionType[4];
	ActionTarget m_actionTarget[4];

};

