#include "..\Mobs\Monster.h"
#pragma once
class CCreatureAttributes
{
public:
	COMPASS_DIRECTION direction;
	CMonster::MonsterTyp type;
	int count;
	int position[4];
	int hitPoints[4];

};

