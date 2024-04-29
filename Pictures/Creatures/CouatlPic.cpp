#include "stdafx.h"
#include "..\..\resource.h"
#include "CouatlPic.h"

CCouatlPic::CCouatlPic(CDC* pDC) : CBasePictures(pDC)
{
	InitPics();
}

CCouatlPic:: ~CCouatlPic() {
	delete m_pCouatlAttack;
	delete m_pCouatlFront;
	delete m_pCouatlLeft;
	delete m_pCouatlRight;
	delete m_pCouatlBack;
}

void CCouatlPic::InitPics() {

	LoadPic(m_pCouatlAttack, IDB_MONSTER_COUATL_ATTACK);
	LoadPic(m_pCouatlFront, IDB_MONSTER_COUATL_FRONT);
	LoadPic(m_pCouatlRight, IDB_MONSTER_COUATL_RIGHT);
	LoadPicAndFlip(m_pCouatlLeft, IDB_MONSTER_COUATL_RIGHT);
	LoadPic(m_pCouatlBack, IDB_MONSTER_COUATL_BACK);
}

CBitmap* CCouatlPic::GetCouatlPic(int index, bool attacking) {
	if (index == 0) {
		if (attacking) {
			return m_pCouatlAttack;
		}
		else {
			return m_pCouatlFront;
		}
	}
	if (index == 1) return m_pCouatlRight;
	if (index == 2) return m_pCouatlBack;
	if (index == 3) return m_pCouatlLeft;

	return NULL;
}