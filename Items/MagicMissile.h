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

	CMagicMissile(MagicMissileType type) { m_type = type;  };

	MagicMissileType GetType() { return m_type; }

private:
	MagicMissileType m_type;

	// Damage = 8 * (Max(1, Min(CloudStrength / 32, 4) + Random(1)) + Random(3)) / (CreaturePoisonResistance + 1)
};

