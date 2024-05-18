#include "stdafx.h"
#include "..\..\resource.h"
#include "GigglerPic.h"

CGigglerPic::CGigglerPic(CDC* pDC) : CBasePictures(pDC)
{
	InitPics();
}

CGigglerPic:: ~CGigglerPic() {
	for (int flip = 0; flip < 2; flip++)
	{
		delete m_pGigglerAttack[flip];
		delete m_pGigglerFront[flip];
	}
	delete m_pGigglerLeft;
	delete m_pGigglerRight;
	delete m_pGigglerBack;
}

void CGigglerPic::InitPics() {
	LoadPic(m_pGigglerAttack[0], IDB_MONSTER_GIGGLER_ATTACK);
	LoadPic(m_pGigglerFront[0], IDB_MONSTER_GIGGLER_FRONT);

	LoadPicAndFlip(m_pGigglerAttack[1], IDB_MONSTER_GIGGLER_ATTACK);
	LoadPicAndFlip(m_pGigglerFront[1], IDB_MONSTER_GIGGLER_FRONT);
	LoadPic(m_pGigglerRight, IDB_MONSTER_GIGGLER_RIGHT);
	LoadPicAndFlip(m_pGigglerLeft, IDB_MONSTER_GIGGLER_RIGHT);
	LoadPic(m_pGigglerBack, IDB_MONSTER_GIGGLER_BACK);
}

CBitmap* CGigglerPic::GetGigglerPic(int index, bool attacking, int flip) {
	if (index == 0) {
		if (attacking) {
			return m_pGigglerAttack[flip];
		}
		else {
			return m_pGigglerFront[flip];
		}
	}
	if (index == 1) return m_pGigglerRight;
	if (index == 2) return m_pGigglerBack;
	if (index == 3) return m_pGigglerLeft;

	return NULL;
}