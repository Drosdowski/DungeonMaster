#include "stdafx.h"
#include "CTeleporter.h"

CTeleporter::CTeleporter(VEKTOR target, int direction, RotationType type, bool visible, bool sound, Scope scope, bool open) {
	m_targetField = target;
	m_targetDirection = direction;
	m_rotationType = type;
	m_isVisible = visible;
	m_sound = sound;
	m_scope = scope;
	m_open = open;
}