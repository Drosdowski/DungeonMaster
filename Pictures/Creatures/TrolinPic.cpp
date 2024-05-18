#include "stdafx.h"
#include "..\..\resource.h"
#include "TrolinPic.h"

CTrolinPic::CTrolinPic(CDC* pDC) : CBasePictures(pDC)
{
	InitPics();
}

CTrolinPic:: ~CTrolinPic() {
	for (int flip = 0; flip < 2; flip++)
	{
		delete m_pTrolinAttack[flip];
		delete m_pTrolinFront[flip];
	}
	delete m_pTrolinLeft;
	delete m_pTrolinRight;
	delete m_pTrolinBack;
}

void CTrolinPic::InitPics() {
	LoadPic(m_pTrolinAttack[0], IDB_MONSTER_TROLIN_ATTACK);
	LoadPic(m_pTrolinFront[0], IDB_MONSTER_TROLIN_FRONT);

	LoadPicAndFlip(m_pTrolinAttack[1], IDB_MONSTER_TROLIN_ATTACK);
	LoadPicAndFlip(m_pTrolinFront[1], IDB_MONSTER_TROLIN_FRONT);
	LoadPic(m_pTrolinRight, IDB_MONSTER_TROLIN_RIGHT);
	LoadPicAndFlip(m_pTrolinLeft, IDB_MONSTER_TROLIN_RIGHT);
	LoadPic(m_pTrolinBack, IDB_MONSTER_TROLIN_BACK);
}

CBitmap* CTrolinPic::GetTrolinPic(int index, bool attacking, int flip) {
	if (index == 0) {
		if (attacking) {
			return m_pTrolinAttack[flip];
		}
		else {
			return m_pTrolinFront[flip];
		}
	}
	if (index == 1) return m_pTrolinRight;
	if (index == 2) return m_pTrolinBack;
	if (index == 3) return m_pTrolinLeft;

	return NULL;
}

