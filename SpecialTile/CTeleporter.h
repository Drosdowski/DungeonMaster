#pragma once
#include "CTeleporterAttributes.h"
class CTeleporter
{
public:
	CTeleporter(TeleporterAttributes attributes, bool visible, bool open);
	~CTeleporter() {};

	VEKTOR getTargetField() { return m_attributes.target; }
	int getTargetDirection() { return m_attributes.rotation; }
	TeleporterAttributes::RotationType getRotationType() { return m_attributes.rotationType; }
	TeleporterAttributes::Scope getScope() { return m_attributes.scope; }
	bool isVisible() { return m_isVisible; }
	bool hasSound() { return m_attributes.sound; }

private:
	bool m_isVisible;
	bool m_open;
	TeleporterAttributes m_attributes;
	
};

