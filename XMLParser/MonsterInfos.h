#pragma once
#include "..\Consts\MonsterConst.h"

class TiXmlElement;
class CMonsterInfos
{
public:
	CMonsterInfos();
	~CMonsterInfos();

	CMonsterConst GetMonsterInfo(int index) { return m_pMonsterInfos[index]; };


private:
	void LoadMonsterInfos();
	void ParseMonsterInfos(TiXmlElement* element);
	void ParseMonster(TiXmlElement* element);

	CMonsterConst m_pMonsterInfos[29];

};

