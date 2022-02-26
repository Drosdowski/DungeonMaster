// Feld.cpp : implementation file
//

#include "stdafx.h"
#include "Feld.h"
#include "SpecialTile\Decoration.h"
#include "SpecialTile\CDoor.h"
#include "Mobs\MobGroups\GrpMonster.h"
#include "Items/CMiscellaneous.h"
#include "CHelpfulValues.h"
#include <cassert>

/////////////////////////////////////////////////////////////////////////////
// CField

CField::CField()
{
	m_iTyp = EMPTY;
	VEKTOR pos{ 0,0,0 };
	m_posKoord = pos;
	m_pGrpMonster = NULL;
	InitDeco(NULL);
}

CField::CField(VEKTOR koord, FeldTyp fieldType, CFieldDecoration* pDeco[4])
{
	ASSERT(fieldType != DOOR);
	SetType(fieldType);
	m_posKoord = koord;
	m_pGrpMonster = NULL;
	InitDeco(pDeco);
}

CField::CField(VEKTOR koord, FeldTyp fieldType, CDoor::DoorType doorType, bool doorDirectionEastWest, CFieldDecoration* pDeco[4])
{	
	SetType(fieldType, doorType, doorDirectionEastWest);
	m_posKoord = koord;
	m_pGrpMonster = NULL;
	InitDeco(pDeco);
}

CField::CField(VEKTOR koord, FeldTyp fieldType, CStairs::StairType stairType, bool eastWest, CFieldDecoration* pDeco[4])
{
	SetType(fieldType, stairType, eastWest);
	m_posKoord = koord;
	m_pGrpMonster = NULL;
	InitDeco(pDeco);
}

CField::~CField()
{
	if (m_pGrpMonster)
		delete m_pGrpMonster;
	if (m_pDoor)
		delete m_pDoor;
	if (m_pStairs)
		delete m_pStairs;
	for (int i = 0; i < 4; i++) {
		if (m_pWallDecoration[i]) {
			delete m_pWallDecoration[i];
		}
	}
	for (int i = 0; i < 4; i++) {
		while (!m_pMiscellaneous[i].empty()) {
			CMiscellaneous* item = m_pMiscellaneous[i].top();
			delete item;
			m_pMiscellaneous[i].pop();
		}
	}
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


void CField::SetType(FeldTyp fieldType, CDoor::DoorType doorType, bool doorFrameEastAndWest) {
	m_iTyp = fieldType;
	if (fieldType == DOOR) {
		m_pDoor = new CDoor(doorType, doorFrameEastAndWest);
	} else {
		assert(false);
	}
}

void CField::SetType(FeldTyp fieldType, CStairs::StairType stairsType, bool eastWest) {
	m_iTyp = fieldType;
	if (fieldType == STAIRS) {
		m_pStairs = new CStairs(stairsType, eastWest);
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
