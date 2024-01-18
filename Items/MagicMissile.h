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
		Dust = 4,
		OpenDoor = 5,
		Lightning = 6
	};
	enum SpellSize {
		Light = 0,
		Medium = 1,
		Strong = 2
	};

	CMagicMissile(MagicMissileType type, int level) { m_type = type; m_isExloding = false; m_strength = CastingFactor(level); }; // 8 - 28

	MagicMissileType GetType() { return m_type; }
	SpellSize GetSize() { return (SpellSize)(int)((m_strength - 8) / 7); }
	bool IsExploding() { return m_isExloding; }
	int GetStrength() { return m_strength; } // Strength für Schaden / Bildgröße -> nicht für Weite!
	void SetStrengh(int strength) { m_strength = strength; }
	void DecreaseStrength() { m_strength--; }
	void Explode() { m_flyForce = VEKTOR{ 0,0,0 }; m_isExloding = true; }


private:
	MagicMissileType m_type;
	int m_strength;
	bool m_isExloding;
	
	int CastingFactor(int level) { return 4 + (level * 4); }

	// Damage = 8 * (Max(1, Min(CloudStrength / 32, 4) + Random(1)) + Random(3)) / (CreaturePoisonResistance + 1)
};

