#include "stdafx.h"
#include "..\..\resource.h"
#include "RedDragonPic.h"

CRedDragonPic::CRedDragonPic(CDC* pDC) : CBasePictures(pDC)
{
	InitPics();
}

CRedDragonPic:: ~CRedDragonPic() {
	for (int flip = 0; flip < 2; flip++)
	{
		delete m_pRedDragonAttack[flip];
		delete m_pRedDragonFront[flip];
	}
	delete m_pRedDragonLeft;
	delete m_pRedDragonRight;
	delete m_pRedDragonBack;
}

void CRedDragonPic::InitPics() {
	LoadPic(m_pRedDragonAttack[0], IDB_MONSTER_REDDRAGON_ATTACK);
	LoadPic(m_pRedDragonFront[0], IDB_MONSTER_REDDRAGON_FRONT);

	LoadPicAndFlip(m_pRedDragonAttack[1], IDB_MONSTER_REDDRAGON_ATTACK);
	LoadPicAndFlip(m_pRedDragonFront[1], IDB_MONSTER_REDDRAGON_FRONT);
	LoadPic(m_pRedDragonRight, IDB_MONSTER_REDDRAGON_RIGHT);
	LoadPicAndFlip(m_pRedDragonLeft, IDB_MONSTER_REDDRAGON_RIGHT);
	LoadPic(m_pRedDragonBack, IDB_MONSTER_REDDRAGON_BACK);
}

CBitmap* CRedDragonPic::GetRedDragonPic(int index, bool attacking, int flip) {
	if (index == 0) {
		if (attacking) {
			return m_pRedDragonAttack[flip];
		}
		else {
			return m_pRedDragonFront[flip];
		}
	}
	if (index == 1) return m_pRedDragonRight;
	if (index == 2) return m_pRedDragonBack;
	if (index == 3) return m_pRedDragonLeft;

	return NULL;
}