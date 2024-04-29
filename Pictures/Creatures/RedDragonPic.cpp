#include "stdafx.h"
#include "..\..\resource.h"
#include "RedDragonPic.h"

CRedDragonPic::CRedDragonPic(CDC* pDC) : CBasePictures(pDC)
{
	InitPics();
}

CRedDragonPic:: ~CRedDragonPic() {
	delete m_pRedDragonAttack;
	delete m_pRedDragonFront;
	delete m_pRedDragonLeft;
	delete m_pRedDragonRight;
	delete m_pRedDragonBack;
}

void CRedDragonPic::InitPics() {

	LoadPic(m_pRedDragonAttack, IDB_MONSTER_REDDRAGON_ATTACK);
	LoadPic(m_pRedDragonFront, IDB_MONSTER_REDDRAGON_FRONT);
	LoadPic(m_pRedDragonRight, IDB_MONSTER_REDDRAGON_RIGHT);
	LoadPicAndFlip(m_pRedDragonLeft, IDB_MONSTER_REDDRAGON_RIGHT);
	LoadPic(m_pRedDragonBack, IDB_MONSTER_REDDRAGON_BACK);
}

CBitmap* CRedDragonPic::GetRedDragonPic(int index, bool attacking) {
	if (index == 0) {
		if (attacking) {
			return m_pRedDragonAttack;
		}
		else {
			return m_pRedDragonFront;
		}
	}
	if (index == 1) return m_pRedDragonRight;
	if (index == 2) return m_pRedDragonBack;
	if (index == 3) return m_pRedDragonLeft;

	return NULL;
}