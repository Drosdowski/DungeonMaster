#pragma once
#include "ItemConst.h"
class CWeaponConst : public CItemConst
{
public:

	enum AttackType {
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
		AttackType type;
		int dmg;
		int difficult;
		bool useCharge;
	};
	
	AttackStyle style[3];
	int damage;
	int distance;
	int shootDamage;

};

