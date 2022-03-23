#pragma once
#include "CTeleporterAttributes.h"
class CTeleporter
{
public:
	CTeleporter(TeleporterAttributes attributes, bool visible, bool open);
	~CTeleporter() {};

	VEKTOR getTargetField() { return m_attributes.target; }
	COMPASS_DIRECTION getTargetDirection() { return (COMPASS_DIRECTION)m_attributes.rotation; }
	TeleporterAttributes::RotationType getRotationType() { return m_attributes.rotationType; }
	TeleporterAttributes::Scope getScope() { if (m_open) return m_attributes.scope; else return TeleporterAttributes::Scope::None; }
	bool isVisible() { return m_isVisible; }
	bool hasSound() { return m_attributes.sound; }

private:
	bool m_isVisible;
	bool m_open;
	TeleporterAttributes m_attributes;
	
};

