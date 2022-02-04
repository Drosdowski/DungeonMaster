// Feld.cpp : implementation file
//

#include "stdafx.h"
#include "Feld.h"
#include "SpecialTile\Decoration.h"
#include "SpecialTile\CDoor.h"
#include "Mobs\MobGroups\GrpMonster.h"
#include <cassert>

/////////////////////////////////////////////////////////////////////////////
// CField

CField::CField()
{
	m_iTyp = EMPTY;
	VEKTOR pos; pos.x = 0; pos.y = 0; pos.z = 0;
	m_posKoord = pos;
	m_pGrpMonster = NULL;
	for (int i = 0; i < 4; i++) {
		m_pWallDecoration[i] = NULL;
	}
}

CField::CField(VEKTOR koord, FeldTyp fieldType, CFieldDecoration* pDeco[4])
{
	ASSERT(fieldType != DOOR);
	SetType(fieldType);
	m_posKoord = koord;
	m_pGrpMonster = NULL;
	for (int i = 0; i < 4; i++) {
		m_pWallDecoration[i] = pDeco[i];
	}
}

CField::CField(VEKTOR koord, FeldTyp fieldType, CDoor::DoorType doorType, bool doorDirectionEastWest, CFieldDecoration* pDeco[4])
{	
	SetType(fieldType, doorType, doorDirectionEastWest);
	m_posKoord = koord;
	m_pGrpMonster = NULL;
	for (int i = 0; i < 4; i++) {
		m_pWallDecoration[i] = pDeco[i];
	}
}

CField::CField(VEKTOR koord, FeldTyp fieldType, CStairs::StairType stairType, bool eastWest, CFieldDecoration* pDeco[4])
{
	SetType(fieldType, stairType, eastWest);
	m_posKoord = koord;
	m_pGrpMonster = NULL;
	for (int i = 0; i < 4; i++) {
		m_pWallDecoration[i] = pDeco[i];
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
	for (int i = 0; i < 4; i++) {
		if (m_pWallDecoration[i]) {
			delete m_pWallDecoration[i];
		}
	}

}


void CField::InitMonsterGruppe(CMonster::MonsterTyp iTyp, int iAnz)
{
	if (m_pGrpMonster)
		AfxMessageBox("Fehler: Versuch, zwei Monstergruppen auf gleichem Feld zu initialisiern");
	m_pGrpMonster = new CGrpMonster(m_posKoord);
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