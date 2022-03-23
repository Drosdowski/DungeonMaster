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

	CActuator(int index, COMPASS_DIRECTION position, VEKTOR target, ActionTypes actionTypes, ActionTarget actionTarget, int type, int graphic);
	~CActuator();
 
	int GetType() { return m_type; } // todo muss hier kein POSITIOn rein ??
	VEKTOR GetTarget(int position) { return m_target[position]; }
	ActionTypes GetActionType(int position) { return m_actionType[position]; }
	ActionTarget GetActionTarget(int position) { return m_actionTarget[position]; }
	int GetCriticalWeigth() { return 100; } // todo wo steht das?
	int GetGraphic() { return m_graphic; }
	COMPASS_DIRECTION GetPosition() { return m_position; } // todo COMPASS...

private:
	int m_index;
	COMPASS_DIRECTION m_position;
	int m_type;
	int m_graphic;
	VEKTOR m_target[4];
	ActionTypes m_actionType[4];
	ActionTarget m_actionTarget[4];

};

