#pragma once
#include "Feld.h"

#define FELD_MAX_X 30
#define FELD_MAX_Y 30
#define FELD_MAX_Z 1


class CDungeonMap
{
public:
	CDungeonMap();
	~CDungeonMap();
	void DemoMap();
	void LoadMap();
	CField* GetField(int, int, int);
	CField* GetField(VEKTOR);

private:
	CField* m_pFeld[FELD_MAX_X][FELD_MAX_Y][FELD_MAX_Z];
};

