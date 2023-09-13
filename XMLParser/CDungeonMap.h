#pragma once
#include "../Feld.h"
#include "../Items/CActuator.h"
#include "../Attributes/TeleporterAttributes.h"
#include "../Attributes/CreatureAttributes.h"
#include "../Attributes/DoorAttributes.h"
#include "../Attributes/WeaponAttributes.h"
#include "../Attributes/ClothAttributes.h"
#include "../Attributes/PotionAttributes.h"
#include "../Attributes/MiscellaneousAttributes.h"
#include "../Attributes/ScrollAttributes.h"
#include "../Attributes/ContainerAttributes.h"
#include "../Attributes/TextAttributes.h"
#include <XMLParser/ItemInfos.h>
#include <XMLParser/MonsterInfos.h>

#define FELD_MAX_X 32
#define FELD_MAX_Y 32
#define FELD_MAX_Z 14

#define FILENAME "Maps\\SaveGame.xml"

class TiXmlElement;
class TiXmlDocument;
class CGrpHeld;
class CDungeonMap
{
public:
	CDungeonMap(CItemInfos* pItemInfos, CMonsterInfos* pMonsterInfos);
	~CDungeonMap();
	void LoadMap();
	CField* GetField(int, int, int);
	CField* GetField(VEKTOR);
	int GetMaxWidth(int ebene) { return m_LevelWidth[ebene]; }
	int GetMaxHeight(int ebene) { return m_LevelHeight[ebene]; }
	int GetLevelDifficulty(int ebene) { return m_LevelDiff[ebene]; }
	CPoint GetOffset(int ebene);
	VEKTOR GetStart() { return m_start; }
	COMPASS_DIRECTION GetStartDirection() { return m_startRicht; }
	CGrpHeld* GetHeroes() { return m_pGrpHelden; }
	WallDecorationType GetWallDecorationType(int ebene, int graphic);
	void SaveGame(CGrpHeld* pGrpHeroes);
	void LoadGame(CGrpHeld* pGrpHeroes);
	CString GetText(int id);

private:

	void ParseActuatorObjects(TiXmlElement* rootNode);
	void ParseCreatureObjects(TiXmlElement* rootNode);
	void ParseDoorObjects(TiXmlElement* rootNode);
	void ParseMiscellaneousObjects(TiXmlElement* rootNode);
	void ParseWeaponObjects(TiXmlElement* rootNode);
	void ParseClothObjects(TiXmlElement* rootNode);
	void ParsePotionObjects(TiXmlElement* rootNode);
	void ParseScrollObjects(TiXmlElement* rootNode);
	void ParseContainerObjects(TiXmlElement* rootNode);
	void ParseObjects(TiXmlElement* rootNode);
	void ParseTeleporterObjects(TiXmlElement* rootNode);
	void ParseTextObjects(TiXmlElement* rootNode);

	void ParseMaps(TiXmlElement* rootNode);
	void ParseMap(TiXmlElement* rootNode, int etage);
	void ParseDungeon(TiXmlElement* rootNode);
	void ParseWallDecorationGraphics(TiXmlElement* rootNode, int etage);
	void ParseWallDecorationGraphic(TiXmlElement* rootNode, int etage);
	void ParseFloorDecorationGraphics(TiXmlElement* rootNode, int etage);
	void ParseFloorDecorationGraphic(TiXmlElement* rootNode, int etage);
	void ParseDoorDecorationGraphics(TiXmlElement* rootNode, int etage);
	void ParseDoorDecorationGraphic(TiXmlElement* rootNode, int etage);
	void ParseTiles(TiXmlElement* rootNode, int etage);
	void ParseTile(TiXmlElement* rootNode, int etage);
	void ParseItems(TiXmlElement* rootNode, VEKTOR coords, bool initDungeon);
	void ParseActuator(TiXmlElement* miscItem, VEKTOR coords);
	void ParseMiscellaneous(TiXmlElement* rootNode, VEKTOR coords);
	void ParseWeapons(TiXmlElement* rootNode, VEKTOR coords);
	void ParseCloth(TiXmlElement* rootNode, VEKTOR coords);
	void ParsePotions(TiXmlElement* rootNode, VEKTOR coords);
	void ParseScrolls(TiXmlElement* rootNode, VEKTOR coords);
	void ParseContainers(TiXmlElement* rootNode, VEKTOR coords);
	void ParseText(TiXmlElement* rootNode, VEKTOR coords);
	void ParseFloorDecoration(TiXmlElement* miscItem, VEKTOR coords);
	void ParseWallDecoration(TiXmlElement* miscItem, VEKTOR coords);
	void ParseCreature(TiXmlElement* miscItem, VEKTOR coords);
	void RestorePosition(TiXmlElement* rootElement, CGrpHeld* pGrpHeroes);	
	void SaveMap(TiXmlElement* maps, int level);
	void LoadMap(TiXmlElement* maps);
	void SaveHero(TiXmlElement* heroes, int id);
	void LoadHero(TiXmlElement* hero);
	void LoadHeroes(TiXmlElement* heroes);
	void LoadMaps(TiXmlElement* maps);
	void LoadTile(TiXmlElement* tile, int index);

	CField* ParseDoor(TiXmlElement* rootNode, VEKTOR pos, int etage);
	CField* ParseStairs(TiXmlElement* rootNode, VEKTOR pos);
	CField* ParsePit(TiXmlElement* rootNode, VEKTOR pos);
	CField* ParseTeleport(TiXmlElement* rootNode, VEKTOR pos);
	CField* ParseTrickWall(TiXmlElement* rootNode, VEKTOR pos);

	CField* m_pFeld[FELD_MAX_X][FELD_MAX_Y][FELD_MAX_Z];
	CField* m_pEdgeWall;
	int m_LevelWidth[FELD_MAX_Z];
	int m_LevelHeight[FELD_MAX_Z];
	int m_LevelDiff[FELD_MAX_Z];
	int m_offsetX[FELD_MAX_Z]; // shifting when changing floor level
	int m_offsetY[FELD_MAX_Z]; // shifting when changing floor level
	VEKTOR m_start;
	COMPASS_DIRECTION m_startRicht;
	int m_countDoors;
	int m_countMiscellaneous;
	int m_countWeapons;
	int m_countClothes;
	int m_countPotions;
	int m_countScrolls;
	int m_countContainers;
	int m_countActuators;
	int m_countTeleporters;
	int m_countCreatures;
	int m_countFloors;
	int m_countTexts;
	CGrpHeld* m_pGrpHelden;
	bool saveGameExists;

	// dynamic arrays
	CMiscellaneousAttributes* m_miscellaneousAtt = NULL;
	CWeaponAttributes* m_weaponAtt = NULL;
	CClothAttributes* m_clothAtt = NULL;
	CPotionAttributes* m_potionAtt = NULL;
	CScrollAttributes* m_scrollAtt = NULL;
	CContainerAttributes* m_containerAtt = NULL;

	int* m_actuatorType;
	CDoorAttributes* m_doorAtt = NULL;
	TeleporterAttributes* m_teleportAtt = NULL;
	CCreatureAttributes* m_creatureAtt = NULL;
	CTextAttributes* m_pTextInfos = NULL;
	WallDecorationType** m_wallDecorationTypes = NULL;
	FloorDecorationType** m_floorDecorationTypes = NULL;
	DoorDecorationType** m_doorDecorationTypes = NULL;
	CItemInfos* m_pItemInfos = NULL;
	CMonsterInfos* m_pMonsterInfos = NULL;

	TiXmlDocument* m_pDoc = NULL;
};

