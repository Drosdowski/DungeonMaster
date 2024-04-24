#include "stdafx.h"
#include "..\..\resource.h"
#include "BlackFlamePic.h"

CBlackFlamePic::CBlackFlamePic(CDC* pDC) : CBasePictures(pDC)
{
	InitPics();
}

CBlackFlamePic:: ~CBlackFlamePic() {
	delete m_pBlackFlameAttack;
	delete m_pBlackFlameFront;
}


void CBlackFlamePic::InitPics() {

	LoadPic(m_pBlackFlameAttack, IDB_MONSTER_BLACKFLAME_ATTACK);
	LoadPic(m_pBlackFlameFront, IDB_MONSTER_BLACKFLAME_FRONT);
}

CBitmap* CBlackFlamePic::GetBlackFlamePic(bool attacking) {
	if (attacking) {
		return m_pBlackFlameAttack;
	}
	else {
		return m_pBlackFlameFront;
	}
}

