#include "stdafx.h"
#include "..\..\resource.h"
#include "CMummyPic.h"

CMummyPic::CMummyPic(CDC* pDC) : CBasePictures(pDC)
{
	InitPics();
}

CMummyPic:: ~CMummyPic() {
	delete m_pMummyAttack;
	delete m_pMummyFront;
	delete m_pMummyLeft;
	delete m_pMummyRight;
	delete m_pMummyBack;
}


void CMummyPic::InitPics() {

	LoadPic(m_pMummyAttack, IDB_MONSTER_MUMMY_ATTACK);
	LoadPic(m_pMummyFront, IDB_MONSTER_MUMMY_FRONT);
	LoadPic(m_pMummyRight, IDB_MONSTER_MUMMY_RIGHT);
	LoadPicAndFlip(m_pMummyLeft, IDB_MONSTER_MUMMY_RIGHT);
	LoadPic(m_pMummyBack, IDB_MONSTER_MUMMY_BACK);
}

CBitmap* CMummyPic::GetMummyPic(int richt, bool attacking) {
	if (richt == 0) {
		if (attacking) {
			return m_pMummyAttack;
		}
		else {
			return m_pMummyFront;
		}
	}
	if (richt == 1) return m_pMummyRight;
	if (richt == 2) return m_pMummyBack;
	if (richt == 3) return m_pMummyLeft;

	return NULL;
}

