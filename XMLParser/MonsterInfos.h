#pragma once
#include "..\Consts\MonsterConst.h"

class TiXmlElement;
class CMonsterInfos
{
public:
	CMonsterInfos();
	~CMonsterInfos();

	CMonsterConst GetMonster(int index) { return monsterInfos[index]; };


private:
	void LoadMonsterInfos();
	void ParseMonsterInfos(TiXmlElement* element);
	void ParseMonster(TiXmlElement* element);

	CMonsterConst monsterInfos[29];

};

