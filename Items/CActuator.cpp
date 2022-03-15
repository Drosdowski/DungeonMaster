#include "stdafx.h"
#include "CActuator.h"

CActuator::CActuator(int index, int position, VEKTOR target, ActionTypes actionType, ActionTarget actionTarget, int type) {
	m_index = index;
	m_target[position] = target;
	m_actionType[position] = actionType;
	m_actionTarget[position] = actionTarget;
	m_type = type;
	m_position = position;
}

CActuator::~CActuator() {

}