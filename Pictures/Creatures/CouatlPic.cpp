#include "stdafx.h"
#include "..\..\resource.h"
#include "CouatlPic.h"

CCouatlPic::CCouatlPic(CDC* pDC) : CBasePictures(pDC)
{
	InitPics();
}

CCouatlPic:: ~CCouatlPic() {
	for (int flip = 0; flip < 2; flip++)
	{
		delete m_pCouatlAttack[flip];
		delete m_pCouatlFront[flip];
	}
	delete m_pCouatlLeft;
	delete m_pCouatlRight;
	delete m_pCouatlBack;
}

void CCouatlPic::InitPics() {

	LoadPic(m_pCouatlAttack[0], IDB_MONSTER_COUATL_ATTACK);
	LoadPic(m_pCouatlFront[0], IDB_MONSTER_COUATL_FRONT);
	LoadPic(m_pCouatlRight, IDB_MONSTER_COUATL_RIGHT);
	LoadPicAndFlip(m_pCouatlLeft, IDB_MONSTER_COUATL_RIGHT);
	LoadPic(m_pCouatlBack, IDB_MONSTER_COUATL_BACK);

	LoadPicAndFlip(m_pCouatlAttack[1], IDB_MONSTER_COUATL_ATTACK);
	LoadPicAndFlip(m_pCouatlFront[1], IDB_MONSTER_COUATL_FRONT);
}

CBitmap* CCouatlPic::GetCouatlPic(int index, bool attacking, int flip) {
	if (index == 0) {
		if (attacking) {
			return m_pCouatlAttack[flip];
		}
		else {
			return m_pCouatlFront[flip];
		}
	}
	if (index == 1) return m_pCouatlRight;
	if (index == 2) return m_pCouatlBack;
	if (index == 3) return m_pCouatlLeft;

	return NULL;
}