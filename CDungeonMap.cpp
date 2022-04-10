#include "stdafx.h"
#include <sstream>
#include <string>
#include "TinyXML/tinyxml.h"
#include "Mobs/MobGroups/GrpHeld.h"
#include "Mobs/MobGroups/GrpMonster.h"
#include "Items\Decoration.h"
#include "Items/CMiscellaneous.h"
#include "SpecialTile/CTeleporter.h"
#include "CDungeonMap.h"

CDungeonMap::CDungeonMap()
{ 
	VEKTOR v{ 0,0,0 };

	m_pEdgeWall = new CField(v, FeldTyp::WALL);
	LoadMap();
	m_pGrpHelden = new CGrpHeld(m_start, m_startRicht);
}

CDungeonMap::~CDungeonMap()
{
	delete m_pEdgeWall;
	delete m_pGrpHelden;
	for (int z = 0; z < FELD_MAX_Z; z++) {
		if (m_wallDecorationTypes[z])
			delete m_wallDecorationTypes[z];
		for (int i = 0; i < m_LevelWidth[z]; i++)
			for (int j = 0; j < m_LevelHeight[z]; j++) {
				delete m_pFeld[i][j][z];
			}
	}
	delete m_wallDecorationTypes;
		
	delete m_doorType;
	delete m_miscellaneousType;
	delete m_miscellaneousSubtype;
	delete m_actuatorType;
	delete m_teleportAtt;	
	delete m_creatureAtt;
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
	CStairs* stair;
	if (direction == 0)
		stair = new CStairs(CStairs::StairType::DOWN, (orientation != 0));
	else
		stair = new CStairs(CStairs::StairType::UP, (orientation != 0));

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
				CTeleporter* teleItem = new CTeleporter(m_teleportAtt[index], is_visible, is_open);
				return new CField(pos, teleItem);
			}

		}
		parentElement = parentElement->NextSiblingElement();
	}
	
	return NULL;
}


CField* CDungeonMap::ParseDoor(TiXmlElement* rootNode, VEKTOR pos) {
	int orientation, type;
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
				type = m_doorType[index];
			}

		}
		parentElement = parentElement->NextSiblingElement();

	}
	if (type == 0)
		return new CField(pos, new CDoor(CDoor::DoorType::Iron, (orientation != 0)));
	else
		return new CField(pos, new CDoor(CDoor::DoorType::Wood, (orientation != 0)));
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
	int allowDecoration;
	rootNode->QueryIntAttribute("allow_decoration", &allowDecoration);

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
	else
		m_pFeld[x][y][etage] = new CField(pos, iFieldType); // etage 1 / index 30 => m_levelWidth[1] kaputt!
	
	if (hasObjects == 1 || allowDecoration == 1) {
		ParseItems(rootNode, VEKTOR{x ,y, etage});
	}
}

void CDungeonMap::ParseItems(TiXmlElement* rootNode, VEKTOR coords) {
	TiXmlElement* parentElement = rootNode->FirstChildElement();
	while (parentElement)
	{
		const char* parent = parentElement->Value();
		if (strcmp(parent, "items") == 0)
		{ // 16851
			TiXmlElement* miscItem = parentElement->FirstChildElement();
			while (miscItem)
			{
				if (strcmp(miscItem->Value(), "miscellaneous") == 0) {

					ParseMiscellaneous(miscItem, coords);
				}
				else if (strcmp(miscItem->Value(), "actuator") == 0) {
					ParseActuator(miscItem, coords);
				}
				else if (strcmp(miscItem->Value(), "random_floor_decoration") == 0) {
					ParseFloorDecoration(miscItem, coords);
				}
				else if (strcmp(miscItem->Value(), "creature") == 0) {
					ParseCreature(miscItem, coords);
				}
			
				miscItem = miscItem->NextSiblingElement();
			}


		}
		parentElement = parentElement->NextSiblingElement();

	}
}

void CDungeonMap::ParseMiscellaneous(TiXmlElement* miscItem, VEKTOR coords) {
	int msubtype, mtype = 0;
	int index, subPos;
	miscItem->QueryIntAttribute("index", &index);
	miscItem->QueryIntAttribute("position", &subPos);
	mtype = m_miscellaneousType[index];
	msubtype = m_miscellaneousSubtype[index];

	CMiscellaneous* misc = new CMiscellaneous(index, (CMiscellaneous::ItemType) mtype, msubtype);
	m_pFeld[coords.x][coords.y][coords.z]->PutMisc(misc, (SUBPOS_ABSOLUTE)subPos);
}

void CDungeonMap::ParseFloorDecoration(TiXmlElement* decoItem, VEKTOR coords) {
	int graphic;
	decoItem->QueryIntAttribute("graphic", &graphic);
	CFieldDecoration* deco = new CFieldDecoration((FloorDecorationType)graphic);
	m_pFeld[coords.x][coords.y][coords.z]->PutFloorDeco(deco);

}

void CDungeonMap::ParseCreature(TiXmlElement* creatureItem, VEKTOR coords) {
	int index, position;
	creatureItem->QueryIntAttribute("index", &index);
	creatureItem->QueryIntAttribute("position", &position);

	CCreatureAttributes attribute = m_creatureAtt[index];
	CGrpMonster* pGrpMonster = new CGrpMonster(coords, attribute);

	m_pFeld[coords.x][coords.y][coords.z]->SetMonsterGroup(pGrpMonster);

	TiXmlElement* parentElement = creatureItem->FirstChildElement();
	while (parentElement)
	{
		const char* parent = parentElement->Value();
		if (strcmp(parent, "items") == 0)
		{
			TiXmlElement* monsterItem = parentElement->FirstChildElement();
			if (monsterItem) {
				// todo  monster with items
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
	int index, position, type, graphic, data, once_only;
	VEKTOR target = coords;
	CActuator::ActionTypes actionType;
	CActuator::ActionTarget actionTarget;
	actuatorItem->QueryIntAttribute("index", &index);
	actuatorItem->QueryIntAttribute("position", &position);
	
	// todo ab hier children
	TiXmlElement* actuatorAttributes = actuatorItem->FirstChildElement();
	while (actuatorAttributes)
	{
		if (strcmp(actuatorAttributes->Value(), "action_type") == 0) {
			const char* strActionType = actuatorAttributes->GetText();
			if (strcmp(strActionType, "Set") == 0) actionType = CActuator::Set;
			if (strcmp(strActionType, "Clear") == 0) actionType = CActuator::Clear;
			if (strcmp(strActionType, "Hold") == 0) actionType = CActuator::Hold;
			if (strcmp(strActionType, "Toggle") == 0) actionType = CActuator::Toggle;
		}
		else if (strcmp(actuatorAttributes->Value(), "action_target") == 0) {
			const char* strActionTarget = actuatorAttributes->GetText();
			if (strcmp(strActionTarget, "remote") == 0) actionTarget = CActuator::Remote;
			if (strcmp(strActionTarget, "local") == 0) actionTarget = CActuator::Local;
		}
		else if (strcmp(actuatorAttributes->Value(), "type") == 0) {
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

		actuatorAttributes = actuatorAttributes->NextSiblingElement();
	}

	//WallDecorationType graphicType = graphic > 0 ? m_wallDecorationTypes[graphic, coords.z] : None;
	//if (graphicType < 0 || graphicType > 255) graphicType = None; 
	CActuator* actuator = new CActuator(index, (COMPASS_DIRECTION)position, target, actionType, actionTarget, type, data, graphic, once_only);
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
		if (strcmp(parent, "tiles") == 0)
		{
			ParseTiles(parentElement, etage);
		}
		else if (strcmp(parent, "wall_decoration_graphics") == 0)
		{
			m_wallDecorationTypes[etage] = new WallDecorationType[15];
			ParseWallDecorationGraphics(parentElement, etage);
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
			int index, type;
			parentElement->QueryIntAttribute("index", &index);
			parentElement->QueryIntAttribute("type", &type);
			m_doorType[index] = type; // todo mehr attribute zulassen - knopf, ...
		}
		parentElement = parentElement->NextSiblingElement();
	}
}

void CDungeonMap::ParseMiscellaneousesObjects(TiXmlElement* rootNode) {
	TiXmlElement* parentElement = rootNode->FirstChildElement();
	while (parentElement)
	{
		const char* parent = parentElement->Value();
		if (strcmp(parent, "miscellaneous") == 0) // several existing
		{
			int index, subtype, type;
			parentElement->QueryIntAttribute("index", &index);
			parentElement->QueryIntAttribute("subtype", &subtype);
			parentElement->QueryIntAttribute("type", &type);
			m_miscellaneousType[index] = type;
			m_miscellaneousSubtype[index] = subtype;

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
			attribute.type = (CMonster::MonsterTyp)type;
			parentElement->QueryIntAttribute("number_of_creatures", &attribute.count);
			for (int monsterId = 1; monsterId <= attribute.count; monsterId++) {
				parentElement->QueryIntAttribute("position_" + monsterId, &attribute.position[attribute.count]);
				parentElement->QueryIntAttribute("hit_point_" + monsterId, &attribute.hitPoints[attribute.count]);
			}
			const char* facing = parentElement->Attribute("facing");
			if (strcmp(facing, "North")) attribute.direction = NORTH;
			if (strcmp(facing, "East")) attribute.direction = EAST;
			if (strcmp(facing, "South")) attribute.direction = SOUTH;
			if (strcmp(facing, "West")) attribute.direction = WEST;

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
			attribute.rotation = rotation_type == "Relative" ? TeleporterAttributes::RotationType::Relative : TeleporterAttributes::RotationType::Absolute;
			const char* scope = parentElement->Attribute("scope");
			if (strcmp(scope, "All"))  attribute.scope = TeleporterAttributes::Scope::All;
			if (strcmp(scope, "Creatures"))  attribute.scope = TeleporterAttributes::Scope::Creatures;
			if (strcmp(scope, "Items"))  attribute.scope = TeleporterAttributes::Scope::Items;
			if (strcmp(scope, "Items_Party"))  attribute.scope = TeleporterAttributes::Scope::Items_Party;
			
			parentElement->QueryIntAttribute("sound", &attribute.sound);
			m_teleportAtt[index] = attribute;

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
			ParseMiscellaneousesObjects(parentElement);
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
	m_doorType = new int[m_countDoors];
	rootNode->QueryIntAttribute("number_of_miscellaneous", &m_countMiscellaneous);
	m_miscellaneousType = new int[m_countMiscellaneous];
	m_miscellaneousSubtype = new int[m_countMiscellaneous];
	rootNode->QueryIntAttribute("number_of_actuators", &m_countActuators);	
	m_actuatorType = new int[m_countActuators];
	rootNode->QueryIntAttribute("number_of_teleporters", &m_countTeleporters);
	m_teleportAtt = new TeleporterAttributes[m_countTeleporters];
	rootNode->QueryIntAttribute("number_of_maps", &m_countFloors);
	m_wallDecorationTypes = new WallDecorationType * [m_countFloors];
	rootNode->QueryIntAttribute("number_of_creatures", &m_countCreatures);
	m_creatureAtt = new CCreatureAttributes[m_countCreatures];

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
	TiXmlDocument doc("Maps\\0000.DUNGEON [Dungeon].xml");
	bool loadOkay = doc.LoadFile();

	if (!loadOkay)
	{
		printf("Could not load test file 'demotest.xml'. Error='%s'. Exiting.\n", doc.ErrorDesc());
		exit(1);
	}
	TiXmlElement* rootElement = doc.FirstChildElement();
	const char* docname = rootElement->Value();
	if (strcmp(docname, "dungeon") == 0) {

		ParseDungeon(rootElement);
	}

}

void CDungeonMap::DemoMap() {
/*	m_LevelWidth[0] = FELD_MAX_X;
	m_LevelHeight[0] = FELD_MAX_Y;
	for (int i = 0; i < m_LevelWidth[0]; i++)
		for (int j = 0; j < m_LevelHeight[0]; j++)
		{
			CField::FeldTyp iFieldType = ((((j % 4) != 0) || (i == m_LevelWidth[0] / 2))
				&& (j > 3) && (j < m_LevelHeight[0] - 3)
				&& (i > 3) && (i < m_LevelWidth[0] - 3)
				) ? CField::FeldTyp::EMPTY : CField::FeldTyp::WALL;

			if ((i == m_LevelWidth[0] / 2) && (j == m_LevelHeight[0] / 2 + 1)) {
				iFieldType = CField::FeldTyp::DOOR;
			}
			VEKTOR pos; pos.x = i; pos.y = j; pos.z = 0;

			CFieldDecoration* deco[4];
			for (int b = 0; b < 4; b++) {
				if (i % 4 == 1) {
					deco[b] = new CFieldDecoration(Switch);
				}
				else if (i % 4 == 3) {
					deco[b] = new CFieldDecoration(Fountain);
				}
				else {
					deco[b] = new CFieldDecoration(None);
				}
			}

			if (iFieldType == CField::FeldTyp::DOOR)
				m_pFeld[i][j][0] = new CField(pos, iFieldType, CDoor::DoorType::Iron, true, deco);
			else
				m_pFeld[i][j][0] = new CField(pos, iFieldType, deco);
			//if ((i == m_LevelWidth[0] / 2) && (j == m_LevelHeight[0] / 2 + 1)) {
				//m_pFeld[i][j][0]->InitMonsterGruppe(m_pPictures, pDC, CMonster::MonsterTyp::MUMIE, 1);
			//}
			//else

			if ((i == m_LevelWidth[0] / 2) && (j == m_LevelHeight[0] / 2 + 5)) {
				m_pFeld[i][j][0]->InitMonsterGruppe(CMonster::MonsterTyp::SKELETT, 1);
			}
		}
		*/
		m_pFeld[3][7][0]->InitMonsterGruppe(CMonster::MonsterTyp::SKELETT, 4, COMPASS_DIRECTION::NORTH);
}

WallDecorationType CDungeonMap::GetWallDecorationType(int ebene, int graphic)
{
	if (graphic > 0)
		return m_wallDecorationTypes[ebene][graphic - 1];
	else
		return None;
}
