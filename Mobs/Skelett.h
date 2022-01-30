#pragma once
#include "Monster.h"

class CSkelett : public CMonster
{
public:
	CSkelett();

	void InitValues();
	int GetIDB(int index);
};

