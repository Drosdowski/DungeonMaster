#include "stdafx.h"
#include "..\..\resource.h"
#include "ScreamerPic.h"

CScreamerPic::CScreamerPic(CDC* pDC) : CBasePictures(pDC)
{
	InitPics();
}

CScreamerPic:: ~CScreamerPic() {
	for (int flip = 0; flip < 2; flip++)
	{
		delete m_pScreamerAttack[flip];
		delete m_pScreamerFront[flip];
	}
}

void CScreamerPic::InitPics() {

	LoadPic(m_pScreamerAttack[0], IDB_MONSTER_SCREAMER_ATTACK);
	LoadPic(m_pScreamerFront[0], IDB_MONSTER_SCREAMER_FRONT);
	LoadPicAndFlip(m_pScreamerAttack[1], IDB_MONSTER_SCREAMER_ATTACK);
	LoadPicAndFlip(m_pScreamerFront[1], IDB_MONSTER_SCREAMER_FRONT);
}

CBitmap* CScreamerPic::GetScreamerPic(bool attacking, int flip) {
	if (attacking) {
		return m_pScreamerAttack[flip];
	}
	else {
		return m_pScreamerFront[flip];
	}
}

