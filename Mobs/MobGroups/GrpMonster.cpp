// GrpMonster.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "GrpMonster.h"
#include "..\Skelett.h"
#include "..\Mumie.h"
#include "..\MobGroups\GrpHeld.h"
#include "..\..\CalculationHelper\CHelpfulValues.h"
#include "..\..\Items\CMiscellaneous.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGrpMonster

CGrpMonster::CGrpMonster()
{
}

CGrpMonster::CGrpMonster(VEKTOR pos, COMPASS_DIRECTION richt)
{
	for (int i=1; i<=4; i++)
		m_pMember[i] = NULL;
	m_posPosition = pos;
	m_grpDirection = richt;
	carriedItem = NULL;
}

CGrpMonster::CGrpMonster(VEKTOR pos, CCreatureAttributes attributes) {
	for (int i = 1; i <= 4; i++)
		m_pMember[i] = NULL;
	
	for (int i = 1; i <= attributes.count; i++)
	{
		if (i <= attributes.count) {
			InitMonster(i, attributes);
		}
	}
	m_posPosition = pos;
	m_grpDirection = attributes.direction;
	carriedItem = NULL;
}


CGrpMonster::~CGrpMonster()
{
	if (carriedItem)
		delete carriedItem;
}

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CGrpMonster 

void CGrpMonster::InitMonster(int nr, CCreatureAttributes attributes)
{
	if (m_pMember[nr] == NULL)
	{
		int hp = attributes.hitPoints[nr - 1];
		switch (attributes.type)
		{
		case CMonster::MonsterTyp::SKELETT:
			m_pMember[nr] = new CSkelett(hp);
			break;
		case CMonster::MonsterTyp::MUMIE:
			m_pMember[nr] = new CMumie(hp);
			break;
		default:
			return; // todo other monster types!
		} 
		
		m_grpDirection = COMPASS_DIRECTION::NORTH;
		SetNewCharOnNextFreePos(nr);

		m_pMember[nr]->SetDirection(m_grpDirection);
	}
}

bool CGrpMonster::SetzeModus(int iModus)
{
	// Modus könnte sein: angst/fliehen, frozen, taub/ruhend, angreifend
	return true;
}

bool CGrpMonster::Altern()
{
	bool anyoneAlive = false;
	for (int i=1; i<5; i++)
	{
		CMonster* pMonster= (CMonster*) m_pMember[i];
		if (pMonster) {
			bool monsterAlive = pMonster->Altern();
			if (!monsterAlive)
			{
				delete m_pMember[i]; // TODO auslöschen! todo: staubwolke malen!
				m_pMember[i] = NULL;
			}
			else {
				anyoneAlive = true;
			}
		}
	}
	return anyoneAlive;
}


void CGrpMonster::EndAttack() {
	for (int i = 1; i < 5; i++)
	{
		CMonster* pMonster = (CMonster*)m_pMember[i];
		if (pMonster) {
			pMonster->EndAttack();
		}
	}
}

CMonster* CGrpMonster::AttackHero(VEKTOR myPos, VEKTOR hisPos) {
	for (int i = 1; i < 5; i++)
	{
		CMonster* pMonster = (CMonster*)m_pMember[i];
		if (pMonster && pMonster->IstBereit()) {	
			if (pMonster->InFrontOfOpponent(myPos, hisPos, emptyNorthRow(), emptyEastRow(), emptySouthRow(), emptyWestRow())) {
				if (pMonster->GetDirection() == m_grpDirection)
				{
					int dmg = pMonster->CalcDmg(1); // todo monster attacke random
					pMonster->AttackModeWithDmg(dmg);
					pMonster->ActionDone();
					return pMonster; // pro Tick nur ein Angriff / Gruppe
				}
				else {
					pMonster->SetDirection(m_grpDirection); // Einzeldrehung zur Attacke
				}
			}
			else {
				TryToAdavanceToFirstRow(i, myPos, hisPos);
			}			
		}
	}

	return NULL;
}

bool CGrpMonster::isSubPosAbsoluteFree(SUBPOS_ABSOLUTE pos) {
	for (int i = 1; i < 5; i++)
	{
		CMonster* pMonster = (CMonster*)m_pMember[i];
		if (pMonster && pMonster->HoleSubPosition() == pos) {
			return false;
		}
	}
	return true;
}

void CGrpMonster::TryToAdavanceToFirstRow(int index, VEKTOR myPos, VEKTOR hisPos) {
	CCharacter* monster = m_pMember[index];
	if (monster) {
		switch (monster->HoleSubPosition())
		{
		case NORTHWEST:
			if (monster->northOf(myPos, hisPos) && isSubPosAbsoluteFree(SOUTHWEST))
				monster->SetzeSubPosition(SOUTHWEST);

			if (monster->westOf(myPos, hisPos) && isSubPosAbsoluteFree(NORTHEAST))
				monster->SetzeSubPosition(NORTHEAST);

		case NORTHEAST:
			if (monster->northOf(myPos, hisPos) && isSubPosAbsoluteFree(SOUTHWEST))
				monster->SetzeSubPosition(SOUTHWEST);

			if (monster->eastOf(myPos, hisPos) && isSubPosAbsoluteFree(NORTHWEST))
				monster->SetzeSubPosition(NORTHWEST);

		case SOUTHWEST:
			if (monster->southOf(myPos, hisPos) && isSubPosAbsoluteFree(NORTHWEST))
				monster->SetzeSubPosition(NORTHWEST);

			if (monster->westOf(myPos, hisPos) && isSubPosAbsoluteFree(SOUTHEAST))
				monster->SetzeSubPosition(SOUTHEAST);

		case SOUTHEAST:
			if (monster->southOf(myPos, hisPos) && isSubPosAbsoluteFree(NORTHEAST))
				monster->SetzeSubPosition(NORTHEAST);

			if (monster->eastOf(myPos, hisPos) && isSubPosAbsoluteFree(SOUTHWEST))
				monster->SetzeSubPosition(SOUTHWEST);

		}
	}

}

CMonster* CGrpMonster::GetBySubpos(SUBPOS pos) {
	for (int i = 1; i < 5; i++)
	{
		CMonster* pMonster = (CMonster*)m_pMember[i];
		if (pMonster && pMonster->HoleSubPosition() == pos)
			return pMonster;
	}
	return NULL;
}

bool CGrpMonster::AnyoneReady() {
	for (int i = 1; i < 5; i++)
	{
		CMonster* pMonster = (CMonster*)m_pMember[i];
		if (pMonster) {
			if (pMonster->IstBereit())
				return true;
		}
	}
	return false;
}

bool CGrpMonster::EveryoneReady() {
	for (int i = 1; i < 5; i++)
	{
		CMonster* pMonster = (CMonster*)m_pMember[i];
		if (pMonster) {
			if (!pMonster->IstBereit())
				return false;
		}
	}
	return true;
}

void CGrpMonster::ActionDone() {
	// todo : attacke ist nur für 1 Monster action!
	for (int i = 1; i < 5; i++)
	{
		CMonster* pMonster = (CMonster*)m_pMember[i];
		if (pMonster) {
			pMonster->ActionDone();
		}
	}
}

CMonster* CGrpMonster::GetMonster(int ID) {
	return (CMonster*)m_pMember[ID];
}

CMonster* CGrpMonster::GetMonsterByRelSubPos(SUBPOS pos, COMPASS_DIRECTION richt) {
	for (int i = 1; i < 5; i++)
	{
		CMonster* pMonster = (CMonster*)m_pMember[i];
		if (pMonster) {
			if (CHelpfulValues::GetRelativeSubPosPassive(pMonster->HoleSubPosition(), richt) == pos) // todo welche RICHT? monster oder hero ???
				return pMonster;
		}
	}
	return NULL; 
}

//   0
//   |
// 1- -3
//   |
//   2
void CGrpMonster::TurnToHero(VEKTOR heroPos) {
	VEKTOR monPos = GetVector();
	COMPASS_DIRECTION monDir = m_grpDirection;

	COMPASS_DIRECTION newDirection;
	if (heroPos.x < monPos.x) {
		newDirection = COMPASS_DIRECTION::WEST;
	}
	else if (heroPos.x > monPos.x) {
		newDirection = COMPASS_DIRECTION::EAST;
	}
	else if (heroPos.y < monPos.y) {
		newDirection = COMPASS_DIRECTION::NORTH;
	}
	else {
		newDirection = COMPASS_DIRECTION::SOUTH;
	}

	for (int i = 1; i < 5; i++)
	{
		CMonster* pMonster = (CMonster*)m_pMember[i];
		if (pMonster) {
			if (pMonster->TurnTo(newDirection))
				m_grpDirection = newDirection;
			pMonster->EndAttack();
		}
	}
	
}

void CGrpMonster::Laufen(VEKTOR WunschPos) {
	for (int i = 1; i <= 4; i++)
		if ((m_pMember[i]) && (m_pMember[i]->Hp().Aktuell > 0))
		{
			m_pMember[i]->ActionDone();
		}
	m_posPosition = WunschPos;
}

void CGrpMonster::CarryItem(CMiscellaneous* item, SUBPOS_ABSOLUTE pos) {
	carriedItem = item;
	carriedItemPos = pos;
}
