#pragma once
#include "Monster.h"

class CPictures;
class CMumie : public CMonster
{
public:
	CMumie(CPictures* pPictures, CDC* pDC);

	void InitValues();
	int GetIDB(int index);
};

