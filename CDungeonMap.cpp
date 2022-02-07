#include "stdafx.h"
#include "SpecialTile\Decoration.h"
#include "TinyXML/tinyxml.h"
#include "CDungeonMap.h"

CDungeonMap::CDungeonMap()
{ 
	CFieldDecoration* deco[4];
	for (int b = 0; b < 4; b++) {
		deco[b] = new CFieldDecoration(None);
	}
	VEKTOR v; v.x = 0; v.y = 0;v.z = 0;

	m_pEdgeWall = new CField(v, CField::FeldTyp::WALL, deco);
	LoadMap();
}

CDungeonMap::~CDungeonMap()
{
	delete m_pEdgeWall;
	for (int z = 0; z < FELD_MAX_Z; z++)
		for (int i = 0; i < m_LevelWidth[z]; i++)
			for (int j = 0; j < m_LevelHeight[z]; j++) {
				delete m_pFeld[i][j][z];
			}
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

void CDungeonMap::ParseTile(TiXmlElement* rootNode, int etage) {
	const char* parent = rootNode->Value();
	int index;
	rootNode->QueryIntAttribute("index", &index);
	int x = index % m_LevelWidth[etage];
	int y = (int)(index / m_LevelWidth[etage]);
	int type;
	int orientation;
	int direction;
	rootNode->QueryIntAttribute("type", &type);
	// 0 = Wall , 1 == Empty, 3 = Stair, 4 == Door
	if (type != 0 && type != 1 && type != 3 && type != 4)
	{
		type = 1; // Teleporter etc erstmal leer lassen
	}
	CField::FeldTyp iFieldType = (CField::FeldTyp)type;
	VEKTOR pos; pos.x = x; pos.y = y; pos.z = etage;

	CFieldDecoration* deco[4];
	for (int b = 0; b < 4; b++) {
		deco[b] = new CFieldDecoration(None);
	}

	if (iFieldType == CField::FeldTyp::DOOR)
	{
		rootNode->QueryIntAttribute("orientation", &orientation);		
		m_pFeld[x][y][etage] = new CField(pos, iFieldType, CDoor::DoorType::Iron, (orientation != 0), deco);
	}
	else if (iFieldType == CField::FeldTyp::STAIRS) {
		rootNode->QueryIntAttribute("direction", &direction);
		rootNode->QueryIntAttribute("orientation", &orientation);
		if (direction == 0)
			m_pFeld[x][y][etage] = new CField(pos, iFieldType, CStairs::StairType::DOWN, (orientation != 0), deco); 
		else
			m_pFeld[x][y][etage] = new CField(pos, iFieldType, CStairs::StairType::UP, (orientation != 0), deco);
	}		
	else
		m_pFeld[x][y][etage] = new CField(pos, iFieldType, deco); // etage 1 / index 30 => m_levelWidth[1] kaputt!
	
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
	TiXmlElement* parentElement = rootElement->FirstChildElement();
	while (parentElement)
	{
		const char* parent = parentElement->Value();
		if (strcmp(parent, "maps") == 0)
		{
			ParseMaps(parentElement);
		}
		parentElement = parentElement->NextSiblingElement();
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
		m_pFeld[3][7][0]->InitMonsterGruppe(CMonster::MonsterTyp::SKELETT, 4);
}
