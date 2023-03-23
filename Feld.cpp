// Feld.cpp : implementation file
//

#include "stdafx.h"
#include "Feld.h"
#include "SpecialTile\CDoor.h"
#include "SpecialTile\CTeleporter.h"
#include "SpecialTile\TrickWall.h"
#include "Mobs\MobGroups\GrpMonster.h"
#include "Items\FloorDecoration.h"
#include "Items\WallDecoration.h"
#include "Items/Item.h"
#include "Items\CActuator.h"
#include "Items\Weapon.h"
#include "Items\CMiscellaneous.h"
#include "Items\Potion.h"
#include "Items\Container.h"
#include "Items\Cloth.h"
#include "Items\CActuator.h"
#include "CalculationHelper\CHelpfulValues.h"
#include <cassert>

/////////////////////////////////////////////////////////////////////////////
// CField

CField::CField()
{
	InitVars();
	m_iTyp = EMPTY;
	VEKTOR pos{ 0,0,0 };
	m_posKoord = pos;
}

CField::CField(VEKTOR koord, FeldTyp fieldType)
{
	InitVars();
	SetType(fieldType);
	m_posKoord = koord;
}

CField::CField(VEKTOR koord, CDoor* pDoor)
{	
	InitVars();
	SetTypeDoor(pDoor);
	m_posKoord = koord;
}

CField::CField(VEKTOR koord, CStairs* pStair)
{
	InitVars();
	SetTypeStair(pStair);
	m_posKoord = koord;
}

CField::CField(VEKTOR koord, CPit* pPit)
{
	InitVars();
	SetTypePit(pPit);
	m_posKoord = koord;
}

CField::CField(VEKTOR koord, CTeleporter* teleItem) {
	InitVars();
	SetTypeTeleporter(teleItem);
	m_posKoord = koord;
}

CField::CField(VEKTOR koord, CTrickWall* trickwall) {
	InitVars();
	SetTypeTrickwall(trickwall);
	m_posKoord = koord;
}

void CField::InitVars() {
	m_lastWeight = 0;
	m_pGrpMonster = NULL;
	m_floorOrnateType = NULL;
	for (int p = 0; p < 4; p++) {
		m_wallOrnateType[p] = NULL;
	}
}


CField::~CField()
{
	if (m_pGrpMonster)
		delete m_pGrpMonster;
	if (m_pDoor)
		delete m_pDoor;
	if (m_pStairs)
		delete m_pStairs;
	if (m_pPit)
		delete m_pPit;
	if (m_pTeleporter)
		delete m_pTeleporter;
	if (m_pTrickwall)
		delete m_pTrickwall;
	if (m_floorOrnateType)
		delete m_floorOrnateType;
	for (int p = 0; p < 4; p++) {
		if (m_wallOrnateType[p])
			delete m_wallOrnateType[p];
	}

	for (int i = 0; i < 4; i++) {
		for (CItem* item : m_pItem[i]) {
			if (item->getItemType() == CItem::ItemType::WeaponItem)
				delete (CWeapon*)item;
			else if (item->getItemType() == CItem::ItemType::MiscItem)
				delete (CMiscellaneous*)item;
			else if (item->getItemType() == CItem::ItemType::ClothItem)
				delete (CCloth*)item;
			else if (item->getItemType() == CItem::ItemType::PotionItem)
				delete (CPotion*)item;
			else if (item->getItemType() == CItem::ItemType::ScrollItem)
				delete (CScroll*)item;
			else
				delete item;
		}
		for (CMagicMissile* missile : m_pMagicMissiles[i]) {
			if (missile)
				delete missile;
		}
		for (CActuator* actuator : m_pActuator[i]) {
			delete actuator;
		}
	}
}

CGrpMonster* CField::GetMonsterGroup() {
	return m_pGrpMonster;
}

void CField::RemoveMonsterGroup() {
	delete m_pGrpMonster;
	m_pGrpMonster = NULL;
}

bool CField::BlockedToWalk() {
	if (m_iTyp == WALL) return true;
	if (m_iTyp == DOOR) {
		CDoor* door = HoleDoor();
		if (door && door->getState() == CDoor::DoorState::CLOSED) return true;
	}
	return false;
}

bool CField::BlockedToPut() {
	if (m_iTyp == WALL) return true;
	return false;
}


void CField::SetMonsterGroup(CGrpMonster* pGrpMonster) {
	m_pGrpMonster = pGrpMonster;
}

void CField::SetType(FeldTyp fieldType) {
	m_iTyp = fieldType;
}

void CField::SetTypeDoor(CDoor* pDoor) {
	m_iTyp = DOOR;
	m_pDoor = pDoor;
}

void CField::SetTypeStair(CStairs* pStair) {
	m_iTyp = STAIRS;
	m_pStairs = pStair;
}

void CField::SetTypePit(CPit* pPit) {
	m_iTyp = PIT;
	m_pPit = pPit;
}

void CField::SetTypeTeleporter(CTeleporter* teleItem) {
	m_iTyp = TELEPORT;
	m_pTeleporter = teleItem;
}

void CField::SetTypeTrickwall(CTrickWall* trickwall) {
	m_iTyp = TRICKWALL;
	m_pTrickwall = trickwall;
}


void CField::ThrowItem(CItem* item, SUBPOS_ABSOLUTE index, VEKTOR force) {
	item->m_flyForce = force;
	m_pItem[index].push_back(item);
}

void CField::CastMissile(CMagicMissile* missile, SUBPOS_ABSOLUTE index) {
	m_pMagicMissiles[index].push_back(missile);
}

void CField::PutItem(CItem* item, SUBPOS_ABSOLUTE index) {
	m_pItem[index].push_back(item);
}

void CField::PutWeapon(CWeapon* weapon, SUBPOS_ABSOLUTE index) {
	m_pItem[index].push_back((CItem*)weapon);
}

void CField::PutCloth(CCloth* cloth, SUBPOS_ABSOLUTE index) {
	m_pItem[index].push_back((CItem*)cloth);
}

void CField::PutMisc(CMiscellaneous* misc, SUBPOS_ABSOLUTE index) {
	m_pItem[index].push_back((CItem*)misc);
}

void CField::PutPotion(CPotion* potion, SUBPOS_ABSOLUTE index) {
	m_pItem[index].push_back((CItem*)potion);
}

void CField::PutScroll(CScroll* scroll, SUBPOS_ABSOLUTE index) {
	m_pItem[index].push_back((CItem*)scroll);
}

void CField::PutContainer(CContainer* container, SUBPOS_ABSOLUTE index) {
	m_pItem[index].push_back((CItem*)container);
}

void CField::PutFloorDeco(CFloorDecoration* deco) {
	m_floorOrnateType = deco;
}

void CField::PutWallDeco(CWallDecoration* deco, int position) {
	m_wallOrnateType[position] = deco;
}

void CField::PutActuator(CActuator* actuator, COMPASS_DIRECTION index) {
	m_pActuator[index].push_back(actuator);
}

// Item von Stapel nehmen - ist dann "in der Hand"
CItem* CField::TakeItem(SUBPOS_ABSOLUTE subPos) {	
	if (m_pItem[subPos].size() > 0)
	{
		CItem* topItem = m_pItem[subPos].back();
		m_pItem[subPos].pop_back();

		return topItem;
	}
	else
		return NULL;
}

CMagicMissile* CField::TakeMissile(SUBPOS_ABSOLUTE subPos, CMagicMissile* pMissile) {
	if (m_pMagicMissiles[subPos].size() > 0)
	{
		for (std::deque<CMagicMissile*>::iterator it = m_pMagicMissiles[subPos].begin(); it != m_pMagicMissiles[subPos].end(); ) {
			if (*it == pMissile) {
				m_pMagicMissiles[subPos].erase(it);
				return pMissile;
			}
			++it;

		}

		return NULL;
	}
	else
		return NULL;
}

int CField::GetWeight(VEKTOR heroPos) {
	int weight = 0;
	if (GetMonsterGroup() != NULL) weight = 100; // max
	if (m_posKoord.x == heroPos.x && m_posKoord.y == heroPos.y && m_posKoord.z == heroPos.z) weight = 100; // max
	for (int i = 0; i < 4; i++) {
		for (CItem* item : m_pItem[i]) {
			weight += item->GetWeight(); 
		}
	}

	return weight;
}

void CField::StoreCurrentWeight(VEKTOR heroPos) {
	int currentWeight = GetWeight(heroPos);
	m_lastWeight = currentWeight; // direkt speichern, darf nur 1x triggern
}

bool CField::CriticalWeightBreached(VEKTOR heroPos, int criticalWeight) {
	int currentWeight = GetWeight(heroPos);

	if (m_lastWeight < criticalWeight && currentWeight >= criticalWeight) return true;
	return false;
}

bool CField::CriticalWeightGone(VEKTOR heroPos, int criticalWeight) {
	int currentWeight = GetWeight(heroPos);

	if (m_lastWeight >= criticalWeight && currentWeight < criticalWeight) return true;
	return false;
}

void CField::RotateActuators(COMPASS_DIRECTION position) {
	CActuator* actuator = m_pActuator[position].back();
	m_pActuator[position].pop_back();
	m_pActuator[position].push_front(actuator);
}
