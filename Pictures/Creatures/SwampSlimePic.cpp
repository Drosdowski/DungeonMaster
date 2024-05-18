#include "stdafx.h"
#include "..\..\resource.h"
#include "SwampSlimePic.h"


CSwampSlimePic::CSwampSlimePic(CDC* pDC) : CBasePictures(pDC)
{
	InitPics();
}

CSwampSlimePic:: ~CSwampSlimePic() {
	for (int flip = 0; flip < 2; flip++)
	{
		delete m_pSwampSlimeAttack[flip];
		delete m_pSwampSlimeFront[flip];
	}
}

void CSwampSlimePic::InitPics() {
	LoadPic(m_pSwampSlimeAttack[0], IDB_MONSTER_SWAMPSLIME_ATTACK);
	LoadPic(m_pSwampSlimeFront[0], IDB_MONSTER_SWAMPSLIME_FRONT);

	LoadPicAndFlip(m_pSwampSlimeAttack[1], IDB_MONSTER_SWAMPSLIME_ATTACK);
	LoadPicAndFlip(m_pSwampSlimeFront[1], IDB_MONSTER_SWAMPSLIME_FRONT);
}

CBitmap* CSwampSlimePic::GetSwampSlimePic(bool attacking, int flip) {
	if (attacking) {
		return m_pSwampSlimeAttack[flip];
	}
	else {
		return m_pSwampSlimeFront[flip];
	}
}

