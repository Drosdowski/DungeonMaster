#include "..\Consts\MonsterConst.h"
#pragma once
class CCreatureAttributes
{
public:

	COMPASS_DIRECTION direction;
	MonsterTyp type;
	int count;
	int position[4];
	int hitPoints[4];
	int ready[4];
	CMonsterConst monsterInfo;
	int transCol;
};

