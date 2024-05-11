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
	int readyAttack[4] = { 0,0,0,0 };
	int readyMove[4] = { 0,0,0,0 };
	CMonsterConst monsterInfo;
	int transCol;
};

