#include "stdafx.h"
#include "SpecialTile\Decoration.h"
#include "TinyXML/tinyxml.h"
#include "Mobs/MobGroups/GrpHeld.h"
#include "Items/CMiscellaneous.h"
#include "CDungeonMap.h"

CDungeonMap::CDungeonMap()
{ 
	VEKTOR v{ 0,0,0 };

	m_pEdgeWall = new CField(v, FeldTyp::WALL, NULL);
	LoadMap();
	m_pGrpHelden = new CGrpHeld(m_start, m_startRicht);
}

CDungeonMap::~CDungeonMap()
{
	delete m_pEdgeWall;
	delete m_pGrpHelden;
	for (int z = 0; z < FELD_MAX_Z; z++)
		for (int i = 0; i < m_LevelWidth[z]; i++)
			for (int j = 0; j < m_LevelHeight[z]; j++) {
				delete m_pFeld[i][j][z];
			}
	delete m_doorType;
	delete m_miscellaneousType;
	delete m_miscellaneousSubtype;
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
	if (direction == 0)
		return new CField(pos, FeldTyp::STAIRS, CStairs::StairType::DOWN, (orientation != 0), NULL);
	else
		return new CField(pos, FeldTyp::STAIRS, CStairs::StairType::UP, (orientation != 0), NULL);
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
		return new CField(pos, FeldTyp::DOOR, CDoor::DoorType::Iron, (orientation != 0), NULL);
	else
		return new CField(pos, FeldTyp::DOOR, CDoor::DoorType::Wood, (orientation != 0), NULL);
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
		
	// 0 = Wall , 1 == Empty, 3 = Stair, 4 == Door
	if (type != 0 && type != 1 && type != 3 && type != 4)
	{
		type = 1; // Teleporter etc erstmal leer lassen
	}
	FeldTyp iFieldType = (FeldTyp)type;
	VEKTOR pos{ x, y, etage };

	if (iFieldType == FeldTyp::DOOR)
	{
		m_pFeld[x][y][etage] = ParseDoor(rootNode, pos);
	}
	else if (iFieldType == FeldTyp::STAIRS) {
		
		m_pFeld[x][y][etage] = ParseStairs(rootNode, pos);
	}		
	else
		m_pFeld[x][y][etage] = new CField(pos, iFieldType, NULL); // etage 1 / index 30 => m_levelWidth[1] kaputt!
	
	if (hasObjects == 1) {
		int msubtype, mtype = 0;
		TiXmlElement* parentElement = rootNode->FirstChildElement();
		while (parentElement)
		{
			const char* parent = parentElement->Value();
			if (strcmp(parent, "items") == 0)
			{ // 16851
				TiXmlElement* miscItem = parentElement->FirstChildElement();
				while (miscItem && strcmp(miscItem->Value(), "miscellaneous") == 0) 
				{
					int index, subPos;
					miscItem->QueryIntAttribute("index", &index);
					miscItem->QueryIntAttribute("position", &subPos);
					mtype = m_miscellaneousType[index];
					msubtype = m_miscellaneousSubtype[index];

					CMiscellaneous* misc = new CMiscellaneous(index, mtype, msubtype);
					m_pFeld[x][y][etage]->PutMisc(misc, (SUBPOS_ABSOLUTE)subPos);
					miscItem = miscItem->NextSiblingElement();
				}

			}
			parentElement = parentElement->NextSiblingElement();

		}
	}
}


void CDungeonMap::ParseTiles(TiXmlElement* rootNode, int etage) {
	TiXmlElement* parentElement = rootNode->FirstChildElement();
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
	TiXmlElement* parentElement = rootNode->FirstChildElement();
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

	const char* startDir = rootNode->Attribute("start_facing");
	if (strcmp(startDir, "North") == 0) m_startRicht = 0;
	if (strcmp(startDir, "East") == 0) m_startRicht = 1;
	if (strcmp(startDir, "South") == 0) m_startRicht = 2;
	if (strcmp(startDir, "West") == 0) m_startRicht = 3;
	

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
		m_pFeld[3][7][0]->InitMonsterGruppe(CMonster::MonsterTyp::SKELETT, 4, 0);
}
