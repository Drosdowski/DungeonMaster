#pragma once
#include "MovingObject.h"
class CMagicMissile : public CMovingObject
{
public:
	enum MagicMissileType {
		None = -1,
		OpenDoor = 0,
		Lightning = 1,
		Fireball = 2,
		Poison = 3,
		PoisonBlob = 4,
		AntiMagic = 5,
		Dust = 6
	};
	enum SpellSize {
		Light = 0,
		Medium = 1,
		Strong = 2
	};

	CMagicMissile(MagicMissileType type, int level, VEKTOR origin) { m_type = type; m_isExloding = false; m_strength = CastingFactor(level); m_startingCoord = origin;  m_disposed = false; } // 8 - 28

	MagicMissileType GetType() { return m_type; }
	SpellSize GetSize() { return (SpellSize)(int)((m_strength - 8) / 7); }
	bool IsExploding() { return m_isExloding; }
	int GetStrength() { return m_strength; } // Strength für Schaden / Bildgröße -> nicht für Weite!
	void SetStrengh(int strength) { m_strength = strength; }
	void DecreaseStrength() { m_strength--; }
	void Explode() { m_flyForce = VEKTOR{ 0,0,0 }; m_isExloding = true; }
	VEKTOR GetOrigin() { return m_startingCoord; }
	bool isDisposed() { return m_disposed; }
private:
	MagicMissileType m_type;
	int m_strength;
	bool m_isExloding;
	VEKTOR m_startingCoord;
	bool m_disposed;
	
	int CastingFactor(int level) { return 4 + (level * 4); }

	// Damage = 8 * (Max(1, Min(CloudStrength / 32, 4) + Random(1)) + Random(3)) / (CreaturePoisonResistance + 1)
};

