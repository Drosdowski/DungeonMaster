#include "stdafx.h"
#include "CActuator.h"

CActuator::CActuator(int index, VEKTOR actionTarget, ActionTypes actionType, int type) {
	m_index = index;
	m_actionTarget = actionTarget;
	m_actionType = actionType;
	m_type = type;
}

CActuator::~CActuator() {

}