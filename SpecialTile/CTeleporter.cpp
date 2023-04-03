#include "stdafx.h"
#include "CTeleporter.h"
#include "..\DMDoc.h"
#include "..\Mobs\MobGroups\GrpHeld.h"
#include "..\XMLParser\CDungeonMap.h"

CTeleporter::CTeleporter(TeleporterAttributes attributes, bool visible, TeleporterState open) {
	m_attributes = attributes;
	m_isVisible = visible;
	m_open = open;
}

VEKTOR CTeleporter::Trigger(CDMDoc* pDoc, CGrpHeld* pGrpHelden, CDungeonMap* pMap, VEKTOR telePos) {
	VEKTOR heroPos = pGrpHelden->GetVector(); 
	VEKTOR toPos = getTargetField();
	bool soundPlayed = false;
	if (getScope() == TeleporterAttributes::Scope::Items_Party ||
		getScope() == TeleporterAttributes::Scope::All) {
		heroPos = toPos;
		if (getRotationType() == TeleporterAttributes::RotationType::Absolute)
		{
			pDoc->SetzeRichtung(getTargetDirection());
			soundPlayed = true;
			pDoc->PlayDMSound("C:\\Users\\micha\\source\\repos\\DungeonMaster\\sound\\DMCSB-SoundEffect-Teleporting.mp3");
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
	} 
	if (getScope() == TeleporterAttributes::Scope::Items_Party ||
		getScope() == TeleporterAttributes::Scope::Items ||
		getScope() == TeleporterAttributes::Scope::All) {
		
		CField* pFieldFrom = pMap->GetField(telePos);
		CField* pFieldTo = pMap->GetField(toPos);

		for (int i = 0; i < 4; i++) {
			SUBPOS_ABSOLUTE pos = (SUBPOS_ABSOLUTE)i;
			for (CItem* item : pFieldFrom->GetItem(pos)) {
				pFieldTo->PutItem(pFieldFrom->TakeItem(pos), pos);
			}
		}

		/*if (getRotationType() == TeleporterAttributes::RotationType::Absolute)
		{
			pField->DrehenAbsolut(getTargetDirection());
			if (!soundPlayed) {
				pDoc->PlayDMSound("C:\\Users\\micha\\source\\repos\\DungeonMaster\\sound\\DMCSB-SoundEffect-Teleporting.mp3");
				soundPlayed = true;
			}
		}
		else
		{
			if (getTargetDirection() == 90)
			{
				pField->DrehenRelativ(RECHTS);
			}
			else if (getTargetDirection() == 180) {
				pField->DrehenRelativ(RECHTS);
				pField->DrehenRelativ(RECHTS);
			}
			else if (getTargetDirection() == 270) {
				pField->DrehenRelativ(LINKS);
			}
		}*/
	}
	return heroPos;
}