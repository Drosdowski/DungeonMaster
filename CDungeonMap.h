#pragma once
#include "Feld.h"

#define FELD_MAX_X 32
#define FELD_MAX_Y 32
#define FELD_MAX_Z 14

class TiXmlElement;
class CDungeonMap
{
public:
	CDungeonMap();
	~CDungeonMap();
	void DemoMap();
	void LoadMap();
	CField* GetField(int, int, int);
	CField* GetField(VEKTOR);
	int GetMaxWidth(int ebene) { return m_LevelWidth[ebene]; }
	int GetMaxHeight(int ebene) { return m_LevelHeight[ebene]; }
	CPoint GetOffset(int ebene);

private:
	void ParseTile(TiXmlElement* rootNode, int etage);
	void ParseTiles(TiXmlElement* rootNode, int etage);
	void ParseMap(TiXmlElement* rootNode, int etage);
	void ParseMaps(TiXmlElement* rootNode);
	CField* ParseDoor(TiXmlElement* rootNode, VEKTOR pos);
	CField* m_pFeld[FELD_MAX_X][FELD_MAX_Y][FELD_MAX_Z];
	CField* m_pEdgeWall;
	int m_LevelWidth[FELD_MAX_Z];
	int m_LevelHeight[FELD_MAX_Z];
	int m_offsetX[FELD_MAX_Z]; // shifting when changing floor level
	int m_offsetY[FELD_MAX_Z]; // shifting when changing floor level
};

