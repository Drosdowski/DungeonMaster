#include "stdafx.h"
#include "..\..\resource.h"
#include "GigglerPic.h"

CGigglerPic::CGigglerPic(CDC* pDC) : CBasePictures(pDC)
{
	InitPics();
}

CGigglerPic:: ~CGigglerPic() {
	delete m_pGigglerAttack;
	delete m_pGigglerFront;
	delete m_pGigglerLeft;
	delete m_pGigglerRight;
	delete m_pGigglerBack;
}

void CGigglerPic::InitPics() {

	LoadPic(m_pGigglerAttack, IDB_MONSTER_GIGGLER_ATTACK);
	LoadPic(m_pGigglerFront, IDB_MONSTER_GIGGLER_FRONT);
	LoadPic(m_pGigglerRight, IDB_MONSTER_GIGGLER_RIGHT);
	LoadPicAndFlip(m_pGigglerLeft, IDB_MONSTER_GIGGLER_RIGHT);
	LoadPic(m_pGigglerBack, IDB_MONSTER_GIGGLER_BACK);
}

CBitmap* CGigglerPic::GetGigglerPic(int index, bool attacking) {
	if (index == 0) {
		if (attacking) {
			return m_pGigglerAttack;
		}
		else {
			return m_pGigglerFront;
		}
	}
	if (index == 1) return m_pGigglerRight;
	if (index == 2) return m_pGigglerBack;
	if (index == 3) return m_pGigglerLeft;

	return NULL;
}