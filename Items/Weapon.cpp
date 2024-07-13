#include "stdafx.h"
#include "Weapon.h"
#include <cassert>

CWeapon::CWeapon(int index, CWeaponAttributes attribute) : CItem(index, WeaponItem ) {
	m_attribute = attribute;
}

CWeapon::~CWeapon() {
}

void CWeapon::reduceCharges() {
	m_attribute.charges = max(0, m_attribute.charges - 1);
}

int CWeapon::GetOffsetForGroup(bool active) {
	if (m_attribute.type == CWeaponAttributes::Torch) {
		if (active) {
			return 4 + (int)(m_attribute.charges / 4);
		}
		else {
			return 4;
		}
	}
	else if (m_attribute.type == CWeaponAttributes::BoltBlade)
	{
		if (m_attribute.charges > 0)
			return 25;
		else
			return 24;
	} else if (m_attribute.type >= 8 && m_attribute.type < 38) {
		return m_attribute.type - 8;
	}
	else if (m_attribute.type == CWeaponAttributes::HornOfFear) {
		return 7;
	}
	assert(false);
}

int CWeapon::GetSheetForGroup() {
	if (m_attribute.type < 8)
		return 0;
	else if (m_attribute.type < 38)
		return 1;
	else if (m_attribute.type == CWeaponAttributes::HornOfFear)
		return 4;
	else
		assert(false); // todo !!
	return -1;
}

CItem::ItemGroup CWeapon::GetGroup() {
	if (m_attribute.type >= CWeaponAttributes::Rock && m_attribute.type <= CWeaponAttributes::ThrowingStar) return ItemGroup::Throwable;
	return ItemGroup::Weapon;
}

double CWeapon::GetWeight() {
	return m_attribute.fixAttributes.weight[0]; // todo sub berücksichtigen!
}

CString CWeapon::GetName() {
	switch (m_attribute.type) {
	case CWeaponAttributes::EyeOfTime: return "Eye Of Time";
	case CWeaponAttributes::Stormring: return "Stormring";
	case CWeaponAttributes::Torch: return "Torch";
	case CWeaponAttributes::Flamitt: return "Flamitt";
	case CWeaponAttributes::StaffOfClaws: return "Staff of Claws";
	case CWeaponAttributes::BoltBlade: return "Bolt Blade";
	case CWeaponAttributes::Fury: return "Fury";
	case CWeaponAttributes::TheFirestaff: return "The Firestaff";
	case CWeaponAttributes::Dagger: return "Dagger";
	case CWeaponAttributes::Falchion: return "Falchion";
	case CWeaponAttributes::Sword: return "Sword";
	case CWeaponAttributes::Rapier: return "Rapier";
	case CWeaponAttributes::Sabre: return "Sabre";
	case CWeaponAttributes::SamuraiSword: return "Samurai Sword";
	case CWeaponAttributes::Delta: return "Delta";
	case CWeaponAttributes::DiamondEdge: return "Diamond Edge";
	case CWeaponAttributes::VorpalBlade: return "Vorpal Blade";
	case CWeaponAttributes::TheInquisitor: return "The Inquisitor";
	case CWeaponAttributes::Axe: return "Axe";
	case CWeaponAttributes::Hardcleave: return "Hardcleave";
	case CWeaponAttributes::Mace: return "Mace";
	case CWeaponAttributes::MaceOfOrder: return "Mace Of Order";
	case CWeaponAttributes::Morningstar: return "Morningstar";
	case CWeaponAttributes::Club: return "Club";
	case CWeaponAttributes::StoneClub: return "Stone Club";
	case CWeaponAttributes::Bow: return "Bow";
	case CWeaponAttributes::Crossbow: return "Crossbow";
	case CWeaponAttributes::Arrow: return "Arrow";
	case CWeaponAttributes::Slayer: return "Slayer";
	case CWeaponAttributes::Sling: return "Sling";
	case CWeaponAttributes::Rock: return "Rock";
	case CWeaponAttributes::PoisonDart: return "Poison Dart";
	case CWeaponAttributes::ThrowingStar: return "Throwing Star";
	case CWeaponAttributes::Stick: return "Stick";
	case CWeaponAttributes::Staff: return "Staff";
	case CWeaponAttributes::Wand: return "Wand";
	case CWeaponAttributes::Teowand: return "Teowand";
	case CWeaponAttributes::YewStaff: return "YewStaff";
	case CWeaponAttributes::StaffOfIrra: return "Staff Of Irra";
	case CWeaponAttributes::CrossOfNeta: return "Cross Of Neta";
	case CWeaponAttributes::SerpentStaff: return "Serpent Staff";
	case CWeaponAttributes::DragonSpit: return "Dragon Spit";
	case CWeaponAttributes::SceptreOfLyf: return "Sceptre Of Lyf";
	case CWeaponAttributes::HornOfFear: return "Horn Of Fear";
	case CWeaponAttributes::SpeedBow: return "Speed Bow";
	case CWeaponAttributes::FireStaffComplete: return "Fire Staff Complete";
	case CWeaponAttributes::Conduit: return "Conduit";

	}
}