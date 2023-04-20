#pragma once
#include "..\Attributes\TeleporterAttributes.h"
class CDMDoc;
class CGrpHeld;
class CDungeonMap;
class CTeleporter
{
public:
	enum TeleporterState {
		Inactive = 0,
		Active = 1
	};

	CTeleporter(TeleporterAttributes attributes, bool visible, TeleporterState open);
	~CTeleporter() {};

	VEKTOR getTargetField() { return m_attributes.target; }
	COMPASS_DIRECTION getTargetDirection() { return (COMPASS_DIRECTION)m_attributes.rotation; }
	TeleporterAttributes::RotationType getRotationType() { return m_attributes.rotationType; }
	TeleporterAttributes::Scope getScope() { if (isOpen()) return m_attributes.scope; else return TeleporterAttributes::Scope::None; }
	int getRotation() { return m_attributes.rotation; }
	bool isVisible() { return m_isVisible && m_open == TeleporterState::Active; }
	bool hasSound() { return m_attributes.sound; }
	void setOpen(TeleporterState value) { m_open = value; }
	void toggleOpen() { m_open = (m_open == TeleporterState::Active ? TeleporterState::Inactive : TeleporterState::Active); }
	void Trigger(CDMDoc* pDoc, CDungeonMap* pMap, VEKTOR telePos);
	bool isOpen() { return (m_open == TeleporterState::Active); }

private:
	bool m_isVisible;
	TeleporterState m_open;
	TeleporterAttributes m_attributes;
	
};

