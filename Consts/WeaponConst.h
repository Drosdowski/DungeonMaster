#pragma once
#include "ItemConst.h"
class CWeaponConst : public CItemConst
{
public:

	enum AttackType {
		none,
		punch,
		swing,
		slash,
		jab,
		chop,
		melee,
		parry,
		throw_,
		stab,
		thrust,
		cleave,
		berzerk,
		bash,
		shoot,
		brandish,
		confuse,
		stun,
		calm,
		blowhorn,
		disrupt,
		dispell,
		lightning,
		heal,
		light,
		fireball,
		fireshield,
		freezeLife,
		spellshield,
		window,
		invoke,
		fuse,
		fluxcage
	};
	class AttackStyle {
		AttackType type = none;
		int dmg = 0;
		int difficult = 0;
		bool useCharge = 0;
	};
	
	AttackStyle style[3];
	int damage = 0;
	int distance = 0;
	int shootDamage = 0;

};

