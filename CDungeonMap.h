#pragma once
#include "Feld.h"
#include "Items/CActuator.h"
#include "SpecialTile/CTeleporterAttributes.h"
#include "SpecialTile/CCreatureAttributes.h"
#include "SpecialTile/CDoorAttributes.h"

#define FELD_MAX_X 32
#define FELD_MAX_Y 32
#define FELD_MAX_Z 14

class TiXmlElement;
class CGrpHeld;
class CDungeonMap
{
public:
	CDungeonMap();
	~CDungeonMap();
	void LoadMap();
	CField* GetField(int, int, int);
	CField* GetField(VEKTOR);
	int GetMaxWidth(int ebene) { return m_LevelWidth[ebene]; }
	int GetMaxHeight(int ebene) { return m_LevelHeight[ebene]; }
	CPoint GetOffset(int ebene);
	VEKTOR GetStart() { return m_start; }
	COMPASS_DIRECTION GetStartDirection() { return m_startRicht; }
	CGrpHeld* GetHeroes() { return m_pGrpHelden; }
	WallDecorationType GetWallDecorationType(int ebene, int graphic);


private:

	void ParseActuatorObjects(TiXmlElement* rootNode);
	void ParseCreatureObjects(TiXmlElement* rootNode);
	void ParseDoorObjects(TiXmlElement* rootNode);
	void ParseMiscellaneousesObjects(TiXmlElement* rootNode);
	void ParseObjects(TiXmlElement* rootNode);
	void ParseTeleporterObjects(TiXmlElement* rootNode);

	void ParseMaps(TiXmlElement* rootNode);
	void ParseMap(TiXmlElement* rootNode, int etage);
	void ParseDungeon(TiXmlElement* rootNode);
	void ParseWallDecorationGraphics(TiXmlElement* rootNode, int etage);
	void ParseWallDecorationGraphic(TiXmlElement* rootNode, int etage);
	void ParseTiles(TiXmlElement* rootNode, int etage);
	void ParseTile(TiXmlElement* rootNode, int etage);
	void ParseItems(TiXmlElement* rootNode, VEKTOR coords);
	void ParseActuator(TiXmlElement* miscItem, VEKTOR coords);
	void ParseMiscellaneous(TiXmlElement* rootNode, VEKTOR coords);
	void ParseFloorDecoration(TiXmlElement* miscItem, VEKTOR coords);
	void ParseWallDecoration(TiXmlElement* miscItem, VEKTOR coords);
	void ParseCreature(TiXmlElement* miscItem, VEKTOR coords);

	CField* ParseDoor(TiXmlElement* rootNode, VEKTOR pos);
	CField* ParseStairs(TiXmlElement* rootNode, VEKTOR pos);
	CField* ParsePit(TiXmlElement* rootNode, VEKTOR pos);
	CField* ParseTeleport(TiXmlElement* rootNode, VEKTOR pos);
	CField* m_pFeld[FELD_MAX_X][FELD_MAX_Y][FELD_MAX_Z];
	CField* m_pEdgeWall;
	int m_LevelWidth[FELD_MAX_Z];
	int m_LevelHeight[FELD_MAX_Z];
	int m_offsetX[FELD_MAX_Z]; // shifting when changing floor level
	int m_offsetY[FELD_MAX_Z]; // shifting when changing floor level
	VEKTOR m_start;
	COMPASS_DIRECTION m_startRicht;
	int m_countDoors;
	int m_countMiscellaneous;
	int m_countActuators;
	int m_countTeleporters;
	int m_countCreatures;
	int m_countFloors;
	CGrpHeld* m_pGrpHelden;

	// dynamic arrays
	int* m_miscellaneousType;
	int* m_miscellaneousSubtype;
	int* m_actuatorType;
	CDoorAttributes* m_doorAtt;
	TeleporterAttributes* m_teleportAtt;
	CCreatureAttributes* m_creatureAtt;
	WallDecorationType** m_wallDecorationTypes;
	//CActuator::ActionTypes* m_actionType;
	//VEKTOR* m_actionTarget;



};

