#include "stdafx.h"
#include "CActuator.h"

CActuator::CActuator(int index, 
					 COMPASS_DIRECTION position, 
					 VEKTOR target, 
					 ActionTypes actionType, 
					 ActionTarget actionTarget, 
					 int type, 
					 int data, 
					 int graphic, 
					 int once_only,
					 bool action) {
	m_index = index;
	m_target = target;
	m_actionType = actionType;
	m_actionTarget = actionTarget;
	m_type = type;
	m_position = position;
	m_data = data;
	m_graphic = graphic;
	m_once_only = once_only;
	m_active = true;
	m_action = action;
}

CActuator::~CActuator() {

}