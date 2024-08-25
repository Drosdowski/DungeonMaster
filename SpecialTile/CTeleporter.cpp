#include "stdafx.h"
#include "CTeleporter.h"
#include "..\CalculationHelper\CHelpfulValues.h"
#include "..\DMDoc.h"
#include "..\Mobs\MobGroups\GrpHeld.h"
#include "..\Mobs\MobGroups\GrpMonster.h"
#include "..\XMLParser\CDungeonMap.h"
#include <cassert>

CTeleporter::CTeleporter(TeleporterAttributes attributes, bool visible, TeleporterState open) : CDelayedTile() {
	m_attributes = attributes;
	m_isVisible = visible;
	m_open = open;
	if (open < 0 || open > 1) assert(false);
}

void CTeleporter::Trigger(CDMDoc* pDoc, CDungeonMap* pMap, VEKTOR telePos, bool triggerRotate) {
	CGrpHeld* pGrpHelden = pMap->GetHeroes();
	CField* pTeleporterField = pMap->GetField(telePos);
	CGrpMonster* pGrpMonster = pTeleporterField->GetMonsterGroup();
	VEKTOR heroPos = pGrpHelden->GetVector();
	VEKTOR toPos = getTargetField();
	CField* targetField = pMap->GetField(toPos);
	bool soundPlayed = false;
	// Teleport Monsters
	if (getScope() == TeleporterAttributes::Scope::Creatures ||
		getScope() == TeleporterAttributes::Scope::All) {

		if (pGrpMonster) {
			pTeleporterField->RemoveMonsterGroup();
			targetField->SetMonsterGroup(pGrpMonster);
			pGrpMonster->SetVector(toPos);

			if (!soundPlayed && m_attributes.sound) {
				pDoc->PlayDMSound("C:\\Users\\micha\\source\\repos\\DungeonMaster\\sound\\DMCSB-SoundEffect-Teleporting.mp3");
				soundPlayed = true;
			}
			if (getRotationType() == TeleporterAttributes::RotationType::Absolute)
			{
				pGrpMonster->DrehenAbsolut(getTargetDirection());
			}
			else
			{
				if (getTargetDirection() == 90)
				{
					pGrpMonster->DrehenRelativ(RECHTS);
				}
				else if (getTargetDirection() == 180) {
					pGrpMonster->DrehenRelativ(RECHTS);
					pGrpMonster->DrehenRelativ(RECHTS);
				}
				else if (getTargetDirection() == 270) {
					pGrpMonster->DrehenRelativ(LINKS);
				}
			}
		}
	} 
	// Teleport Heroes
	if (getScope() == TeleporterAttributes::Scope::Items_Party ||
		getScope() == TeleporterAttributes::Scope::All) {
		if (CHelpfulValues::VectorEqual(heroPos, telePos)) { 
			if (!(CHelpfulValues::VectorEqual(heroPos, toPos))) {
				pGrpHelden->Laufen(toPos, true);
				if (!soundPlayed && m_attributes.sound) {
					pDoc->PlayDMSound("C:\\Users\\micha\\source\\repos\\DungeonMaster\\sound\\DMCSB-SoundEffect-Teleporting.mp3");
					soundPlayed = true;
				}
				pGrpMonster = targetField->GetMonsterGroup();
				if (pGrpMonster) {
					pGrpMonster->InstantKill();
				}
			}
			if (triggerRotate)
			{
				if (getRotationType() == TeleporterAttributes::RotationType::Absolute)
				{
					pGrpHelden->DrehenAbsolut(getTargetDirection());
				}
				else
				{
					if (getTargetDirection() == 90)
					{
						pGrpHelden->DrehenRelativ(RECHTS);
					}
					else if (getTargetDirection() == 180) {
						pGrpHelden->DrehenRelativ(RECHTS);
						pGrpHelden->DrehenRelativ(RECHTS);
					}
					else if (getTargetDirection() == 270) {
						pGrpHelden->DrehenRelativ(LINKS);
					}
				}
				pGrpHelden->ChangeCompass();
			}
		}

	} 

	// Item Teleport
	if (getScope() == TeleporterAttributes::Scope::Items_Party ||
		getScope() == TeleporterAttributes::Scope::Items ||
		getScope() == TeleporterAttributes::Scope::All) {
		
		for (int i = 0; i < 4; i++) {
			SUBPOS_ABSOLUTE pos = (SUBPOS_ABSOLUTE)i;
			for (CItem* item : pTeleporterField->GetItem(pos)) {
				targetField->PutItem(pTeleporterField->TakeItem(pos), pos);
				if (!soundPlayed && m_attributes.sound) {
					pDoc->PlayDMSound("C:\\Users\\micha\\source\\repos\\DungeonMaster\\sound\\DMCSB-SoundEffect-Teleporting.mp3");
					soundPlayed = true;
				}
			}
		}

	}
}

void CTeleporter::setOpen(TeleporterState value, int delay)
{ 
	if (value < 0 || value > 1) assert(false);
	if (m_open == TeleporterState::Inactive && value == TeleporterState::Active)
	{
		CDelayedTile::Open(delay);
	}
	else if (m_open == TeleporterState::Active && value == TeleporterState::Inactive) 
	{
		CDelayedTile::Close(delay);
	}
	m_open = value;
}

bool CTeleporter::isOpen()
{
	if (m_open < 0 || m_open > 1) assert(false);
	return (m_open == TeleporterState::Active && openDelayDone()) || (m_open == TeleporterState::Inactive && !closeDelayDone());
}