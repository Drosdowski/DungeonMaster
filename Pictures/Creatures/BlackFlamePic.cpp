#include "stdafx.h"
#include "..\..\resource.h"
#include "BlackFlamePic.h"

CBlackFlamePic::CBlackFlamePic(CDC* pDC) : CBasePictures(pDC)
{
	InitPics();
}

CBlackFlamePic:: ~CBlackFlamePic() {
	for (int flip = 0; flip < 2; flip++)
	{
		delete m_pBlackFlameAttack[flip];
		delete m_pBlackFlameFront[flip];
	}
}

void CBlackFlamePic::InitPics() {
	LoadPic(m_pBlackFlameAttack[0], IDB_MONSTER_BLACKFLAME_ATTACK);
	LoadPic(m_pBlackFlameFront[0], IDB_MONSTER_BLACKFLAME_FRONT);

	LoadPicAndFlip(m_pBlackFlameAttack[1], IDB_MONSTER_BLACKFLAME_ATTACK);
	LoadPicAndFlip(m_pBlackFlameFront[1], IDB_MONSTER_BLACKFLAME_FRONT);
}

CBitmap* CBlackFlamePic::GetBlackFlamePic(bool attacking, int flip) {
	if (attacking) {
		return m_pBlackFlameAttack[flip];
	}
	else {
		return m_pBlackFlameFront[flip];
	}
}

