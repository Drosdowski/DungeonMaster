// Feld.cpp : implementation file
//

#include "stdafx.h"
#include "Feld.h"
#include "SpecialTile\CDoor.h"
#include "Mobs\MobGroups\GrpMonster.h"
#include "Items\Decoration.h"
#include "Items/CMiscellaneous.h"
#include "Items/CFloorOrnate.h"
#include "Items\CActuator.h"
#include "CHelpfulValues.h"
#include <cassert>

/////////////////////////////////////////////////////////////////////////////
// CField

CField::CField()
{
	m_iTyp = EMPTY;
	VEKTOR pos{ 0,0,0 };
	m_lastWeight = 0;
	m_posKoord = pos;
	m_pGrpMonster = NULL;	
	m_pFloorOrnate = NULL;
	InitDeco(NULL);
}

CField::CField(VEKTOR koord, FeldTyp fieldType, CFieldDecoration* pDeco[4])
{
	ASSERT(fieldType != DOOR);
	SetType(fieldType);
	m_lastWeight = 0;
	m_posKoord = koord;
	m_pGrpMonster = NULL;
	m_pFloorOrnate = NULL;
	InitDeco(pDeco);
}

CField::CField(VEKTOR koord, FeldTyp fieldType, CDoor::DoorType doorType, bool eastWest, CFieldDecoration* pDeco[4])
{	
	SetTypeDoor(fieldType, doorType, eastWest);
	m_lastWeight = 0;
	m_posKoord = koord;
	m_pGrpMonster = NULL;
	m_pFloorOrnate = NULL;
	InitDeco(pDeco);
}

CField::CField(VEKTOR koord, FeldTyp fieldType, CStairs::StairType stairType, bool eastWest)
{
	SetTypeStair(fieldType, stairType, eastWest);
	m_lastWeight = 0;
	m_posKoord = koord;
	m_pGrpMonster = NULL;
	m_pFloorOrnate = NULL;
	InitDeco(NULL);
}

CField::CField(VEKTOR koord, FeldTyp fieldType, CPit::PitType pitType, CPit::PitState state)
{
	SetTypePit(fieldType, pitType, state);
	m_lastWeight = 0;
	m_posKoord = koord;
	m_pGrpMonster = NULL;
	m_pFloorOrnate = NULL;
	InitDeco(NULL);
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
	for (int i = 0; i < 4; i++) {
		if (m_pWallDecoration[i]) {
			delete m_pWallDecoration[i];
		}
		while (!m_pMiscellaneous[i].empty()) {
			CMiscellaneous* item = m_pMiscellaneous[i].top();
			delete item;
			m_pMiscellaneous[i].pop();
		}
		while (!m_pActuator[i].empty()) {
			CActuator* actuator = m_pActuator[i].top();
			delete actuator;
			m_pActuator[i].pop();
		}
	}
	if (m_pFloorOrnate)
		delete m_pFloorOrnate;
}

void CField::InitDeco(CFieldDecoration* pDeco[4]) {
	for (int i = 0; i < 4; i++) {
		if (pDeco != NULL)
		{
			m_pWallDecoration[i] = pDeco[i];
		}
		else {
			m_pWallDecoration[i] = new CFieldDecoration(None);
		}
	}
}


void CField::InitMonsterGruppe(CMonster::MonsterTyp iTyp, int iAnz, int richt)
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


void CField::SetTypeDoor(FeldTyp fieldType, CDoor::DoorType doorType, bool doorFrameEastAndWest) {
	m_iTyp = fieldType;
	if (fieldType == DOOR) {
		m_pDoor = new CDoor(doorType, doorFrameEastAndWest);
	} else {
		assert(false);
	}
}

void CField::SetTypeStair(FeldTyp fieldType, CStairs::StairType stairsType, bool eastWest) {
	m_iTyp = fieldType;
	if (fieldType == STAIRS) {
		m_pStairs = new CStairs(stairsType, eastWest);
	}
	else {
		assert(false);
	}
}

void CField::SetTypePit(FeldTyp fieldType, CPit::PitType pitType, CPit::PitState state) {
	m_iTyp = fieldType;
	if (fieldType == PIT) {
		m_pPit = new CPit(pitType, state);
	}
	else {
		assert(false);
	}
}

void CField::ThrowMisc(CMiscellaneous* misc, SUBPOS_ABSOLUTE index, VEKTOR force) {
	misc->m_flyForce = force;
	m_pMiscellaneous[index].push(misc);
}

void CField::PutMisc(CMiscellaneous* misc, SUBPOS_ABSOLUTE index) {
	m_pMiscellaneous[index].push(misc);
}

void CField::PutFloorDeco(CFloorOrnate* deco) {
	m_pFloorOrnate = deco;
}

void CField::PutActuator(CActuator* actuator, SUBPOS_ABSOLUTE index) {
	m_pActuator[index].push(actuator);
}

// Item von Stapel nehmen - ist dann "in der Hand"
CMiscellaneous* CField::TakeMisc(SUBPOS_ABSOLUTE subPos) {
	if (m_pMiscellaneous[subPos].size() > 0)
	{
		CMiscellaneous* topItem = m_pMiscellaneous[subPos].top();
		m_pMiscellaneous[subPos].pop();

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
