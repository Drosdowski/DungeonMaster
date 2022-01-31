#include "stdafx.h"
#include "Decoration.h"
#include "tinyxml.h"
#include "CDungeonMap.h"

CDungeonMap::CDungeonMap()
{ 
}

CDungeonMap::~CDungeonMap()
{
	for (int i = 0; i < FELD_MAX_X; i++)
		for (int j = 0; j < FELD_MAX_Y; j++) // Weil Baum
		{
			delete m_pFeld[i][j][0];
		}
}

CField* CDungeonMap::GetField(int x, int y, int z) {
	return m_pFeld[x][y][z];
}

CField* CDungeonMap::GetField(VEKTOR v) {
	return m_pFeld[v.x][v.y][v.z];
}


void CDungeonMap::DemoMap() {
	for (int i = 0; i < FELD_MAX_X; i++)
		for (int j = 0; j < FELD_MAX_Y; j++)
		{
			CField::FeldTyp iFieldType = ((((j % 4) != 0) || (i == FELD_MAX_X / 2))
				&& (j > 3) && (j < FELD_MAX_Y - 3)
				&& (i > 3) && (i < FELD_MAX_X - 3)
				) ? CField::FeldTyp::EMPTY : CField::FeldTyp::WALL;

			if ((i == FELD_MAX_X / 2) && (j == FELD_MAX_Y / 2 + 1)) {
				iFieldType = CField::FeldTyp::DOOR;
			}
			VEKTOR pos; pos.x = i; pos.y = j; pos.z = 0;

			CFieldDecoration* deco[4];
			for (int b = 0; b < 4; b++) {
				if (i % 4 == 1) {
					deco[b] = new CFieldDecoration(Switch);
				}
				else if (i % 4 == 3) {
					deco[b] = new CFieldDecoration(Fountain);
				}
				else {
					deco[b] = new CFieldDecoration(None);
				}
			}

			if (iFieldType == CField::FeldTyp::DOOR)
				m_pFeld[i][j][0] = new CField(pos, iFieldType, CDoor::DoorType::Iron, true, deco);
			else
				m_pFeld[i][j][0] = new CField(pos, iFieldType, deco);
			/*if ((i == FELD_MAX_X / 2) && (j == FELD_MAX_Y / 2 + 1)) {
				m_pFeld[i][j][0]->InitMonsterGruppe(m_pPictures, pDC, CMonster::MonsterTyp::MUMIE, 1);
			}
			else*/

			if ((i == FELD_MAX_X / 2) && (j == FELD_MAX_Y / 2 + 5)) {
				m_pFeld[i][j][0]->InitMonsterGruppe(CMonster::MonsterTyp::SKELETT, 1);
			}
		}
}
