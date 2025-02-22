#include "stdafx.h"
#include "CActuator.h"

CActuator::CActuator(int index, 
					 COMPASS_DIRECTION position, 
					 VEKTOR target, 
					 ActionTypes actionType, 
					 ActionTarget actionTarget, 
					 COMPASS_DIRECTION direction,
					 ActuatorType type,
					 int data, 
					 int graphic, 
					 int once_only,
					 int delay,
					 int action,
					 int power) {
	m_index = index;
	m_target = target;
	m_actionType = actionType;
	m_actionTarget = actionTarget;
	m_TargetDirection = direction;
	m_type = type;
	m_position = position;
	m_data = data;
	m_graphic = graphic;
	m_once_only = once_only;
	m_delay = delay * DELAY_FACTOR;
	m_active = true;
	m_action = action;
	m_gateCounter = 0;
	m_power = power;
	resetDelay();
}

CActuator::~CActuator() {

}