#include "stdafx.h"
#include "..\..\resource.h"
#include "OituPic.h"

COituPic::COituPic(CDC* pDC) : CBasePictures(pDC)
{
	InitPics();
}

COituPic:: ~COituPic() {
	for (int flip = 0; flip < 2; flip++)
	{
		delete m_pOituAttack[flip];
		delete m_pOituFront[flip];
	}
	delete m_pOituLeft;
	delete m_pOituRight;
	delete m_pOituBack;
}

void COituPic::InitPics() {
	LoadPic(m_pOituAttack[0], IDB_MONSTER_OITU_ATTACK);
	LoadPic(m_pOituFront[0], IDB_MONSTER_OITU_FRONT);

	LoadPicAndFlip(m_pOituAttack[1], IDB_MONSTER_OITU_ATTACK);
	LoadPicAndFlip(m_pOituFront[1], IDB_MONSTER_OITU_FRONT);
	LoadPic(m_pOituRight, IDB_MONSTER_OITU_RIGHT);
	LoadPicAndFlip(m_pOituLeft, IDB_MONSTER_OITU_RIGHT);
	LoadPic(m_pOituBack, IDB_MONSTER_OITU_BACK);
}

CBitmap* COituPic::GetOituPic(int index, bool attacking, int flip) {
	if (index == 0) {
		if (attacking) {
			return m_pOituAttack[flip];
		}
		else {
			return m_pOituFront[flip];
		}
	}
	if (index == 1) return m_pOituRight;
	if (index == 2) return m_pOituBack;
	if (index == 3) return m_pOituLeft;

	return NULL;
}