#include "stdafx.h"
#include "..\..\resource.h"
#include "MummyPic.h"

CMummyPic::CMummyPic(CDC* pDC) : CBasePictures(pDC)
{
	InitPics();
}

CMummyPic:: ~CMummyPic() {
	for (int flip = 0; flip < 2; flip++)
	{
		delete m_pMummyAttack[flip];
		delete m_pMummyFront[flip];
	}
	delete m_pMummyLeft;
	delete m_pMummyRight;
	delete m_pMummyBack;
}

void CMummyPic::InitPics() {
	LoadPic(m_pMummyAttack[0], IDB_MONSTER_MUMMY_ATTACK);
	LoadPic(m_pMummyFront[0], IDB_MONSTER_MUMMY_FRONT);

	LoadPicAndFlip(m_pMummyAttack[1], IDB_MONSTER_MUMMY_ATTACK);
	LoadPicAndFlip(m_pMummyFront[1], IDB_MONSTER_MUMMY_FRONT);
	LoadPic(m_pMummyRight, IDB_MONSTER_MUMMY_RIGHT);
	LoadPicAndFlip(m_pMummyLeft, IDB_MONSTER_MUMMY_RIGHT);
	LoadPic(m_pMummyBack, IDB_MONSTER_MUMMY_BACK);
}

CBitmap* CMummyPic::GetMummyPic(int richt, bool attacking, int flip) {
	if (richt == 0) {
		if (attacking) {
			return m_pMummyAttack[flip];
		}
		else {
			return m_pMummyFront[flip];
		}
	}
	if (richt == 1) return m_pMummyRight;
	if (richt == 2) return m_pMummyBack;
	if (richt == 3) return m_pMummyLeft;

	return NULL;
}

