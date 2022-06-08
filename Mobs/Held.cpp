// Held.cpp : implementation file
//

#include "stdafx.h"
#include "Rucksack.h"
#include "..\CalculationHelper\CHelpfulValues.h"
#include "..\Items\Item.h"
#include "..\Items\CMiscellaneous.h"
#include "..\Items\Cloth.h"
#include "..\Items\Weapon.h"
#include "Monster.h"
#include <Attributes/ClothAttributes.h>
#include "..\XMLParser\AttackInfos.h"
#include "..\XMLParser\MonsterInfos.h"
// following includes for compass
#include "Held.h"
#include "..\Attributes\MiscellaneousAttributes.h"
#include <cassert>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHeld

CHeld::CHeld(int iIndex, CString strName): CCharacter(true)
{
	m_HP.Max = 100; // todo level up: increase http://dmweb.free.fr/?q=node/691
	m_MA.Max = 100;
	m_ST.Max = 100;

	m_iCurrentLuck = 0;

	m_sVitals.str.Max = 60; m_sVitals.str.Aktuell = 60;
	m_sVitals.dex.Max = 50; m_sVitals.dex.Aktuell = 50;
	m_sVitals.vit.Max = 40; m_sVitals.vit.Aktuell = 40;
	m_sVitals.wis.Max = 30; m_sVitals.wis.Aktuell = 30;
	
	m_HP.Aktuell = m_HP.Max;
	m_ST.Aktuell = m_ST.Max;
	m_MA.Aktuell = m_MA.Max;
	m_bAktiv = true;
	m_strName = strName;
	m_iIndex = iIndex;
	m_iFood = maxFood;
	m_iWater = maxWater;
	for (int i = 1; i<5; i++)
		m_sExp[i] = 200;
	switch (iIndex)
	{
	case 1:
		m_Farbe[1] = HELLGRUEN; break;
	case 2:
		m_Farbe[2] = GELB; break;
	case 3:
		m_Farbe[3] = ROT; break;
	case 4:
		m_Farbe[4] = BLAU; break;
	}

	for (int i = 0; i < 30; i++) {
		m_itemCarrying[i] = NULL;
	}

	m_pRucksack = new CRucksack();
}


CHeld::~CHeld()
{
	for (int i = 0; i < 30; i++) {
		if (m_itemCarrying[i]) {

			DelItem(m_itemCarrying[i]);
		}
	}
	delete m_pRucksack;
	DelItem(m_pItemInHand);
}

void CHeld::DelItem(CItem* pItem) {
	if (pItem) {
		if (pItem->getItemType() == CItem::ItemType::WeaponItem)
			delete (CWeapon*)pItem;
		else if (pItem->getItemType() == CItem::ItemType::MiscItem)
			delete (CMiscellaneous*)pItem;
		else  if (pItem->getItemType() == CItem::ItemType::ClothItem)
			delete (CCloth*)pItem;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CHeld message handlers



/////////////////////////////////////////////////////////////////////////////
/////////////////////////////// Hilfsfunktionen /////////////////////////////
/////////////////////////////////////////////////////////////////////////////

bool CHeld::Altern()
{
	bool alive = CCharacter::Altern();
	if (m_dealingDmg > 0)
	{
		m_dealingDmg = 0;
		// phase
	}

	// erstmal konstant, später hp & st abhängig 
	// von VIT, ma von WIS sowie von FOOD & WATER
	if (alive)
	{
		WerteTemporaerAendern(1, 1, 1);
		//m_iFood--;
		//m_iWater--;
		if (m_iFood < 50)
			WerteTemporaerAendern(0, -1, 0);
		if (m_iWater < 50)
			WerteTemporaerAendern(0, -1, 0);
		if (m_iFood < 15)
			WerteTemporaerAendern(0, -2, 0);
		if (m_iWater < 15)
			WerteTemporaerAendern(0, -2, 0);
		if (m_ST.Aktuell <= 0)
		{
			m_HP.Aktuell = 0;	// zu Tode erschöpft
			return false;
		}
	}
	return alive;
}

void CHeld::WerteTemporaerAendern(int hp, int st, int ma)
{
	m_HP.Aktuell = min(max(hp + m_HP.Aktuell, 0), m_HP.Max);
	m_ST.Aktuell = min(max(st + m_ST.Aktuell, 0), m_ST.Max);
	m_MA.Aktuell = min(max(ma + m_MA.Aktuell, 0), m_MA.Max);
}

int CHeld::CalcDmg(CWeapon* weapon, CAttackInfos* attackInfos, CMonsterInfos* monsterInfos, CGrpChar* pOpponents, int levelDif) {
	CAttackConst ac = attackInfos->GetAttack(weapon->getIndex());
	CMonsterConst mc = monsterInfos->GetMonsterInfo(weapon->getIndex());
	// https://www.dungeon-master.com/forum/viewtopic.php?t=31345
	// todo xp gain  --- Mastery = log2(Experience=469)
	
	if (!hitSucessful(ac, pOpponents, levelDif))
	{
		WerteTemporaerAendern(0, -(2 + (rand() % 1)), 0); // daneben
		return 0;
	}
	else {
		WerteTemporaerAendern(0, -ac.stamina + (rand() % 1), 0); // treffer!

		// damage berechnen!
		CWeapon* weapon = (CWeapon*)m_itemCarrying[1];
		int d3_strength = m_sVitals.str.Aktuell;
		int d5_load_coefficient = MaxLoad();
		int d6_weapon_weight = weapon->GetWeight();
		int d7_damage_coefficient = d3_strength + (rand() % 15);

		ReduceWhenOverload(d6_weapon_weight, d5_load_coefficient, d7_damage_coefficient);
		d7_damage_coefficient += weapon->GetAttributes().damage;
		// d7_damage_coefficient += TODO 2* SKILL (SWING / SHOOT / THROW ...)
		if (m_ST.Aktuell / m_ST.Max < 0.5) {
			// tired...
			d7_damage_coefficient /= 2; // +???
		}
		// TODO if hand hurt d7_damage_coefficient /= 2; 

		int d4_AC_coefficient = ACC_Coeff(levelDif, mc.armor);
		if (weapon->GetType() == CWeaponAttributes::WeaponType::DiamondEdge) {
			d4_AC_coefficient -= (d4_AC_coefficient / 4);
		}

		d7_damage_coefficient += (rand() % 32) - d4_AC_coefficient;
		int d6_damage = d7_damage_coefficient;
		if (d7_damage_coefficient <= 1) {
			d7_damage_coefficient = rand() % 3;
		}
		if (d7_damage_coefficient == 0) {
			m_ST.Aktuell -= (rand() % 1 + 2);
			return 0;
		}
		else {
			d6_damage += rand() % 16;
		}
		if (d6_damage > 0 || (rand() % 1 > 0)) {
			d7_damage_coefficient += rand() % 3;
			if (rand() % 3 == 0) {
				d7_damage_coefficient += rand() % 16 + d6_damage;
			}
		}
		d7_damage_coefficient /= 2;
		int d0 = 0;
		if (d7_damage_coefficient > 0)
			d0 = rand() % d7_damage_coefficient;
		d7_damage_coefficient += rand() % 4 + d0;
		d7_damage_coefficient += rand() % d7_damage_coefficient;
		d7_damage_coefficient /= 4;
		d7_damage_coefficient += rand() % 4 + 1;

		//int d0_skillRef = rand() % 64;
		//nt d1_mastery todo skill mastery + 10
		m_ST.Aktuell -= (rand() % 3 + 4);

		return d7_damage_coefficient;
	}

}

int CHeld::ACC_Coeff(int levelDif, int armor) {
	return levelDif + armor + (rand() % 32);
}

void CHeld::ReduceWhenOverload(int d6_weapon_weight, int d5_load_coefficient, int &dmg) {
	int temp_coefficient[2];

	if (d6_weapon_weight <= d5_load_coefficient)
		dmg += d6_weapon_weight - 12;
	else
	{
		temp_coefficient[0] = ((d5_load_coefficient - 12) / 2 + d5_load_coefficient);
		temp_coefficient[1] = temp_coefficient[0];
		if (d6_weapon_weight <= temp_coefficient[1])
			dmg += (d6_weapon_weight - d5_load_coefficient) / 2;
		else
			dmg = (dmg - 2 * (d6_weapon_weight - temp_coefficient[0]));
	}
}

bool CHeld::hitSucessful(CAttackConst ac, CGrpChar* pOpponents, int levelDif) {
	double d6_hitProbaility = ac.to_hit / 75.0;
	int d7_baseDamage = ac.damage;
	int quickness = m_sVitals.dex.Aktuell + (rand() % 8);
	int loadingEffect = (int)((quickness / 2) * CurLoad() / MaxLoad());
	quickness -= loadingEffect;
	int chanceToHit = min(max((quickness / 2), rand() % 8 + 1), 100 - rand() % 8);

	int enemyDef = 10; // todo enemy def
	int d1_neededToHit = (enemyDef + rand() % 32 + levelDif) - 16;
	bool successfulHit = (chanceToHit > d1_neededToHit);
	if (!successfulHit) {
		if (rand() % 3 == 0)
			return true;
		else
		{
			int luckNeeded = 75 - d6_hitProbaility;
			if ((rand() % 100) > luckNeeded)
				return true;
			else {
				if ((rand() % m_iCurrentLuck) > luckNeeded) {
					m_iCurrentLuck -= 2;
					return true;
				}
				else {
					m_iCurrentLuck += 2;
					return false;
				}
			}
		}
	}
	return true;
}

void CHeld::Essen(int amount) {
	m_iFood = min(maxFood, m_iFood + amount);
}

void CHeld::Trinken(int amount) {
	m_iWater = min(maxWater, m_iWater + amount);
}

void CHeld::TakeItemInHand(CItem* item)
{
	if (m_pItemInHand == NULL)
		m_pItemInHand = item;
	else
		assert(false); // ???
}

void CHeld::EmptyHand() {
	// kein delete, Objekt ist jetzt woanders...
	m_pItemInHand = NULL;
}

CItem* CHeld::SwitchItemAt(int index, CItem* item)
{
	CItem* carryingBefore = m_itemCarrying[index];
	m_itemCarrying[index] = item;
	ChangeCompass();
	return carryingBefore;
}

double CHeld::MaxLoad() {
	// http://dmweb.free.fr/?q=node/691
	double maxLoad = (8 * m_sVitals.str.Aktuell + 100) / 10;
	// todo: if injured => MaxLoad = 3 * MaxLoad / 4 
	if (m_itemCarrying[6] && m_itemCarrying[6]->getItemType() == CClothAttributes::ClothType::ElvenBoots) {
		maxLoad = round1(17 * maxLoad / 16);
	}
	if (m_ST.Aktuell >= m_ST.Max / 2) {
		return maxLoad;
	}
	else {
		// BaseMaxLoad = BaseMaxLoad / 2 + (((BaseMaxLoad / 2) * Stamina) / (MaxStamina / 2))
		return round1(maxLoad / 2 + (((maxLoad / 2) * m_ST.Aktuell) / (m_ST.Max / 2)));
	}
}

double CHeld::CurLoad() {
	double sum = 0;
	for (int i = 0; i < 30; i++)
	{
		CItem* item = m_itemCarrying[i];
		if (item)
			sum += item->GetWeight();
	}
	return sum;
}

double CHeld::round1(double value) {
	return floor(value * 10.0 + .5) / 10.0;
}

void CHeld::ChangeCompass() {
	for (int i = 0; i < 30; i++)
	{
		CItem* item = m_itemCarrying[i];
		if (item && item->getItemType() == CItem::ItemType::MiscItem)
		{
			if (item->GetType() == CMiscellaneousAttributes::MiscItemType::Compass) {
				CMiscellaneous* misc = (CMiscellaneous*)item;
				
				misc->SetSubtype(GetDirection());
			}

		}
	}
}