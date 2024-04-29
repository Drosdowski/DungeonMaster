#include "stdafx.h"
#include "..\..\resource.h"
#include "OituPic.h"

COituPic::COituPic(CDC* pDC) : CBasePictures(pDC)
{
	InitPics();
}

COituPic:: ~COituPic() {
	delete m_pOituAttack;
	delete m_pOituFront;
	delete m_pOituLeft;
	delete m_pOituRight;
	delete m_pOituBack;
}

void COituPic::InitPics() {

	LoadPic(m_pOituAttack, IDB_MONSTER_OITU_ATTACK);
	LoadPic(m_pOituFront, IDB_MONSTER_OITU_FRONT);
	LoadPic(m_pOituRight, IDB_MONSTER_OITU_RIGHT);
	LoadPicAndFlip(m_pOituLeft, IDB_MONSTER_OITU_RIGHT);
	LoadPic(m_pOituBack, IDB_MONSTER_OITU_BACK);
}

CBitmap* COituPic::GetOituPic(int index, bool attacking) {
	if (index == 0) {
		if (attacking) {
			return m_pOituAttack;
		}
		else {
			return m_pOituFront;
		}
	}
	if (index == 1) return m_pOituRight;
	if (index == 2) return m_pOituBack;
	if (index == 3) return m_pOituLeft;

	return NULL;
}