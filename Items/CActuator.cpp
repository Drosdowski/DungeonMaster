#include "stdafx.h"
#include "CActuator.h"

CActuator::CActuator(int index, int position, VEKTOR actionTarget, ActionTypes actionType, int type) {
	m_index = index;
	m_actionTarget[position] = actionTarget;
	m_actionType[position] = actionType;
	m_type = type;
	m_position = position;
}

CActuator::~CActuator() {

}