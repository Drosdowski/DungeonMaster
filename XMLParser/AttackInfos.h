#pragma once
#include "..\Consts\AttackConst.h"


class TiXmlElement;
class CAttackInfos
{
public:
	CAttackInfos();
	~CAttackInfos();

	CAttackConst GetAttack(int index) { return attackInfos[index]; };

private:
	void LoadAttackInfos();
	void ParseAttackInfos(TiXmlElement* element);
	void ParseAttack(TiXmlElement* element);

	CAttackConst attackInfos[44];
};

