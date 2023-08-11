// GrpMonster.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "GrpMonster.h"
#include "..\..\Feld.h"
#include "..\Monster.h"
#include "..\MobGroups\GrpHeld.h"
#include "..\..\CalculationHelper\CHelpfulValues.h"
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
		if (i <= attributes.count) {
			InitMonster(i, attributes);
		}
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
		((CMonster*)m_pMember[nr])->setType(attributes.type);
				
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

void CGrpMonster::RandomMove() {
	m_grpDirection = (COMPASS_DIRECTION)( rand() % 4);
}

void CGrpMonster::Scare() {
	m_iScaredCounter += 5;
}

bool CGrpMonster::Altern(CField* field)
{
	bool anyoneAlive = false;
	if (m_iScaredCounter > 0) {
		RandomMove();
		m_iScaredCounter--;
	}

	for (int i=1; i<5; i++)
	{
		CMonster* pMonster= (CMonster*) m_pMember[i];
		if (pMonster) {
			bool monsterAlive = pMonster->Altern(field);
			if (!monsterAlive)
			{
				CMagicMissile* dust = new CMagicMissile(CMagicMissile::MagicMissileType::Dust, pMonster->GetSize());
				dust->Explode();

				m_lastPosition = pMonster->HoleSubPosition();
				field->CastMissile(dust, m_lastPosition);
				delete m_pMember[i];
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

CMonster* CGrpMonster::AttackHero(VEKTOR monsterPos, VEKTOR heroPos) {
	if (AnyoneReady())
	{
		for (int i = 1; i < 5; i++)
		{
			CMonster* pMonster = (CMonster*)m_pMember[i];
			if (pMonster && pMonster->IstBereit()) {
				//CHeld* held = (CHeld*)NearestTarget(hisPos);

				if (pMonster->InFrontOfOpponent(monsterPos, heroPos, emptyNorthRow(), emptyEastRow(), emptySouthRow(), emptyWestRow())) {
					if (pMonster->GetDirection() == m_grpDirection)
					{
						int dmg = pMonster->CalcDmg(1); // todo monster attacke random
						pMonster->AttackModeWithDmg(dmg);
						pMonster->AttackDone();
						return pMonster; // pro Tick nur ein Angriff / Gruppe
					}
					else {
						pMonster->SetDirection(m_grpDirection); // Einzeldrehung zur Attacke
					}
				}
				else {
					TryToAdavanceToFirstRow(i, monsterPos, heroPos);
				}
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
	if (m_iScaredCounter > 0) {
		return false;
	}

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

void CGrpMonster::MoveDone() {
	for (int i = 1; i < 5; i++)
	{
		CMonster* pMonster = (CMonster*)m_pMember[i];
		if (pMonster) {
			pMonster->MoveDone();
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

CMonster* CGrpMonster::GetMonsterByAbsSubPos(SUBPOS_ABSOLUTE pos) {
	for (int i = 1; i < 5; i++)
	{
		CMonster* pMonster = (CMonster*)m_pMember[i];
		if (pMonster) {
			if (pMonster->HoleSubPosition() == pos) 
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

void CGrpMonster::Laufen(VEKTOR WunschPos, boolean teleport) {
	for (int i = 1; i <= 4; i++)
		if ((m_pMember[i]) && (m_pMember[i]->isAlive()))
		{
			// todo monster werden müde?
			m_pMember[i]->MoveDone();
		}
	m_posPosition = WunschPos;
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

