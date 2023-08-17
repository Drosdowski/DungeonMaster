#include "stdafx.h"
#include <sstream>
#include <fstream>
#include <string>
#include "TinyXML/tinyxml.h"
#include "Mobs/MobGroups/GrpHeld.h"
#include "Mobs/MobGroups/GrpMonster.h"
#include "Items\FloorDecoration.h"
#include "Items\WallDecoration.h"
#include "Items/CMiscellaneous.h"
#include "Items/Weapon.h"
#include "Items/Cloth.h"
#include "Items/Potion.h"
#include "Items/Scroll.h"
#include "Items/Container.h"
#include "SpecialTile/CTeleporter.h"
#include "SpecialTile/Trickwall.h"
#include "CDungeonMap.h"

CDungeonMap::CDungeonMap(CItemInfos* pItemInfos, CMonsterInfos* pMonsterInfos)
{ 
	VEKTOR v{ 0,0,0 };

	m_pEdgeWall = new CField(v, FeldTyp::WALL);
	m_pItemInfos = pItemInfos; 
	m_pMonsterInfos = pMonsterInfos;
	m_startRicht = COMPASS_DIRECTION::NORTH;
	m_actuatorType = {};
	m_pDoc = NULL;
	std::ifstream f(FILENAME);
	saveGameExists = f.good();
	f.close();
	LoadMap();
	m_pGrpHelden = new CGrpHeld(m_start, m_startRicht);
	LoadGame(m_pGrpHelden);
}

CDungeonMap::~CDungeonMap()
{
	delete m_pEdgeWall;
	delete m_pGrpHelden;
	for (int z = 0; z < FELD_MAX_Z; z++) {
		if (m_wallDecorationTypes && m_wallDecorationTypes[z])
			delete m_wallDecorationTypes[z];
		for (int i = 0; i < m_LevelWidth[z]; i++)
			for (int j = 0; j < m_LevelHeight[z]; j++) {
				delete m_pFeld[i][j][z];
			}
	}
	delete m_wallDecorationTypes;
		
	delete[] m_doorAtt;
	delete[] m_miscellaneousAtt;
	delete[] m_clothAtt;
	delete[] m_weaponAtt;
	delete[] m_potionAtt;
	delete[] m_scrollAtt;
	delete[] m_containerAtt;
	
	delete[] m_actuatorType;
	delete[] m_teleportAtt;
	delete[] m_creatureAtt;
	delete[] m_pTextInfos;

	delete m_pDoc;
}

CField* CDungeonMap::GetField(int x, int y, int z) {
	if (x >= m_LevelWidth[z] || y >= m_LevelHeight[z] || x < 0 || y < 0) {		
		return m_pEdgeWall;
	}
	else {
		return m_pFeld[x][y][z];
	}
}

CField* CDungeonMap::GetField(VEKTOR v) {
	return GetField(v.x, v.y, v.z);
}

CPoint CDungeonMap::GetOffset(int ebene) {
	return CPoint(m_offsetX[ebene], m_offsetY[ebene]);
}


CField* CDungeonMap::ParseStairs(TiXmlElement* rootNode, VEKTOR pos) {
	int orientation;
	int direction;
	rootNode->QueryIntAttribute("direction", &direction);
	rootNode->QueryIntAttribute("orientation", &orientation);
	COMPASS_DIRECTION stairExit;
	if (orientation == 0) {
		if (pos.x <1 || m_pFeld[pos.x - 1][pos.y][pos.z]->HoleTyp() == WALL)
			stairExit = EAST;
		else
			stairExit = WEST;
	}
	else {
		if (pos.y < 1 || m_pFeld[pos.x][pos.y-1][pos.z]->HoleTyp() == WALL)
			stairExit = SOUTH;
		else
			stairExit = NORTH;
	}
	CStairs* stair;
	if (direction == 0)
		stair = new CStairs(CStairs::StairType::DOWN, stairExit);
	else
		stair = new CStairs(CStairs::StairType::UP, stairExit);

	return new CField(pos, stair);
}

CField* CDungeonMap::ParsePit(TiXmlElement* rootNode, VEKTOR pos) {
	int is_imaginary, is_invisible, is_open;
	rootNode->QueryIntAttribute("is_imaginary", &is_imaginary);
	rootNode->QueryIntAttribute("is_invisible", &is_invisible);
	rootNode->QueryIntAttribute("is_open", &is_open);

	CPit::PitType pitType;
	if (is_imaginary) {
		pitType = CPit::PitType::Imaginary;
	}
	else if (is_invisible) {
		pitType = CPit::PitType::Invisible;
	}
	else {
		pitType = CPit::PitType::Standard;
	}

	return new CField(pos, new CPit(pitType, (CPit::PitState)is_open));
}

CField* CDungeonMap::ParseTeleport(TiXmlElement* rootNode, VEKTOR pos) {
	int is_visible, is_open, index;
	rootNode->QueryIntAttribute("is_visible", &is_visible);
	rootNode->QueryIntAttribute("is_open", &is_open);

	TiXmlElement* parentElement = rootNode->FirstChildElement();
	while (parentElement)
	{
		const char* parent = parentElement->Value();
		if (strcmp(parent, "items") == 0)
		{
			TiXmlElement* teleItem = parentElement->FirstChildElement();
			if (teleItem) {
				teleItem->QueryIntAttribute("index", &index);
				CTeleporter* teleItem = new CTeleporter(m_teleportAtt[index], is_visible, (CTeleporter::TeleporterState) is_open);
				return new CField(pos, teleItem);
			}

		}
		parentElement = parentElement->NextSiblingElement();
	}
	
	return NULL;
}


CField* CDungeonMap::ParseDoor(TiXmlElement* rootNode, VEKTOR pos) {
	int orientation;
	CDoorAttributes attribute;
	rootNode->QueryIntAttribute("orientation", &orientation);
	
	TiXmlElement* parentElement = rootNode->FirstChildElement();
	while (parentElement)
	{
		const char* parent = parentElement->Value();
		if (strcmp(parent, "items") == 0)
		{
			TiXmlElement* doorItem = parentElement->FirstChildElement();
			if (doorItem && strcmp(doorItem->Value(), "door") == 0) {
				int index;
				doorItem->QueryIntAttribute("index", &index);
				attribute = m_doorAtt[index];
			}

		}
		parentElement = parentElement->NextSiblingElement();

	}
	return new CField(pos, new CDoor(attribute, (orientation != 0)));
}

CField* CDungeonMap::ParseTrickWall(TiXmlElement* rootNode, VEKTOR pos) {
	int is_imaginary, is_open;
	
	rootNode->QueryIntAttribute("is_imaginary", &is_imaginary);
	rootNode->QueryIntAttribute("is_open", &is_open);

	CTrickWall::TrickWallType type = (is_imaginary == 1) ? CTrickWall::Imaginary : CTrickWall::Standard;
	CTrickWall::TrickWallState state = (is_open == 1) ? CTrickWall::Opened : CTrickWall::Closed;
	return new CField(pos, new CTrickWall(type, state));
}


void CDungeonMap::ParseTile(TiXmlElement* rootNode, int etage) {
	const char* parent = rootNode->Value();
	int index;
	rootNode->QueryIntAttribute("index", &index);
	int x = index % m_LevelWidth[etage];
	int y = (int)(index / m_LevelWidth[etage]);
	int type;
	rootNode->QueryIntAttribute("type", &type);
	int hasObjects;
	rootNode->QueryIntAttribute("has_objects", &hasObjects);
	int allowDecoration, allowDecorations;
	rootNode->QueryIntAttribute("allow_decoration_east", &allowDecorations);
	rootNode->QueryIntAttribute("allow_decoration_north", &allowDecoration);
	allowDecorations += allowDecoration;
	rootNode->QueryIntAttribute("allow_decoration_south", &allowDecoration);
	allowDecorations += allowDecoration;
	rootNode->QueryIntAttribute("allow_decoration_west", &allowDecoration);
	allowDecorations += allowDecoration;

	// 0 = Wall , 1 == Empty, 2 = Pit, 3 = Stair, 4 == Door, 5 = Teleport, 6 = Trickwall
	FeldTyp iFieldType = (FeldTyp)type;
	VEKTOR pos{ x, y, etage };

	if (iFieldType == FeldTyp::DOOR)
	{
		m_pFeld[x][y][etage] = ParseDoor(rootNode, pos);
	}
	else if (iFieldType == FeldTyp::STAIRS) {
		m_pFeld[x][y][etage] = ParseStairs(rootNode, pos);
	}
	else if (iFieldType == FeldTyp::PIT) {
		m_pFeld[x][y][etage] = ParsePit(rootNode, pos);
	}
	else if (iFieldType == FeldTyp::TELEPORT) {
		m_pFeld[x][y][etage] = ParseTeleport(rootNode, pos);
	}
	else if (iFieldType == FeldTyp::TRICKWALL) {
		m_pFeld[x][y][etage] = ParseTrickWall(rootNode, pos);
	}
	else
		m_pFeld[x][y][etage] = new CField(pos, iFieldType); // etage 1 / index 30 => m_levelWidth[1] kaputt!
	
	if (hasObjects == 1 || allowDecorations >= 1) {
		TiXmlElement* parentElement = rootNode->FirstChildElement();
		if (parentElement)
		{
			ParseItems(parentElement, VEKTOR{x ,y, etage}, true);
		}
	}
}

void CDungeonMap::ParseItems(TiXmlElement* rootNode, VEKTOR coords, bool initDungeon) {
	const char* parent = rootNode->Value();
	if (strcmp(parent, "items") == 0)
		{
			TiXmlElement* item = rootNode->FirstChildElement();
			while (item)
			{
				if (initDungeon && !saveGameExists || !initDungeon) {
					if (strcmp(item->Value(), "miscellaneous") == 0) {
						ParseMiscellaneous(item, coords);
					}
					else if (strcmp(item->Value(), "weapon") == 0) {
						ParseWeapons(item, coords);
					}
					else if (strcmp(item->Value(), "cloth") == 0) {
						ParseCloth(item, coords);
					}
					else if (strcmp(item->Value(), "potion") == 0) {
						ParsePotions(item, coords);
					}
					else if (strcmp(item->Value(), "scroll") == 0) {
						ParseScrolls(item, coords);
					}
					else if (strcmp(item->Value(), "container") == 0) {
						ParseContainers(item, coords);
					}
				}
				if (initDungeon) {
					if (strcmp(item->Value(), "actuator") == 0) {
						ParseActuator(item, coords);
					}
					else if (strcmp(item->Value(), "random_floor_decoration") == 0) {
						ParseFloorDecoration(item, coords);
					}
					else if (strcmp(item->Value(), "random_wall_decoration") == 0) {
						ParseWallDecoration(item, coords);
					}
					else if (strcmp(item->Value(), "creature") == 0 && monsterAktiv) {
						ParseCreature(item, coords);
					}
				}
			
				item = item->NextSiblingElement();
			}


		}
}

void CDungeonMap::ParseMiscellaneous(TiXmlElement* miscItem, VEKTOR coords) {
	int index, subPos;
	miscItem->QueryIntAttribute("index", &index);
	miscItem->QueryIntAttribute("position", &subPos);
	m_pFeld[coords.x][coords.y][coords.z]->PutMisc(new CMiscellaneous(index, m_miscellaneousAtt[index]), (SUBPOS_ABSOLUTE)subPos);
}

void CDungeonMap::ParsePotions(TiXmlElement* potionItem, VEKTOR coords) {
	int index, subPos;
	potionItem->QueryIntAttribute("index", &index);
	potionItem->QueryIntAttribute("position", &subPos);
	m_pFeld[coords.x][coords.y][coords.z]->PutPotion(new CPotion(index, m_potionAtt[index]), (SUBPOS_ABSOLUTE)subPos);
}

void CDungeonMap::ParseScrolls(TiXmlElement* scrollItem, VEKTOR coords) {
	int index, subPos;
	scrollItem->QueryIntAttribute("index", &index);
	scrollItem->QueryIntAttribute("position", &subPos);
	m_pFeld[coords.x][coords.y][coords.z]->PutScroll(new CScroll(index, m_scrollAtt[index]), (SUBPOS_ABSOLUTE)subPos);
}

void CDungeonMap::ParseContainers(TiXmlElement* containerItem, VEKTOR coords) {
	int index;
	containerItem->QueryIntAttribute("index", &index);

	int  itemNumber = 0; // ignore type, only 0 = chest exist!
	TiXmlElement* subElement = containerItem->FirstChildElement();
	CContainer* container = new CContainer(index, m_containerAtt[index]);
	while (subElement)
	{
		const char* itemsInChest = subElement->Value();
		if (strcmp(itemsInChest, "items") == 0) {
			CItem* pItem;
			int index;

			TiXmlElement* itemElement = subElement->FirstChildElement();
			const char* itemInChest = itemElement->Value();
			itemElement->QueryIntAttribute("index", &index);

			if (strcmp(itemInChest, "potion") == 0) {
				pItem = new CPotion(index, m_potionAtt[index]);
			}
			else if (strcmp(itemInChest, "scroll") == 0) {
				pItem = new CScroll(index, m_scrollAtt[index]);
			}
			else if (strcmp(itemInChest, "miscellaneous") == 0) {
				pItem = new CMiscellaneous(index, m_miscellaneousAtt[index]);
			}
			else if (strcmp(itemInChest, "weapon") == 0) {
				pItem = new CWeapon(index, m_weaponAtt[index]);
			}
			else {
				assert(false); // todo
			}
			container->SetSubitems(pItem, itemNumber);

		}
		subElement = subElement->NextSiblingElement();
		itemNumber++;
	}

	m_pFeld[coords.x][coords.y][coords.z]->PutContainer(container, (SUBPOS_ABSOLUTE)0);
}

void CDungeonMap::ParseWeapons(TiXmlElement* weaponItem, VEKTOR coords) {
	int index, subPos;
	weaponItem->QueryIntAttribute("index", &index);
	weaponItem->QueryIntAttribute("position", &subPos);

	m_pFeld[coords.x][coords.y][coords.z]->PutWeapon(new CWeapon(index, m_weaponAtt[index]), (SUBPOS_ABSOLUTE)subPos);
}

void CDungeonMap::ParseCloth(TiXmlElement* clothItem, VEKTOR coords) {
	int index, subPos;
	clothItem->QueryIntAttribute("index", &index);
	clothItem->QueryIntAttribute("position", &subPos);

	m_pFeld[coords.x][coords.y][coords.z]->PutCloth(new CCloth(index, m_clothAtt[index]), (SUBPOS_ABSOLUTE)subPos);
}

void CDungeonMap::ParseFloorDecoration(TiXmlElement* decoItem, VEKTOR coords) {
	int graphic;
	decoItem->QueryIntAttribute("graphic", &graphic);
	CFloorDecoration* deco = new CFloorDecoration((FloorDecorationType)(graphic-1));
	m_pFeld[coords.x][coords.y][coords.z]->PutFloorDeco(deco);
}

void CDungeonMap::ParseWallDecoration(TiXmlElement* decoItem, VEKTOR coords) {
	int graphic, position;
	decoItem->QueryIntAttribute("graphic", &graphic);
	decoItem->QueryIntAttribute("position", &position);
	CWallDecoration* deco = new CWallDecoration(m_wallDecorationTypes[coords.z][graphic-1]);
	m_pFeld[coords.x][coords.y][coords.z]->PutWallDeco(deco, position);
}

void CDungeonMap::ParseText(TiXmlElement* rootNode, VEKTOR coords) {
	int index;
	rootNode->QueryIntAttribute("index", &index);
	//CString text = m_pTextInfos[index];
}


void CDungeonMap::ParseCreature(TiXmlElement* creatureItem, VEKTOR coords) {
	int index, position;
	creatureItem->QueryIntAttribute("index", &index);
	creatureItem->QueryIntAttribute("position", &position);

	CCreatureAttributes attribute = m_creatureAtt[index];
	CGrpMonster* pGrpMonster = new CGrpMonster(coords, attribute, index);

	m_pFeld[coords.x][coords.y][coords.z]->SetMonsterGroup(pGrpMonster);

	TiXmlElement* parentElement = creatureItem->FirstChildElement();
	while (parentElement)
	{
		const char* parent = parentElement->Value();
		if (strcmp(parent, "items") == 0)
		{
			int index, position;
			TiXmlElement* monsterItem = parentElement->FirstChildElement();
			while (monsterItem) 
			{
				const char* subParent = monsterItem->Value();
				if (strcmp(subParent, "miscellaneous") == 0)
				{
					monsterItem->QueryIntAttribute("index", &index);
					monsterItem->QueryIntAttribute("position", &position);
					CMiscellaneous* misc = new CMiscellaneous(index, m_miscellaneousAtt[index]);
					pGrpMonster->CarryItem(misc);

				}
				else if (strcmp(subParent, "weapon") == 0) {
					monsterItem->QueryIntAttribute("index", &index);
					monsterItem->QueryIntAttribute("position", &position);
					CWeapon* weapon = new CWeapon(index, m_weaponAtt[index]);
					pGrpMonster->CarryItem(weapon);
				}
				else if (strcmp(subParent, "cloth") == 0) {
					monsterItem->QueryIntAttribute("index", &index);
					monsterItem->QueryIntAttribute("position", &position);
					CCloth* cloth = new CCloth(index, m_clothAtt[index]);
					pGrpMonster->CarryItem(cloth);
				}
				else if (strcmp(subParent, "potion") == 0) {
					monsterItem->QueryIntAttribute("index", &index);
					monsterItem->QueryIntAttribute("position", &position);
					CPotion* potion = new CPotion(index, m_potionAtt[index]);
					pGrpMonster->CarryItem(potion);
				}
				else if (strcmp(subParent, "scroll") == 0) {
					monsterItem->QueryIntAttribute("index", &index);
					monsterItem->QueryIntAttribute("position", &position);
					CScroll* scroll = new CScroll(index, m_scrollAtt[index]);
					pGrpMonster->CarryItem(scroll);
				}
				else if (strcmp(subParent, "container") == 0) {
					monsterItem->QueryIntAttribute("index", &index);
					monsterItem->QueryIntAttribute("position", &position);
					CContainer* container = new CContainer(index, m_containerAtt[index]);
					pGrpMonster->CarryItem(container);
				}
				monsterItem = monsterItem->NextSiblingElement();

			}
		}
		parentElement = parentElement->NextSiblingElement();
	}
}

void CDungeonMap::ParseActuator(TiXmlElement* actuatorItem, VEKTOR coords) {

	/*	<actuator index = "151" position = "0">
			<!--Floor actuator : 3 - P-->
			< type>3 < / type >
			< data>0 < / data > <!--type 3 specific: always activated-->
			< graphic>4 < / graphic > <!-- 0 = invisible-->
			<action_target>remote< / action_target>
			< delay>1 < / delay >
			< has_sound>1 < / has_sound >
			< has_revert>0 < / has_revert >
			<action_type>Set< / action_type>
			< once_only>0 < / once_only >
			< target_y>9 < / target_y > <!--remote specific-->
			< target_x>5 < / target_x > <!--remote specific-->
			<direction>North< / direction> <!--remote specific-->
			< / actuator> <!--North / TopLeft-->
			< / items> */
	int index, position, type, graphic, data, once_only, delay;
	int action = 0;
	VEKTOR target = coords;
	CActuator::ActionTypes actionType;
	CActuator::ActionTarget actionTarget;
	actuatorItem->QueryIntAttribute("index", &index);
	actuatorItem->QueryIntAttribute("position", &position);
	
	// todo ab hier children
	TiXmlElement* actuatorAttributes = actuatorItem->FirstChildElement();
	while (actuatorAttributes)
	{
		if (strcmp(actuatorAttributes->Value(), "type") == 0) {
			const char* strValue = actuatorAttributes->GetText();
			std::stringstream streamValue;
			streamValue << strValue;
			streamValue >> type;
		}
		else if (strcmp(actuatorAttributes->Value(), "data") == 0 && type != 5) {
			const char* strValue = actuatorAttributes->GetText();
			std::stringstream streamValue; // todo type 5 hat anderes Format für data
			streamValue << strValue;
			streamValue >> data;
		}
		else if (strcmp(actuatorAttributes->Value(), "graphic") == 0) {
			const char* strValue = actuatorAttributes->GetText();
			std::stringstream streamValue;
			streamValue << strValue;
			streamValue >> graphic;
		}
		else if (strcmp(actuatorAttributes->Value(), "action_target") == 0) {
			const char* strActionTarget = actuatorAttributes->GetText();
			if (strcmp(strActionTarget, "remote") == 0) actionTarget = CActuator::Remote;
			if (strcmp(strActionTarget, "local") == 0) actionTarget = CActuator::Local;
		}
		else if (strcmp(actuatorAttributes->Value(), "delay") == 0) {
			const char* strValue = actuatorAttributes->GetText();
			std::stringstream streamValue;
			streamValue << strValue;
			streamValue >> delay;
		}
		else if (strcmp(actuatorAttributes->Value(), "action_type") == 0) {
			const char* strActionType = actuatorAttributes->GetText();
			if (strcmp(strActionType, "Set") == 0) actionType = CActuator::Set;
			if (strcmp(strActionType, "Clear") == 0) actionType = CActuator::Clear;
			if (strcmp(strActionType, "Hold") == 0) actionType = CActuator::Hold;
			if (strcmp(strActionType, "Toggle") == 0) actionType = CActuator::Toggle;
		}
		else if (strcmp(actuatorAttributes->Value(), "target_x") == 0) {
			const char* strValue = actuatorAttributes->GetText();
			std::stringstream streamValue;
			streamValue << strValue;
			streamValue >> target.x;
		}
		else if (strcmp(actuatorAttributes->Value(), "target_y") == 0) {
			const char* strValue = actuatorAttributes->GetText();
			std::stringstream streamValue;
			streamValue << strValue;
			streamValue >> target.y;
		}
		else if (strcmp(actuatorAttributes->Value(), "once_only") == 0) {
			const char* strValue = actuatorAttributes->GetText();
			std::stringstream streamValue;
			streamValue << strValue;
			streamValue >> once_only;
		}	
		else if (strcmp(actuatorAttributes->Value(), "action") == 0) {
			const char* strValue = actuatorAttributes->GetText();
			std::stringstream streamValue;
			streamValue << strValue;
			streamValue >> action;
		}

		actuatorAttributes = actuatorAttributes->NextSiblingElement();
	}

	//WallDecorationType graphicType = graphic > 0 ? m_wallDecorationTypes[graphic, coords.z] : None;
	//if (graphicType < 0 || graphicType > 255) graphicType = None; 
	CActuator* actuator = new CActuator(index, (COMPASS_DIRECTION)position, target, actionType, actionTarget, type, data, graphic, once_only, delay, (action == 1));
	m_pFeld[coords.x][coords.y][coords.z]->PutActuator(actuator, (COMPASS_DIRECTION)position);
}

void CDungeonMap::ParseWallDecorationGraphic(TiXmlElement* rootNode, int etage) {
	int index;
	rootNode->QueryIntAttribute("index", &index);
	int type;
	rootNode->QueryIntAttribute("type", &type);
	
	m_wallDecorationTypes[etage][index] = (WallDecorationType)type;
}

void CDungeonMap::ParseWallDecorationGraphics(TiXmlElement* rootNode, int etage) {
	TiXmlElement* parentElement = rootNode->FirstChildElement();
	while (parentElement)
	{
		const char* parent = parentElement->Value();
		if (strcmp(parent, "wall_decoration_graphic") == 0)
		{
			ParseWallDecorationGraphic(parentElement, etage);
		}
		parentElement = parentElement->NextSiblingElement();
	}
}

void CDungeonMap::ParseTiles(TiXmlElement* tiles, int etage) {
	TiXmlElement* parentElement = tiles->FirstChildElement();
	while (parentElement)
	{
		const char* parent = parentElement->Value();
		if (strcmp(parent, "tile") == 0)
		{
			ParseTile(parentElement, etage);
		}
		parentElement = parentElement->NextSiblingElement();
	}
}


void CDungeonMap::ParseMap(TiXmlElement* rootNode, int etage) {
	m_wallDecorationTypes[etage] = NULL;
	TiXmlElement* parentElement = rootNode->FirstChildElement();
	while (parentElement)
	{
		const char* parent = parentElement->Value();
		if (strcmp(parent, "wall_decoration_graphics") == 0)
		{
			m_wallDecorationTypes[etage] = new WallDecorationType[15];
			ParseWallDecorationGraphics(parentElement, etage);
		}
		parentElement = parentElement->NextSiblingElement();
	}
	parentElement = rootNode->FirstChildElement();
	while (parentElement)
	{
		const char* parent = parentElement->Value();
		if (strcmp(parent, "tiles") == 0)
		{
			ParseTiles(parentElement, etage);
		}
		parentElement = parentElement->NextSiblingElement();
	}
}
	
void CDungeonMap::ParseMaps(TiXmlElement* rootNode) {
	TiXmlElement* parentElement = rootNode->FirstChildElement();
	while (parentElement)
	{
		const char* parent = parentElement->Value();
		int etage;

		parentElement->QueryIntAttribute("index", &etage);
		parentElement->QueryIntAttribute("width", &m_LevelWidth[etage]);
		parentElement->QueryIntAttribute("height", &m_LevelHeight[etage]);
		parentElement->QueryIntAttribute("difficulty", &m_LevelDiff[etage]);

		parentElement->QueryIntAttribute("offsetx", &m_offsetX[etage]);
		parentElement->QueryIntAttribute("offsety", &m_offsetY[etage]);

		ParseMap(parentElement, etage);
		parentElement = parentElement->NextSiblingElement();
	}
}

void CDungeonMap::ParseDoorObjects(TiXmlElement* rootNode) {
	TiXmlElement* parentElement = rootNode->FirstChildElement();
	while (parentElement)
	{
		const char* parent = parentElement->Value();
		if (strcmp(parent, "door") == 0) // several existing
		{
			int index, button, fireball, force, type;
			CDoorAttributes attribute;
			parentElement->QueryIntAttribute("index", &index);
			parentElement->QueryIntAttribute("type", &type);
			parentElement->QueryIntAttribute("ornate", &attribute.ornate);
			parentElement->QueryIntAttribute("button", &button);
			parentElement->QueryIntAttribute("fireball", &fireball);
			parentElement->QueryIntAttribute("force", &force);
			attribute.button = (button == 1);
			attribute.fireball = (fireball == 1);
			attribute.force = (force == 1);
			attribute.type = (CDoorAttributes::DoorType)type;
			const char* opening = parentElement->Attribute("opening");
			if (strcmp(opening, "Vertical")) attribute.openingDir = CDoorAttributes::Vertical;
			if (strcmp(opening, "Horizontal")) attribute.openingDir = CDoorAttributes::Horizontal;
			m_doorAtt[index] = attribute;
		}
		parentElement = parentElement->NextSiblingElement();
	}
}

void CDungeonMap::ParseMiscellaneousObjects(TiXmlElement* rootNode) {
	TiXmlElement* parentElement = rootNode->FirstChildElement();
	while (parentElement)
	{
		const char* parent = parentElement->Value();
		if (strcmp(parent, "miscellaneous") == 0) // several existing
		{
			int index, type;
			CMiscellaneousAttributes att;
			parentElement->QueryIntAttribute("index", &index);
			parentElement->QueryIntAttribute("subtype", &att.subtype);
			parentElement->QueryIntAttribute("type", &type);
			att.type = (CMiscellaneousAttributes::MiscItemType)type;
			att.fixAttributes = m_pItemInfos->GetMiscInfo(type);
			m_miscellaneousAtt[index] = att;
		}
		parentElement = parentElement->NextSiblingElement();
	}
}

void CDungeonMap::ParseWeaponObjects(TiXmlElement* rootNode) {
	TiXmlElement* parentElement = rootNode->FirstChildElement();
	while (parentElement)
	{
		const char* parent = parentElement->Value();
		if (strcmp(parent, "weapon") == 0) // several existing
		{
			int index, type;
			CWeaponAttributes att;
			parentElement->QueryIntAttribute("index", &index);
			parentElement->QueryIntAttribute("number_of_charges", &att.charges);
			parentElement->QueryIntAttribute("type", &type);
			att.type = (CWeaponAttributes::WeaponType)type;
			att.fixAttributes = m_pItemInfos->GetWeaponInfo(type);
			m_weaponAtt[index] = att;
		}
		parentElement = parentElement->NextSiblingElement();
	}
}

void CDungeonMap::ParseClothObjects(TiXmlElement* rootNode) {
	TiXmlElement* parentElement = rootNode->FirstChildElement();
	while (parentElement)
	{
		const char* parent = parentElement->Value();
		if (strcmp(parent, "cloth") == 0) // several existing
		{
			int index, type;
			CClothAttributes att;
			parentElement->QueryIntAttribute("index", &index);
			parentElement->QueryIntAttribute("type", &type);
			att.type = (CClothAttributes::ClothType)type;
			att.fixAttributes = m_pItemInfos->GetClothInfo(type);
			m_clothAtt[index] = att;
		}
		parentElement = parentElement->NextSiblingElement();
	}
}

void CDungeonMap::ParsePotionObjects(TiXmlElement* rootNode) {
	TiXmlElement* parentElement = rootNode->FirstChildElement();
	while (parentElement)
	{
		const char* parent = parentElement->Value(); 
		if (strcmp(parent, "potion") == 0) // several existing
		{
			int index, type, power;
			CPotionAttributes att;
			parentElement->QueryIntAttribute("index", &index);
			parentElement->QueryIntAttribute("type", &type);
			parentElement->QueryIntAttribute("power", &power);
			att.type = (CPotionAttributes::PotionType)type;
			att.power = power;
			m_potionAtt[index] = att;
		}
		parentElement = parentElement->NextSiblingElement();
	}
}

void CDungeonMap::ParseScrollObjects(TiXmlElement* rootNode) {
	TiXmlElement* parentElement = rootNode->FirstChildElement();
	while (parentElement)
	{
		const char* parent = parentElement->Value();
		if (strcmp(parent, "scroll") == 0) 
		{
			int index;
			CScrollAttributes att;
			parentElement->QueryIntAttribute("index", &index);
			att.text = parentElement->GetText();
			att.open = false;
			m_scrollAtt[index] = att;
		}
		parentElement = parentElement->NextSiblingElement();
	}
}

void CDungeonMap::ParseContainerObjects(TiXmlElement* rootNode) {
	TiXmlElement* parentElement = rootNode->FirstChildElement();
	while (parentElement)
	{
		const char* parent = parentElement->Value();
		if (strcmp(parent, "container") == 0)
		{
			int index; // ignore type, only 0 = chest exist!
			parentElement->QueryIntAttribute("index", &index);
			CContainerAttributes att;
			att.open = false;
			m_containerAtt[index] = att;
		}
		parentElement = parentElement->NextSiblingElement();
	}
}

void CDungeonMap::ParseCreatureObjects(TiXmlElement* rootNode) {
	TiXmlElement* parentElement = rootNode->FirstChildElement();
	while (parentElement)
	{
		const char* parent = parentElement->Value();
		if (strcmp(parent, "creature") == 0)
		{
			/*<creature index = "0"
				type = "6"
				number_of_creatures = "4"
				position_1 = "1"
				position_2 = "0"
				position_3 = "3"
				position_4 = "2"
				hit_point_1 = "46"
				hit_point_2 = "52"
				hit_point_3 = "49"
				hit_point_4 = "46"
				facing = "North"*/
			CCreatureAttributes attribute;
			int index, type;
			parentElement->QueryIntAttribute("index", &index);
			parentElement->QueryIntAttribute("type", &type);
			attribute.type = (MonsterTyp)type;
			parentElement->QueryIntAttribute("number_of_creatures", &attribute.count);
			parentElement->QueryIntAttribute("position_1", &attribute.position[0]);
			parentElement->QueryIntAttribute("hit_point_1", &attribute.hitPoints[0]);
			parentElement->QueryIntAttribute("position_2", &attribute.position[1]);
			parentElement->QueryIntAttribute("hit_point_2", &attribute.hitPoints[1]);
			parentElement->QueryIntAttribute("position_3", &attribute.position[2]);
			parentElement->QueryIntAttribute("hit_point_3", &attribute.hitPoints[2]);
			parentElement->QueryIntAttribute("position_4", &attribute.position[3]);
			parentElement->QueryIntAttribute("hit_point_4", &attribute.hitPoints[3]);

			const char* facing = parentElement->Attribute("facing");
			if (strcmp(facing, "North")) attribute.direction = NORTH;
			if (strcmp(facing, "East")) attribute.direction = EAST;
			if (strcmp(facing, "South")) attribute.direction = SOUTH;
			if (strcmp(facing, "West")) attribute.direction = WEST;

			attribute.monsterInfo = m_pMonsterInfos->GetMonsterInfo(type);

			m_creatureAtt[index] = attribute;
		}
		parentElement = parentElement->NextSiblingElement();

	}
}


void CDungeonMap::ParseActuatorObjects(TiXmlElement* rootNode) {
	TiXmlElement* parentElement = rootNode->FirstChildElement();
	while (parentElement)
	{
		const char* parent = parentElement->Value();
		if (strcmp(parent, "actuator") == 0) // several existing
		{
			/*
			<actuator index="151"
			type="3"
			data="0"
			graphic_number="4"
			word2_bits012="192"
			word3="18752"/>*/

			int index, type;

			parentElement->QueryIntAttribute("index", &index);
			parentElement->QueryIntAttribute("type", &type);
			m_actuatorType[index] = type;
		}
		parentElement = parentElement->NextSiblingElement();
	}
}

void CDungeonMap::ParseTeleporterObjects(TiXmlElement* rootNode) {
	/*<teleporter index = "0"
		dest_map = "10"
		dest_map_x = "6"
		dest_map_y = "0"
		rotation = "0"
		rotation_type = "Relative"
		scope = "All"
		sound = "0" / >*/
	TiXmlElement* parentElement = rootNode->FirstChildElement();
	while (parentElement)
	{
		const char* parent = parentElement->Value();
		if (strcmp(parent, "teleporter") == 0) // several existing
		{
			int index;
			TeleporterAttributes attribute;
			parentElement->QueryIntAttribute("index", &index);
			parentElement->QueryIntAttribute("dest_map_x", &attribute.target.x);
			parentElement->QueryIntAttribute("dest_map_y", &attribute.target.y);
			parentElement->QueryIntAttribute("dest_map", &attribute.target.z);
			parentElement->QueryIntAttribute("rotation", &attribute.rotation);
			const char* rotation_type = parentElement->Attribute("rotation_type");
			attribute.rotation = (strcmp(rotation_type, "Relative") == 0) ? TeleporterAttributes::RotationType::Relative : TeleporterAttributes::RotationType::Absolute;
			const char* scope = parentElement->Attribute("scope");
			if (strcmp(scope, "All") == 0)  attribute.scope = TeleporterAttributes::Scope::All;
			if (strcmp(scope, "Creatures") == 0)  attribute.scope = TeleporterAttributes::Scope::Creatures;
			if (strcmp(scope, "Items") == 0)  attribute.scope = TeleporterAttributes::Scope::Items;
			if (strcmp(scope, "Items_Party") == 0)  attribute.scope = TeleporterAttributes::Scope::Items_Party;
			
			parentElement->QueryIntAttribute("sound", &attribute.sound);
			m_teleportAtt[index] = attribute;

		}
		parentElement = parentElement->NextSiblingElement();
	}
}

void CDungeonMap::ParseTextObjects(TiXmlElement* rootNode) {
	/*< text index = "0"
		visible = "0"
		actuator = "0"
		complex = "0"
		text_data = "0"*/
	TiXmlElement* parentElement = rootNode->FirstChildElement();
	while (parentElement)
	{
		const char* parent = parentElement->Value();
		if (strcmp(parent, "text") == 0) // several existing
		{
			CTextAttributes textAttribute;
			int index;
			parentElement->QueryIntAttribute("index", &index);
			parentElement->QueryIntAttribute("visible", &textAttribute.visible);
			parentElement->QueryIntAttribute("text_data", &textAttribute.text_data);
			const char* strText = parentElement->GetText();
			textAttribute.text = strText;
			m_pTextInfos[index] = textAttribute;
			
		}
		parentElement = parentElement->NextSiblingElement();
	}
}

void CDungeonMap::ParseObjects(TiXmlElement* rootNode) {
	TiXmlElement* parentElement = rootNode->FirstChildElement();
	while (parentElement)
	{
		const char* parent = parentElement->Value();
		if (strcmp(parent, "doors") == 0)
		{
			ParseDoorObjects(parentElement);
		}
		else if (strcmp(parent, "miscellaneouses") == 0)
		{
			ParseMiscellaneousObjects(parentElement);
		}
		else if (strcmp(parent, "weapons") == 0)
		{
			ParseWeaponObjects(parentElement);
		}
		else if (strcmp(parent, "clothes") == 0)
		{
			ParseClothObjects(parentElement);
		}
		else if (strcmp(parent, "potions") == 0)
		{
			ParsePotionObjects(parentElement);
		}
		else if (strcmp(parent, "scrolls") == 0)
		{
			ParseScrollObjects(parentElement);
		}
		else if (strcmp(parent, "containers") == 0)
		{
			ParseContainerObjects(parentElement);
		}
		else if (strcmp(parent, "actuators") == 0)
		{
			ParseActuatorObjects(parentElement);
		}
		else if (strcmp(parent, "teleporters") == 0)
		{
			ParseTeleporterObjects(parentElement);
		}
		else if (strcmp(parent, "creatures") == 0)
		{
			ParseCreatureObjects(parentElement);
		}
		else if (strcmp(parent, "texts") == 0)
		{
			ParseTextObjects(parentElement);
		}
		parentElement = parentElement->NextSiblingElement();
	}
}

void CDungeonMap::ParseDungeon(TiXmlElement* rootNode) {
	int x, y;
	rootNode->QueryIntAttribute("start_x", &x);
	rootNode->QueryIntAttribute("start_y", &y);
	m_start.x = x;
	m_start.y = y;
	m_start.z = 0;	
	rootNode->QueryIntAttribute("number_of_doors", &m_countDoors);
	m_doorAtt = new CDoorAttributes[m_countDoors];
	rootNode->QueryIntAttribute("number_of_miscellaneous", &m_countMiscellaneous);
	m_miscellaneousAtt = new CMiscellaneousAttributes[m_countMiscellaneous];
	rootNode->QueryIntAttribute("number_of_weapons", &m_countWeapons);
	m_weaponAtt = new CWeaponAttributes[m_countWeapons];
	rootNode->QueryIntAttribute("number_of_potions", &m_countPotions);
	m_potionAtt = new CPotionAttributes[m_countPotions];
	rootNode->QueryIntAttribute("number_of_clothes", &m_countClothes);
	m_clothAtt = new CClothAttributes[m_countClothes];
	rootNode->QueryIntAttribute("number_of_scrolls", &m_countScrolls);
	m_scrollAtt = new CScrollAttributes[m_countScrolls];
	rootNode->QueryIntAttribute("number_of_containers", &m_countContainers);
	m_containerAtt = new CContainerAttributes[m_countContainers];
	rootNode->QueryIntAttribute("number_of_actuators", &m_countActuators);
	m_actuatorType = new int[m_countActuators];
	rootNode->QueryIntAttribute("number_of_teleporters", &m_countTeleporters);
	m_teleportAtt = new TeleporterAttributes[m_countTeleporters];
	rootNode->QueryIntAttribute("number_of_maps", &m_countFloors);
	m_wallDecorationTypes = new WallDecorationType * [m_countFloors];
	rootNode->QueryIntAttribute("number_of_creatures", &m_countCreatures);
	m_creatureAtt = new CCreatureAttributes[m_countCreatures];
	rootNode->QueryIntAttribute("number_of_texts", &m_countTexts);
	m_pTextInfos = new CTextAttributes[m_countTexts];

	const char* startDir = rootNode->Attribute("start_facing");
	if (strcmp(startDir, "North") == 0) m_startRicht = COMPASS_DIRECTION::NORTH;
	if (strcmp(startDir, "East") == 0) m_startRicht = COMPASS_DIRECTION::EAST;
	if (strcmp(startDir, "South") == 0) m_startRicht = COMPASS_DIRECTION::SOUTH;
	if (strcmp(startDir, "West") == 0) m_startRicht = COMPASS_DIRECTION::WEST;
	

	TiXmlElement* parentElement = rootNode->FirstChildElement();
	while (parentElement)
	{
		const char* parent = parentElement->Value();
		if (strcmp(parent, "maps") == 0)
		{
			ParseMaps(parentElement);
		}
		else if (strcmp(parent, "objects") == 0)
		{
			ParseObjects(parentElement);
		}
		parentElement = parentElement->NextSiblingElement();
	}
}

void CDungeonMap::LoadMap() {
	TiXmlBase::SetCondenseWhiteSpace(false);
	m_pDoc = new TiXmlDocument("Maps\\0000.DUNGEON [Dungeon].xml");
	bool loadOkay = m_pDoc->LoadFile();

	if (!loadOkay)
	{
		printf("Could not load test file 'Dungeon.xml'. Error='%s'. Exiting.\n", m_pDoc->ErrorDesc());
		return;
		exit(1);
	}
	TiXmlElement* rootElement = m_pDoc->FirstChildElement();
	const char* docname = rootElement->Value();
	if (strcmp(docname, "dungeon") == 0) {

		ParseDungeon(rootElement);
	}
}

WallDecorationType CDungeonMap::GetWallDecorationType(int ebene, int graphic)
{
	if (graphic > 0)
		return m_wallDecorationTypes[ebene][graphic - 1];
	else
		return None;
}


void CDungeonMap::SaveGame(CGrpHeld* pGrpHeroes) {
	TiXmlDocument doc; // ("Maps\\SaveGame.XML")
	TiXmlDeclaration* declaration = new TiXmlDeclaration("1.0", "ISO-8859-1", "");//Create DTD
	doc.LinkEndChild(declaration);
	TiXmlElement* dungeon = new TiXmlElement("dungeon");
	VEKTOR heroPos = pGrpHeroes->GetVector();
	dungeon->SetAttribute("start_x", heroPos.x);
	dungeon->SetAttribute("start_y", heroPos.y);
	dungeon->SetAttribute("start_z", heroPos.z);
	COMPASS_DIRECTION richt = pGrpHeroes->GetDirection();
	const char* dir = ( richt == COMPASS_DIRECTION::NORTH ? "North" :
						richt == COMPASS_DIRECTION::EAST ? "East" :
						richt == COMPASS_DIRECTION::SOUTH ? "South" : "West");
	dungeon->SetAttribute("start_facing", dir);

	TiXmlElement* heroes= new TiXmlElement("heroes");
	for (int id = 1; id < 5; id++) {
		SaveHero(heroes, id);
	}
	dungeon->LinkEndChild(heroes);

	TiXmlElement* maps = new TiXmlElement("maps");	
	for (int level = 0; level < m_countFloors; level++) {
		SaveMap(maps, level);
	}
	dungeon->LinkEndChild(maps);

	doc.LinkEndChild(dungeon);

	doc.SaveFile("Maps\\SaveGame.xml");

}

void CDungeonMap::SaveHero(TiXmlElement* heroes, int id) {
	CHeld* held = m_pGrpHelden->GetHero(id);
	if (held) {
		TiXmlElement* hero = new TiXmlElement("hero");
		hero->SetAttribute("index", id);
		for (int itemId = 0; itemId < 30; itemId++) {
			CItem* item = held->GetItemCarrying(itemId);
			if (item) {
				TiXmlElement* heroItem = new TiXmlElement("item");
				heroItem->SetAttribute("item", itemId);
				heroItem->SetAttribute("index", item->GetIndex());
				heroItem->SetAttribute("type", item->getItemType());
				hero->LinkEndChild(heroItem);
			}
		}
		heroes->LinkEndChild(hero);
	}
}

void CDungeonMap::SaveMap(TiXmlElement* maps, int level) {
	TiXmlElement* map = new TiXmlElement("map");
	maps->LinkEndChild(map);
	map->SetAttribute("index", level);
	TiXmlElement* tiles = new TiXmlElement("tiles");
	int tileIndex = 0;
	for (int y = 0; y < m_LevelHeight[level]; y++) {
		for (int x = 0; x < m_LevelWidth[level]; x++) {
			TiXmlElement* tile = new TiXmlElement("tile");
			tile->SetAttribute("index", tileIndex);
			
			CDoor* pDoor = m_pFeld[x][y][level]->HoleDoor();
			if (pDoor) {
				TiXmlElement* door = new TiXmlElement("door");
				door->SetAttribute("state", pDoor->getState());
				tile->LinkEndChild(door);
			}

			for (int subPos = 0; subPos < 4; subPos++) {
				std::deque<CActuator*> pActuators = m_pFeld[x][y][level]->GetActuator((COMPASS_DIRECTION)subPos);
				if (!pActuators.empty()) {
					TiXmlElement* actuators = new TiXmlElement("actuators");
					for (CActuator* pActuator : pActuators) {
						TiXmlElement* actuator = new TiXmlElement("actuator");
						actuator->SetAttribute("index", pActuator->GetIndex()); // Reihenfolge speichern reicht?
						actuator->SetAttribute("subPos", subPos);
						actuators->LinkEndChild(actuator);
					}
					tile->LinkEndChild(actuators);
				}
			}
			// items speichern - ersetzt Map, also alles speichern
			// Monstergruppen sind auch unter "items" einsortiert
			// eigene subPos Schleife, um alles in einem ITEM einzugliedern
			CGrpMonster* pGrpMonsters = m_pFeld[x][y][level]->GetMonsterGroup();
			TiXmlElement* items = new TiXmlElement("items");
			for (int subPos = 0; subPos < 4; subPos++) {
				std::deque<CItem*> pItems = m_pFeld[x][y][level]->GetItem((SUBPOS_ABSOLUTE)subPos);
				if (!pItems.empty() || pGrpMonsters) {
					if (pGrpMonsters) {
						TiXmlElement* creature = new TiXmlElement("creature");
						creature->SetAttribute("index", pGrpMonsters->GetIndex());
						creature->SetAttribute("subPos", subPos);
						for (int i=1; i<5; i++) {
							CMonster* monster = pGrpMonsters->GetMonster(i);
							if (monster && monster->HoleSubPosition() == subPos) {
								CString strHp;
								strHp.Format("hp-%i", i);
								creature->SetAttribute(strHp, (int)monster->Hp().Aktuell);
							}
						}
						items->LinkEndChild(creature);

					}
					for (CItem* pItem : pItems) {
						TiXmlElement* item = new TiXmlElement(pItem->getItemTypeString());
						item->SetAttribute("index", pItem->GetIndex());
						item->SetAttribute("position", subPos);
						items->LinkEndChild(item);
					}

				}
			}
			if (items->NoChildren()) 
				delete items; 
			else
				tile->LinkEndChild(items);
			tiles->LinkEndChild(tile);
			tileIndex++;
		}
	}
	map->LinkEndChild(tiles);
}


void CDungeonMap::LoadGame(CGrpHeld* pGrpHeroes) {
	TiXmlDocument doc(FILENAME);
	bool loadOkay = doc.LoadFile();

	if (!loadOkay)
	{
		printf("Could not load save game 'SaveGame.xml'. Error='%s'. Exiting.\n", doc.ErrorDesc());
		return;
	}
	TiXmlElement* rootElement = doc.FirstChildElement();
	if (strcmp(rootElement->Value(), "dungeon") == 0) {
		RestorePosition(rootElement, pGrpHeroes);
		TiXmlElement* section = rootElement->FirstChildElement();
		while (section) {
			if (strcmp(section->Value(), "maps") == 0) {
				LoadMaps(section);
			}
			if (strcmp(section->Value(), "heroes") == 0) {
				LoadHeroes(section);
			}
			section = section->NextSiblingElement();
		}
	}
}

void CDungeonMap::RestorePosition(TiXmlElement* rootElement, CGrpHeld* pGrpHeroes) {
	VEKTOR newPos;
	int x, y, z;
	rootElement->QueryIntAttribute("start_x", &x);
	rootElement->QueryIntAttribute("start_y", &y);
	rootElement->QueryIntAttribute("start_z", &z);
	newPos = VEKTOR{ x, y, z };
	pGrpHeroes->SetVector(newPos);

	const char* startDir = rootElement->Attribute("start_facing");
	COMPASS_DIRECTION richt;
	if (strcmp(startDir, "North") == 0) richt = COMPASS_DIRECTION::NORTH;
	if (strcmp(startDir, "East") == 0) richt = COMPASS_DIRECTION::EAST;
	if (strcmp(startDir, "South") == 0) richt = COMPASS_DIRECTION::SOUTH;
	if (strcmp(startDir, "West") == 0) richt = COMPASS_DIRECTION::WEST;
	pGrpHeroes->DrehenAbsolut(richt);
}

void CDungeonMap::LoadMaps(TiXmlElement* maps) {
	TiXmlElement* map = maps->FirstChildElement();
	while (map)
	{
		const char* mapId = map->Value();
		if (strcmp(mapId, "map") == 0)
		{
			LoadMap(map);
		}
		map = map->NextSiblingElement();
	}
}

void CDungeonMap::LoadHeroes(TiXmlElement* heroes) {
	TiXmlElement* hero = heroes->FirstChildElement();
	while (hero)
	{
		const char* heroId = hero->Value();
		if (strcmp(heroId, "hero") == 0)
		{
			LoadHero(hero);
		}
		hero = hero->NextSiblingElement();
	}
}

void CDungeonMap::LoadHero(TiXmlElement* hero) {
	int heroId;
	hero->QueryIntAttribute("index", &heroId);
	m_pGrpHelden->InitHeld(heroId);
	CHeld* held = m_pGrpHelden->GetActiveHero();
	TiXmlElement* heroItem = hero->FirstChildElement();
	while (heroItem) {
		int itemId, index, type;
		heroItem->QueryIntAttribute("item", &itemId);
		heroItem->QueryIntAttribute("index", &index);
		heroItem->QueryIntAttribute("type", &type);
		CWeapon* weapon;
		CMiscellaneous* misc;
		CCloth* cloth;
		CPotion* potion;
		CScroll* scroll;
		CContainer* container;
		switch (type) {
		case CItem::WeaponItem:
			weapon = new CWeapon(index, m_weaponAtt[index]);
			held->SwitchItemAt(itemId, (CItem*)weapon);
			break;
		case CItem::MiscItem:
			misc = new CMiscellaneous(index, m_miscellaneousAtt[index]);
			held->SwitchItemAt(itemId, (CItem*)misc);
			break;
		case CItem::ClothItem:
			cloth = new CCloth(index, m_clothAtt[index]);
			held->SwitchItemAt(itemId, (CItem*)cloth);
			break;
		case CItem::PotionItem:
			potion = new CPotion(index, m_potionAtt[index]);
			held->SwitchItemAt(itemId, (CItem*)potion);
			break;
		case CItem::ScrollItem:
			scroll = new CScroll(index, m_scrollAtt[index]);
			held->SwitchItemAt(itemId, (CItem*)scroll);
			break;
		case CItem::ContainerItem:
			container = new CContainer(index, m_containerAtt[index]);
			held->SwitchItemAt(itemId, (CItem*)container);
			break;
		}
		heroItem = heroItem->NextSiblingElement();
	}
}

void CDungeonMap::LoadMap(TiXmlElement* map) {
	int index;
	map->QueryIntAttribute("index", &index);
	
	TiXmlElement* tiles = map->FirstChildElement();
	if (strcmp(tiles->Value(), "tiles") == 0) {
		TiXmlElement* tile = tiles->FirstChildElement();
		while (tile) {
			LoadTile(tile, index);
			tile = tile->NextSiblingElement();
		}
	}
}

void CDungeonMap::LoadTile(TiXmlElement* tile, int mapIndex) {
	int index, state;
	tile->QueryIntAttribute("index", &index);
	int width = m_LevelWidth[mapIndex];
	int height = m_LevelHeight[mapIndex];
	int x = index % width;
	int y = (int)(index / width);
	CField* pField = m_pFeld[x][y][mapIndex];

	TiXmlElement* element = tile->FirstChildElement();
	while (element) {
		if (strcmp(element->Value(), "door") == 0) {
			element->QueryIntAttribute("state", &state);

			CDoor* pDoor = pField->HoleDoor();
			if (pDoor) {
				pDoor->SetState(state);
			}
		}
		if (strcmp(element->Value(), "actuators") == 0) {
			TiXmlElement* actuator = element->FirstChildElement();
			while (actuator) {
				if (strcmp(actuator->Value(), "actuator") == 0) {
					int actuatorId, subPos;
					actuator->QueryIntAttribute("index", &actuatorId);
					actuator->QueryIntAttribute("subPos", &subPos);
					std::deque<CActuator*> pActuators = pField->GetActuator((COMPASS_DIRECTION)subPos);
					if (pActuators.back()->GetIndex() != actuatorId) {
						pField->RotateActuators((COMPASS_DIRECTION)subPos);
					}
				}
				actuator = actuator->NextSiblingElement();
			}
		}
		ParseItems(element, VEKTOR{ x, y, mapIndex }, false);

		element = element->NextSiblingElement();
	}
}