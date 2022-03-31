// Feld.cpp : implementation file
//

#include "stdafx.h"
#include "Feld.h"
#include "SpecialTile\CDoor.h"
#include "SpecialTile\CTeleporter.h"
#include "Mobs\MobGroups\GrpMonster.h"
#include "Items\Decoration.h"
#include "Items/CMiscellaneous.h"
#include "Items\CActuator.h"
#include "CHelpfulValues.h"
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

void CField::InitVars() {
	m_lastWeight = 0;
	m_pGrpMonster = NULL;
	m_floorOrnateType = NULL;
	/*for (int p = 0; p < 4; p++) {
		m_pWallDecoration[p] = NULL;
	}*/
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
	if (m_floorOrnateType)
		delete m_floorOrnateType;
	for (int i = 0; i < 4; i++) {
		for (CMiscellaneous* item : m_pMiscellaneous[i]) {
			delete item;
		}
		for (CActuator* actuator : m_pActuator[i]) {
			delete actuator;
		}
	}
}


void CField::InitMonsterGruppe(CMonster::MonsterTyp iTyp, int iAnz, COMPASS_DIRECTION richt)
{
	if (m_pGrpMonster)
		AfxMessageBox("Fehler: Versuch, zwei Monstergruppen auf gleichem Feld zu initialisiern");
	m_pGrpMonster = new CGrpMonster(m_posKoord, richt);
	for (int i=1; i<= iAnz; i++)
		((CGrpMonster*)m_pGrpMonster)->InitMonster(i, iTyp);
}

CGrpMonster* CField::GetMonsterGroup() {
	return m_pGrpMonster;
}

void CField::RemoveMonsterGroup() {
	delete m_pGrpMonster;
	m_pGrpMonster = NULL;
}

bool CField::Blocked() {
	if (m_iTyp == WALL) return true;
	if (m_iTyp == DOOR) {
		CDoor* door = HoleDoor();
		if (door && door->getState() == CDoor::DoorState::CLOSED) return true;
	}
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


void CField::ThrowMisc(CMiscellaneous* misc, SUBPOS_ABSOLUTE index, VEKTOR force) {
	misc->m_flyForce = force;
	m_pMiscellaneous[index].push_back(misc);
}

void CField::PutMisc(CMiscellaneous* misc, SUBPOS_ABSOLUTE index) {
	m_pMiscellaneous[index].push_back(misc);
}

void CField::PutFloorDeco(CFieldDecoration* deco) {
	m_floorOrnateType = deco;
}

void CField::PutActuator(CActuator* actuator, COMPASS_DIRECTION index) {
	m_pActuator[index].push_back(actuator);
}

// Item von Stapel nehmen - ist dann "in der Hand"
CMiscellaneous* CField::TakeMisc(SUBPOS_ABSOLUTE subPos) {	
	if (m_pMiscellaneous[subPos].size() > 0)
	{
		CMiscellaneous* topItem = m_pMiscellaneous[subPos].back();
		m_pMiscellaneous[subPos].pop_back();

		return topItem;
	}
	else
		return NULL;
}

int CField::GetWeight(VEKTOR heroPos) {
	int weight = 0;
	if (GetMonsterGroup() != NULL) weight = 100; // max
	if (m_posKoord.x == heroPos.x && m_posKoord.y == heroPos.y && m_posKoord.z == heroPos.z) weight = 100; // max
	for (int i = 0; i < 4; i++) {
		weight += m_pMiscellaneous[i].size(); // todo bessere Lösung als Anzahl Items als Gewicht zu nehmen
	}

	return weight;
}

bool CField::CriticalWeightChange(VEKTOR heroPos, int criticalWeight) {
	int currentWeight = GetWeight(heroPos);
	int lastWeight = m_lastWeight;

	m_lastWeight = currentWeight; // direkt speichern, darf nur 1x triggern

	if (lastWeight < criticalWeight && currentWeight >= criticalWeight) return true;
	if (lastWeight >= criticalWeight && currentWeight < criticalWeight) return true;
	return false;
}

void CField::RotateActuators(COMPASS_DIRECTION position) {
	CActuator* actuator = m_pActuator[position].back();
	m_pActuator[position].pop_back();
	m_pActuator[position].push_front(actuator);
}
