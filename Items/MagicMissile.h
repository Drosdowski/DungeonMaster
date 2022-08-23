#pragma once
#include "MovingObject.h"
class CMagicMissile : public CMovingObject
{
public:
	enum MagicMissileType {
		Fireball = 0,
		Poison = 1,
		PoisonBlob = 2,
		AntiMagic = 3,
		Dust = 4
	};
	enum SpellSize {
		Light = 0,
		Medium = 1,
		Strong = 2
	};

	CMagicMissile(MagicMissileType type, int size) { m_type = type; m_isExloding = false; m_strength = size * 10; };

	MagicMissileType GetType() { return m_type; }
	SpellSize GetSize() { return (SpellSize)(int)(m_strength / 10); }
	bool IsExploding() { return m_isExloding; }
	int GetStrength() { return m_strength; } // Strength für Schaden / Bildgröße -> nicht für Weite!
	void SetStrengh(int strength) { m_strength = strength; }
	void DecreaseStrength() { m_strength--; }
	void Explode() { m_flyForce = VEKTOR{ 0,0,0 }; m_isExloding = true; }


private:
	MagicMissileType m_type;
	int m_strength;
	bool m_isExloding;

	// Damage = 8 * (Max(1, Min(CloudStrength / 32, 4) + Random(1)) + Random(3)) / (CreaturePoisonResistance + 1)
};

