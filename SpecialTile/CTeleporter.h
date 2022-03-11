#pragma once
class CTeleporter
{
public:
	enum RotationType {
		Absolute,
		Relative
	};
	enum Scope {
		Items,
		Creatures,
		Items_Party,
		All
	};
	CTeleporter(VEKTOR target, int direction, RotationType type, bool visible, bool sound, Scope scope, bool open);
	~CTeleporter() {};

	VEKTOR getTargetField() { return m_targetField; }
	int getTargetDirection() { return m_targetDirection; }
	RotationType getRotationType() { return m_rotationType; }
	Scope getScope() { return m_scope; }
	bool isVisible() { return m_isVisible; }
	bool hasSound() { return m_sound; }

private:
	VEKTOR m_targetField;
	int m_targetDirection;
	RotationType m_rotationType;
	bool m_isVisible;
	bool m_sound;
	bool m_open;
	Scope m_scope;
	
};

