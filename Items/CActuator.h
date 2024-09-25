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
	enum ActuatorType {
		Inactive = 0,
		PressurePadTPCI = 1, // People, Creatures, Theron, Items
		PressurePadTPC = 2, // People, Creatures, Theron
		PressurePadP = 3, // People
		Slot = 4,
		Gate = 5,
		CreatureGen = 6,
		MissileShooter = 8,
		DoubleWeaponShooter = 9,
		DoubleMissileShooter = 10,
		Storage = 13,
		ChampionMirror = 127
	};

	CActuator(
		int index, COMPASS_DIRECTION position, VEKTOR target,
		ActionTypes actionTypes, ActionTarget actionTarget, COMPASS_DIRECTION direction, 
		ActuatorType type, int data, int graphic, 
		int once_only, int delay, int action, int power);
	~CActuator();
 
	ActuatorType GetType() { return m_type; }
	int GetData() { return m_data; }
	int GetIndex() { return m_index; }
	int GetPower() { return m_power; }
	VEKTOR GetTarget() { return m_target; }
	COMPASS_DIRECTION GetDirection() { return m_TargetDirection;  }
	ActionTypes GetActionType() { return m_actionType; }
	ActionTarget GetActionTarget() { return m_actionTarget; }
	double GetCriticalWeigth() { return 0.1; } // todo wo steht das?
	int GetGraphic() { return m_graphic; }
	COMPASS_DIRECTION GetPosition() { return m_position; } 
	bool IsActive() { return m_active;  }
	void Activate() { m_active = true; }
	void Deactivate() { m_active = false; }
	bool IsOnceOnly() { return m_once_only > 0; }
	int Action() { return m_action; }


	// impro gate coding
	void IncreaseGate() { m_gateCounter++; }
	void DecreaseGate() { m_gateCounter--; }
	bool GateFull() { return m_gateCounter==2; }

	bool delayDone() { return m_delayCounter == 0; }
	void decreaseDelay() { m_delayCounter--; }
	void resetDelay() { m_delayCounter = m_delay; }
	int GetDelay() { return m_delay; }

private:
	int m_index;
	COMPASS_DIRECTION m_position;
	ActuatorType m_type;
	int m_graphic;
	int m_data;
	int m_once_only;
	int m_gateCounter;
	int m_delayCounter;
	int m_delay;
	bool m_active;
	int m_action;
	int m_power;
	VEKTOR m_target;
	ActionTypes m_actionType;
	ActionTarget m_actionTarget;
	COMPASS_DIRECTION m_TargetDirection;
};

