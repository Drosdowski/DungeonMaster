#include "stdafx.h"
#include "..\..\resource.h"
#include "DemonPic.h"

CDemonPic::CDemonPic(CDC* pDC) : CBasePictures(pDC)
{
	InitPics();
}

CDemonPic:: ~CDemonPic() {
	for (int flip = 0; flip < 2; flip++)
	{
		delete m_pDemonAttack[flip];
		delete m_pDemonFront[flip];
	}
	delete m_pDemonLeft;
	delete m_pDemonRight;
	delete m_pDemonBack;
}

void CDemonPic::InitPics() {
	LoadPic(m_pDemonAttack[0], IDB_MONSTER_DEMON_ATTACK);
	LoadPic(m_pDemonFront[0], IDB_MONSTER_DEMON_FRONT);

	LoadPicAndFlip(m_pDemonAttack[1], IDB_MONSTER_DEMON_ATTACK);
	LoadPicAndFlip(m_pDemonFront[1], IDB_MONSTER_DEMON_FRONT);
	LoadPic(m_pDemonRight, IDB_MONSTER_DEMON_RIGHT);
	LoadPicAndFlip(m_pDemonLeft, IDB_MONSTER_DEMON_RIGHT);
	LoadPic(m_pDemonBack, IDB_MONSTER_DEMON_BACK);
}

CBitmap* CDemonPic::GetDemonPic(int index, bool attacking, int flip) {
	if (index == 0) {
		if (attacking) {
			return m_pDemonAttack[flip];
		}
		else {
			return m_pDemonFront[flip];
		}
	}
	if (index == 1) return m_pDemonRight;
	if (index == 2) return m_pDemonBack;
	if (index == 3) return m_pDemonLeft;

	return NULL;
}