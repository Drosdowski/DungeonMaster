#pragma once
#include "MovingObject.h"
class CMagicMissile : public CMovingObject
{
public:
	enum MagicMissileType {
		Fireball = 0,
		Poison = 1,
		PoisonBlob = 2,
		AntiMagic = 3
	};
	enum SpellSize {
		Light = 0,
		Medium = 1,
		Strong = 2
	};

	CMagicMissile(MagicMissileType type) { m_type = type;  };

	MagicMissileType GetType() { return m_type; }
	SpellSize GetSize() { (SpellSize)(int)(m_size / 2); }
	int GetStrength() { m_size; }
	void SetStrengh(int size) { m_size = size; }


private:
	MagicMissileType m_type;
	int m_size;
	

	// Damage = 8 * (Max(1, Min(CloudStrength / 32, 4) + Random(1)) + Random(3)) / (CreaturePoisonResistance + 1)
};

