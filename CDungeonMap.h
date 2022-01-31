#pragma once
#include "Feld.h"

#define FELD_MAX_X 30
#define FELD_MAX_Y 30
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



private:
	void ParseTile(TiXmlElement* rootNode, int etage);
	void ParseTiles(TiXmlElement* rootNode, int etage);
	void ParseMap(TiXmlElement* rootNode, int etage);
	void ParseMaps(TiXmlElement* rootNode);
	CField* m_pFeld[FELD_MAX_X][FELD_MAX_Y][FELD_MAX_Z];
	int m_LevelWidth[FELD_MAX_Z];
	int m_LevelHeight[FELD_MAX_Z];
};

