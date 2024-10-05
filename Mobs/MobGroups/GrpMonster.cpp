// GrpMonster.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "GrpMonster.h"
#include "..\..\Feld.h"
#include "..\Monster.h"
#include "..\..\CalculationHelper\CHelpfulValues.h"
#include "..\..\XMLParser\MonsterInfos.h"
#include "..\..\Items\CMiscellaneous.h"
#include "..\..\Items\Weapon.h"
#include "..\..\Items\Potion.h"
#include "..\..\Items\Cloth.h"
#include "..\..\Items\MagicMissile.h"
#include <cassert>

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

CGrpMonster::CGrpMonster(VEKTOR pos, CCreatureAttributes attributes, int index) {
	for (int i = 1; i <= 4; i++)
		m_pMember[i] = NULL;
	
	for (int i = 1; i <= attributes.count; i++)
	{
		InitMonster(i, attributes);
	}
	m_posPosition = pos;
	m_index = index;
	m_iScaredCounter = 0;
	DrehenAbsolut(attributes.direction);
	carriedItems = {};
}


CGrpMonster::~CGrpMonster()
{
	for (CItem* carriedItem : carriedItems)
	{
		if (carriedItem->getItemType() == CItem::WeaponItem)
			delete (CWeapon*)carriedItem;
		else if (carriedItem->getItemType() == CItem::MiscItem)
			delete (CMiscellaneous*)carriedItem;
		else  if (carriedItem->getItemType() == CItem::ClothItem)
			delete (CCloth*)carriedItem;
		else  if (carriedItem->getItemType() == CItem::PotionItem)
			delete (CPotion*)carriedItem;
	}
}

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CGrpMonster 

void CGrpMonster::InitMonster(int nr, CCreatureAttributes attributes)
{
	if (m_pMember[nr] == NULL)
	{
		m_pMember[nr] = new CMonster(attributes, nr - 1);
				
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

void CGrpMonster::Scare() {
	m_iScaredCounter += 8;
}

void CGrpMonster::InstantKill() {
	for (int i = 1; i < 5; i++)
	{
		CMonster* pMonster = (CMonster*)m_pMember[i];
		if (pMonster && pMonster->isAlive()) {
			pMonster->AddDmg((int)(pMonster->Hp().Aktuell));
		}
	}
}

bool CGrpMonster::Altern(CField* field)
{
	bool didHurt = false;
	for (int i=1; i<5; i++)
	{
		CMonster* pMonster= (CMonster*) m_pMember[i];
		if (pMonster) {
			didHurt = didHurt || pMonster->Altern();
			if (!pMonster->isAlive())
			{
				CMagicMissile* dust = new CMagicMissile(CMagicMissile::MagicMissileType::Dust, pMonster->GetSize(), field->HolePos());
				dust->Explode();

				m_lastPosition = pMonster->HoleSubPosition();
				field->CastMissile(dust, m_lastPosition);
				delete m_pMember[i];
				m_pMember[i] = NULL;
			}
		}
	}
	return didHurt;
}


CMonster* CGrpMonster::AttackHero(int monIndex, VEKTOR monsterPos, VEKTOR heroPos) {
	CMonster* pMonster = (CMonster*)m_pMember[monIndex];
	if (pMonster && pMonster->ReadyToAttack() == 0) {				
		CMonsterConst mc = pMonster->getInfo();

		if (mc.attack_anyone || pMonster->InFrontOfOpponent(monsterPos, heroPos, emptyNorthRow(), emptyEastRow(), emptySouthRow(), emptyWestRow())) {
			int dmg = pMonster->CalcDmg(1); // todo monster attacke random
			int poison = mc.poison;
			pMonster->AttackModeWithDmg(dmg, poison);
			pMonster->AttackOrMoveDone();
			return pMonster; // pro Tick nur ein Angriff / Gruppe
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

int CGrpMonster::Count() {
	int count = 0;
	for (int i = 1; i < 5; i++)
	{
		CMonster* pMonster = (CMonster*)m_pMember[i];
		if (pMonster && pMonster->isAlive()) {
			count ++;
		}
	}
	return count;
}

void CGrpMonster::TryToAdvanceToFirstRow(VEKTOR myPos) {
	for (int i = 1; i < 5; i++)
	{
		CMonster* pMonster = (CMonster*)m_pMember[i];
		if (pMonster && pMonster->isAlive() && pMonster->ReadyToMove() == 0) {
			TryToAdvanceToFirstRow(i, m_posPosition, myPos);
		}
	}

}

bool CGrpMonster::TrySetToSubPos(CMonster* monster, SUBPOS_ABSOLUTE subPos) {
	if (isSubPosAbsoluteFree(subPos)) {
		monster->SetzeSubPosition(subPos);
		monster->AttackOrMoveDone();
		return true;
	}
	return false;
}

void CGrpMonster::TryToAdvanceToFirstRow(int index, VEKTOR monPos, VEKTOR heroPos) {
	CMonster* monster = (CMonster*)m_pMember[index];
	if (Count() > 1)
	{
		if (monster) {
			switch (monster->HoleSubPosition())
			{
			case NORTHWEST:
				if (CHelpfulValues::southOf(monPos, heroPos))
				{
					if (!TrySetToSubPos(monster, SOUTHWEST)) {
						TrySetToSubPos(monster, SOUTHEAST);
					}
				}
				if (CHelpfulValues::eastOf(monPos, heroPos)) {
					if (!TrySetToSubPos(monster, NORTHEAST)) {
						TrySetToSubPos(monster, SOUTHEAST);
					}
				}
				break;
			case NORTHEAST:
				if (CHelpfulValues::southOf(monPos, heroPos))
				{
					if (!TrySetToSubPos(monster, SOUTHWEST)) {
						TrySetToSubPos(monster, SOUTHEAST);
					}
				}
				if (CHelpfulValues::westOf(monPos, heroPos))
				{
					if (!TrySetToSubPos(monster, NORTHWEST)) {
						TrySetToSubPos(monster, SOUTHWEST);
					}
				}
				break;
			case SOUTHWEST:
				if (CHelpfulValues::northOf(monPos, heroPos)) {
					if (!TrySetToSubPos(monster, NORTHWEST)) {
						TrySetToSubPos(monster, NORTHEAST);
					}
				}
				if (CHelpfulValues::eastOf(monPos, heroPos) ) {
					if (!TrySetToSubPos(monster, SOUTHEAST)) {
						TrySetToSubPos(monster, NORTHEAST);
					}
				}
				break;
			case SOUTHEAST:
				if (CHelpfulValues::northOf(monPos, heroPos) && isSubPosAbsoluteFree(NORTHEAST)) {
					if (!TrySetToSubPos(monster, NORTHEAST)) {
						TrySetToSubPos(monster, NORTHWEST);
					}
				}
				if (CHelpfulValues::westOf(monPos, heroPos) && isSubPosAbsoluteFree(SOUTHWEST))
				{
					if (!TrySetToSubPos(monster, SOUTHWEST)) {
						TrySetToSubPos(monster, NORTHWEST);
					}
				}
				break;
			}
		}
	}
	else {
		monster->SetzeSubPosition(MIDDLE);
	}

}

int CGrpMonster::MonsterIndexReadyToAttack() {
	for (int i = 1; i < 5; i++)
	{
		CMonster* pMonster = (CMonster*)m_pMember[i];
		if (pMonster) {
			if (pMonster->ReadyToAttack() == 0)
				return i;
		}
	}
	return -1;
}

bool CGrpMonster::AnyoneReadyToMove() {
	for (int i = 1; i < 5; i++)
	{
		CMonster* pMonster = (CMonster*)m_pMember[i];
		if (pMonster) {
			if (pMonster->ReadyToMove() == 0)
				return true;
		}
	}
	return false;
}

bool CGrpMonster::EveryoneReadyToAttack() {
	for (int i = 1; i < 5; i++)
	{
		CMonster* pMonster = (CMonster*)m_pMember[i];
		if (pMonster) {
			if (pMonster->ReadyToAttack() > 0)
				return false;
		}
	}
	return true;
}

bool CGrpMonster::EveryoneReadyToMove() {
	for (int i = 1; i < 5; i++)
	{
		CMonster* pMonster = (CMonster*)m_pMember[i];
		if (pMonster) {
			if (pMonster->ReadyToMove() > 0)
				return false;
		}
	}
	return true;
}


bool CGrpMonster:: isAlive() {
	for (int i = 1; i < 5; i++)
	{
		CMonster* pMonster = (CMonster*)m_pMember[i];
		if (pMonster) {
			if (pMonster->isAlive())
				return true;
		}
	}
	return false;
}

void CGrpMonster::AttackOrMoveDone() {
	for (int i = 1; i < 5; i++)
	{
		CMonster* pMonster = (CMonster*)m_pMember[i];
		if (pMonster) {
			pMonster->AttackOrMoveDone();
		}
	}
}

void CGrpMonster::ReduceScaredCounter() {
	if (m_iScaredCounter > 0) {
		m_iScaredCounter--;
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

CMonster* CGrpMonster::GetMonsterByAbsSubPos(SUBPOS_ABSOLUTE pos) {
	for (int i = 1; i < 5; i++)
	{
		CMonster* pMonster = (CMonster*)m_pMember[i];
		if (pMonster) {
			if (pMonster->HoleSubPosition() == pos || pMonster->HoleSubPosition() == SUBPOS_ABSOLUTE::MIDDLE)
				return pMonster;
		}
	}
	return NULL;
}


MonsterTyp CGrpMonster::GetType() {
	for (int i = 1; i < 5; i++)
	{
		CMonster* pMonster = (CMonster*)m_pMember[i];
		if (pMonster) {
			return pMonster->getType();
		}
	}
	assert(false);
	return LORD_CHAOS;
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
	m_grpDirection = newDirection;

	for (int i = 1; i < 5; i++)
	{
		CMonster* pMonster = (CMonster*)m_pMember[i];
		if (pMonster && pMonster->GetDirection() != newDirection) {
			pMonster->TurnTo(newDirection);
			pMonster->AttackOrMoveDone();
		}
	}
	
}

void CGrpMonster::CarryItem(CItem* item) {
	carriedItems.push_back(item);
}


std::deque<CItem*> CGrpMonster::DropInventory() {
	if (!carriedItems.empty()) {
		std::deque<CItem*> inventory = carriedItems;
		carriedItems.clear();
		return inventory;
	}
	else {
		return {};
	}
}

