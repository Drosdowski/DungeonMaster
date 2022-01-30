#pragma once
#include "Monster.h"

class CSkelett : public CMonster
{
public:
	CSkelett(CPictures* pPictures, CDC* pDC);

	void InitValues();
	int GetIDB(int index);
};

