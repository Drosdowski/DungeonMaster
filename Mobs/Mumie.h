#pragma once
#include "Monster.h"

class CPictures;
class CMumie : public CMonster
{
public:
	CMumie();

	void InitValues();
	int GetIDB(int index);
};

