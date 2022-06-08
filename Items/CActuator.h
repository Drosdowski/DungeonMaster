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

	CActuator(int index, COMPASS_DIRECTION position, VEKTOR target, ActionTypes actionTypes, ActionTarget actionTarget, int type, int data, int graphic, int once_only, bool action);
	~CActuator();
 
	int GetType() { return m_type; }
	int GetData() { return m_data; }
	VEKTOR GetTarget() { return m_target; }
	ActionTypes GetActionType() { return m_actionType; }
	ActionTarget GetActionTarget() { return m_actionTarget; }
	int GetCriticalWeigth() { return 100; } // todo wo steht das?
	int GetGraphic() { return m_graphic; }
	COMPASS_DIRECTION GetPosition() { return m_position; } 
	bool IsActive() { return m_active;  }
	void Deactivate() { m_active = false; }
	bool IsOnceOnly() { return m_once_only > 0; }
	bool Action() { return m_action; }

private:
	int m_index;
	COMPASS_DIRECTION m_position;
	int m_type;
	int m_graphic;
	int m_data;
	bool m_active;
	int m_once_only;
	bool m_action;
	VEKTOR m_target;
	ActionTypes m_actionType;
	ActionTarget m_actionTarget;

};

