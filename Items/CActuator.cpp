#include "stdafx.h"
#include "CActuator.h"

CActuator::CActuator(int index, COMPASS_DIRECTION position, VEKTOR target, ActionTypes actionType, ActionTarget actionTarget, int type, int graphic) {
	m_index = index;
	m_target = target;
	m_actionType = actionType;
	m_actionTarget = actionTarget;
	m_type = type;
	m_position = position;
	m_graphic = graphic;
}

CActuator::~CActuator() {

}