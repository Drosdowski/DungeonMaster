#include "stdafx.h"
#include "..\..\resource.h"
#include "DemonPic.h"

CDemonPic::CDemonPic(CDC* pDC) : CBasePictures(pDC)
{
	InitPics();
}

CDemonPic:: ~CDemonPic() {
	delete m_pDemonAttack;
	delete m_pDemonFront;
	delete m_pDemonLeft;
	delete m_pDemonRight;
	delete m_pDemonBack;
}

void CDemonPic::InitPics() {

	LoadPic(m_pDemonAttack, IDB_MONSTER_DEMON_ATTACK);
	LoadPic(m_pDemonFront, IDB_MONSTER_DEMON_FRONT);
	LoadPic(m_pDemonRight, IDB_MONSTER_DEMON_RIGHT);
	LoadPicAndFlip(m_pDemonLeft, IDB_MONSTER_DEMON_RIGHT);
	LoadPic(m_pDemonBack, IDB_MONSTER_DEMON_BACK);
}

CBitmap* CDemonPic::GetDemonPic(int index, bool attacking) {
	if (index == 0) {
		if (attacking) {
			return m_pDemonAttack;
		}
		else {
			return m_pDemonFront;
		}
	}
	if (index == 1) return m_pDemonRight;
	if (index == 2) return m_pDemonBack;
	if (index == 3) return m_pDemonLeft;

	return NULL;
}