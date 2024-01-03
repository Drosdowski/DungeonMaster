// Held.cpp : implementation file
//

#include "stdafx.h"
#include "Rucksack.h"
#include "..\CalculationHelper\CHelpfulValues.h"
#include "..\Items\Item.h"
#include "..\Items\CMiscellaneous.h"
#include "..\Items\Cloth.h"
#include "..\Items\Weapon.h"
#include "..\Items\Scroll.h"
#include "..\Items\Container.h"
#include "Monster.h"
#include "Champion.h"
#include "MobGroups/GrpMonster.h"
#include <Attributes/ClothAttributes.h>
#include "..\XMLParser\AttackInfos.h"
#include "..\XMLParser\MonsterInfos.h"
// following includes for compass
#include "Held.h"
#include "..\Attributes\MiscellaneousAttributes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHeld

CHeld::CHeld(int iIndex, CChampion* champ, int hp_akt, int st_akt, int ma_akt): CCharacter(true)
{
	m_HP.Max = champ->hp();
	m_ST.Max = champ->st();
	m_MA.Max = champ->ma();
	m_HP.Aktuell = hp_akt; // todo level up: increase http://dmweb.free.fr/?q=node/691
	m_ST.Aktuell = st_akt;
	m_MA.Aktuell = ma_akt;
	
	m_sVitals = champ->GetVitals();
	
	m_bAktiv = true;
	m_strName = champ->GetName();
	m_iIndex = iIndex;
	m_iFood = maxFood;
	m_iWater = maxWater;
	m_fightLevel = champ->fightLevel();
	m_ninjaLevel = champ->ninjaLevel();
	m_priestLevel = champ->priestLevel();
	m_wizardLevel = champ->wizardLevel();
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
	CMiscellaneousAttributes att;
	att.type = CMiscellaneousAttributes::MiscItemType::Bones;
	att.subtype = iIndex;
	CMiscConst fixAtt;
	fixAtt.weight[0] = 10;
	att.fixAttributes = fixAtt;

	m_itemCarrying[30] = new CMiscellaneous(255, att);
	m_male = champ->IsMale();

	delete champ;

	m_pRucksack = new CRucksack();

	m_spell = new int[5];

	m_iRuneTable = 1;
	m_delay = 0;
}


CHeld::~CHeld()
{
	for (int i = 0; i < 31; i++) {
		if (m_itemCarrying[i]) {

			DelItem(m_itemCarrying[i]);
		}
	}
	delete m_pRucksack;

	if (m_spell != NULL) delete[] m_spell;
}

void CHeld::DelItem(CItem* pItem) {
	if (pItem) {
		if (pItem->getItemType() == CItem::ItemType::WeaponItem)
			delete (CWeapon*)pItem;
		else if (pItem->getItemType() == CItem::ItemType::MiscItem)
			delete (CMiscellaneous*)pItem;
		else if (pItem->getItemType() == CItem::ItemType::ClothItem)
			delete (CCloth*)pItem;
		else if (pItem->getItemType() == CItem::ItemType::PotionItem)
			delete (CPoint*)pItem;
		else if (pItem->getItemType() == CItem::ItemType::ScrollItem)
			delete (CScroll*)pItem;
		else if (pItem->getItemType() == CItem::ItemType::ContainerItem)
			delete (CContainer*)pItem;
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
		if (m_iReceivedDmg > 0) {
			// damage
			alive = ReceiveDamage(m_iReceivedDmg);
			m_iReceivedDmg = 0;
		}

		WerteTemporaerAendern(0.1, 0.1, 0.1);
		if (footWaterAktiv) {
			m_iFood--;
			m_iWater--;
		}
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
			m_HP.Aktuell = 0;	
		}
		if (m_delay > 0) {
			m_delay--;
		}
	}
	return alive;
}

void CHeld::WerteSetzen(double hp, double st, double ma) {
	m_HP.Aktuell = hp;
	m_ST.Aktuell = st;
	m_MA.Aktuell = ma;
}

void CHeld::WerteTemporaerAendern(double hp, double st, double ma)
{
	m_HP.Aktuell = min(max(hp + m_HP.Aktuell, 0), m_HP.Max);
	m_ST.Aktuell = min(max(st + m_ST.Aktuell, 0), m_ST.Max);
	m_MA.Aktuell = min(max(ma + m_MA.Aktuell, 0), m_MA.Max);
}

int CHeld::CalcDmg(CWeapon* weapon, CAttackConst ac, CMonsterConst mc, CGrpMonster* pOpponents, int levelDif) {
	// https://www.dungeon-master.com/forum/viewtopic.php?t=31345
	// todo xp gain  --- Mastery = log2(Experience=469)
	// https://gamefaqs.gamespot.com/snes/588299-dungeon-master/faqs/33244 => Exo Gain! (5e. Actions)
	
	if (!hitSucessful(ac, mc, levelDif))
	{
		WerteTemporaerAendern(0, -(2 + (rand() % 1)), 0); // daneben
		return 0;
	}
	else {
		WerteTemporaerAendern(0, -ac.stamina + (rand() % 1), 0); // treffer!

		// damage berechnen!
		CWeapon* weapon = (CWeapon*)m_itemCarrying[1];
		double d3_strength = m_sVitals.str.Aktuell;
		double d5_load_coefficient = MaxLoad();
		double d6_weapon_weight = weapon ? weapon->GetWeight() : 0;
		double d7_damage_coefficient = d3_strength + (rand() % 15);

		ReduceWhenOverload(d6_weapon_weight, d5_load_coefficient, d7_damage_coefficient);
		d7_damage_coefficient += weapon ? weapon->GetAttributes().damage : 1;
		// d7_damage_coefficient += TODO 2* SKILL (SWING / SHOOT / THROW ...)
		if (m_ST.Aktuell / m_ST.Max < 0.5) {
			// tired...
			d7_damage_coefficient /= 2; // +???
		}
		// TODO if hand hurt d7_damage_coefficient /= 2; 

		int d4_AC_coefficient = ACC_Coeff(levelDif, mc.armor);
		if (weapon && weapon->GetType() == CWeaponAttributes::WeaponType::DiamondEdge) {
			d4_AC_coefficient -= (d4_AC_coefficient / 4);
		}

		d7_damage_coefficient += (rand() % 32) - d4_AC_coefficient;
		double d6_damage = d7_damage_coefficient;
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
			d0 = rand() % (int)d7_damage_coefficient;
		d7_damage_coefficient += rand() % 4 + d0;
		d7_damage_coefficient += rand() % (int)d7_damage_coefficient;
		d7_damage_coefficient /= 4;
		d7_damage_coefficient += rand() % 4 + 1;

		//int d0_skillRef = rand() % 64;
		//nt d1_mastery todo skill mastery + 10
		m_ST.Aktuell -= (rand() % 3 + 4);

		return (int)d7_damage_coefficient;
	}

}

int CHeld::ACC_Coeff(int levelDif, int armor) {
	return levelDif + armor + (rand() % 32);
}

void CHeld::ReduceWhenOverload(double d6_weapon_weight, double d5_load_coefficient, double &dmg) {
	double temp_coefficient[2];

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

bool CHeld::hitSucessful(CAttackConst ac, CMonsterConst mc, int levelDif) {
	double d6_hitProbaility = ac.to_hit / 75.0;
	int d7_baseDamage = ac.damage;
	int quickness = (int)m_sVitals.dex.Aktuell + (rand() % 8);
	int loadingEffect = (int)((quickness / 2) * CurLoad() / MaxLoad());
	quickness -= loadingEffect;
	int chanceToHit = min(max((quickness / 2), rand() % 8 + 1), 100 - rand() % 8);

	int d1_neededToHit = (mc.defense + rand() % 32 + levelDif) - 16;
	bool successfulHit = (chanceToHit > d1_neededToHit);
	if (!successfulHit) {
		if (rand() % 3 == 0)
			return true;
		else
		{
			int luckNeeded = 75 - (int)d6_hitProbaility;
			if ((rand() % 100) > luckNeeded)
				return true;
			else {
				if (((int)m_sVitals.luk.Aktuell > 0) && (rand() % (int)m_sVitals.luk.Aktuell) > luckNeeded) {
					m_sVitals.luk.Aktuell -= 2;
					return true;
				}
				else {
					m_sVitals.luk.Aktuell += 2;
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

CItem* CHeld::SwitchItemAt(int index, CItem* item)
{
	CItem* carryingBefore = m_itemCarrying[index];
	m_itemCarrying[index] = item;
	ChangeCompass();
	if (item->getItemType() == CItem::ScrollItem) {
		CScroll* pScroll = (CScroll*)item;
		if (index == 1)
			pScroll->SetOpen(1);
		else
			pScroll->SetOpen(0);
	} else if (item->getItemType() == CItem::ContainerItem) {
		CContainer* pContainer = (CContainer*)item;
		if (index == 1)
			pContainer->SetOpen(true);
		else
			pContainer->SetOpen(false);
	}

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

int CHeld::Armour() {
	int ac = 0;
	for (int i = 0; i < 30; i++)
	{
		CItem* item = m_itemCarrying[i];
		if (item)
			ac += item->GetArmourClass();
	}
	return ac;
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

bool CHeld::UseMana(int mana)
{
	if (m_MA.Aktuell >= mana)
	{ 
		m_MA.Aktuell -= mana;
		return true;
	}
	return false;
}

int CHeld::fightLevel() {
	return max(m_fightLevel.Club, max(m_fightLevel.Parry, max(m_fightLevel.Swing, m_fightLevel.Thrust)));
}
int CHeld::ninjaLevel() {
	return max(m_ninjaLevel.Fight, max(m_ninjaLevel.Shoot, max(m_ninjaLevel.Steal, m_ninjaLevel.Throw)));
}
int CHeld::priestLevel() {
	return max(m_priestLevel.Defend, max(m_priestLevel.Heal, max(m_priestLevel.Identify, m_priestLevel.Influence)));
}
int CHeld::wizardLevel() {
	return max(m_wizardLevel.Air, max(m_wizardLevel.Earth, max(m_wizardLevel.Fire, m_wizardLevel.Water)));
}

CString CHeld::GetSpellForSaveGame() { 
	CString text = "";
 	if (m_spell[1] > 0) { text.AppendFormat("%i", m_spell[1]); }
	if (m_spell[2] > 0) { text.AppendFormat(",%i", m_spell[2]); }
	if (m_spell[3] > 0) { text.AppendFormat(",%i", m_spell[3]); }
	if (m_spell[4] > 0) { text.AppendFormat(",%i", m_spell[4]); }
	return text;
}

CString CHeld::GetSkillsForSaveGame() {
	CString text = "";
	text.AppendFormat("%i,", m_fightLevel.Club);
	text.AppendFormat("%i,", m_fightLevel.Parry);
	text.AppendFormat("%i,", m_fightLevel.Swing);
	text.AppendFormat("%i,", m_fightLevel.Thrust);
			    
	text.AppendFormat("%i,", m_ninjaLevel.Fight);
	text.AppendFormat("%i,", m_ninjaLevel.Shoot);
	text.AppendFormat("%i,", m_ninjaLevel.Steal);
	text.AppendFormat("%i,", m_ninjaLevel.Throw);
			    
	text.AppendFormat("%i,", m_priestLevel.Identify);
	text.AppendFormat("%i,", m_priestLevel.Heal);
	text.AppendFormat("%i,", m_priestLevel.Influence);
	text.AppendFormat("%i,", m_priestLevel.Defend);
			    
	text.AppendFormat("%i,", m_wizardLevel.Fire);
	text.AppendFormat("%i,", m_wizardLevel.Air);
	text.AppendFormat("%i,", m_wizardLevel.Earth);
	text.AppendFormat("%i",  m_wizardLevel.Water);

	return text;
}

void CHeld::SetSpellFromSaveGame(CString spell) {
	int i = 0;
	m_iRuneTable = 1;
	for (CString sItem = spell.Tokenize(",", i); i >= 0; sItem = spell.Tokenize(",", i))
	{
		m_spell[m_iRuneTable] = atoi(sItem);
		m_iRuneTable += 1;
	}

}

void CHeld::SetSkillsFromSaveGame(CString skills) {
	CStringArray saItems;
	int i = 0;
	for (CString sItem = skills.Tokenize(",", i); i >= 0; sItem = skills.Tokenize(",", i))
	{
		saItems.Add(sItem);
	}

	m_fightLevel.Club = atoi(saItems[0]);
	m_fightLevel.Parry = atoi(saItems[1]);
	m_fightLevel.Swing = atoi(saItems[2]);
	m_fightLevel.Thrust = atoi(saItems[3]);

	m_ninjaLevel.Fight = atoi(saItems[4]);
	m_ninjaLevel.Shoot = atoi(saItems[5]);
	m_ninjaLevel.Steal = atoi(saItems[6]);
	m_ninjaLevel.Throw = atoi(saItems[7]);

	m_priestLevel.Identify = atoi(saItems[8]);
	m_priestLevel.Heal = atoi(saItems[9]);
	m_priestLevel.Influence = atoi(saItems[10]);
	m_priestLevel.Defend = atoi(saItems[11]);

	m_wizardLevel.Fire = atoi(saItems[12]);
	m_wizardLevel.Air = atoi(saItems[13]);
	m_wizardLevel.Earth = atoi(saItems[14]);
	m_wizardLevel.Water = atoi(saItems[15]);
}

void CHeld::nextRuneTable()
{
	if (m_iRuneTable < 4)
		m_iRuneTable++;
	else
		m_iRuneTable = 1;
}

void CHeld::resetRuneTable() {
	m_iRuneTable = 1;
	if (m_spell != NULL) delete m_spell;
	m_spell = new int[5];
}


void CHeld::storeRune(int index) {
	m_spell[m_iRuneTable] = index;
	if (m_iRuneTable == 1) {
		for (int i = 2; i < 5; i++)
			m_spell[i] = 0;
	}
	nextRuneTable();
};

int CHeld::GetPower() {
	if (m_iRuneTable > 1) {
		return m_spell[1];
	}
	else {
		return 0;
	}

}