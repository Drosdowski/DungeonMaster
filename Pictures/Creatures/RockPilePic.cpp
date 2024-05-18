#include "stdafx.h"
#include "..\..\resource.h"
#include "RockPilePic.h"

CRockPilePic::CRockPilePic(CDC* pDC) : CBasePictures(pDC)
{
	InitPics();
}

CRockPilePic:: ~CRockPilePic() {
	for (int flip = 0; flip < 2; flip++)
	{
		delete m_pRockPileAttack[flip];
		delete m_pRockPileFront[flip];
	}
}

void CRockPilePic::InitPics() {
	LoadPic(m_pRockPileAttack[0], IDB_MONSTER_ROCKPILE_ATTACK);
	LoadPic(m_pRockPileFront[0], IDB_MONSTER_ROCKPILE_FRONT);

	LoadPicAndFlip(m_pRockPileAttack[1], IDB_MONSTER_ROCKPILE_ATTACK);
	LoadPicAndFlip(m_pRockPileFront[1], IDB_MONSTER_ROCKPILE_FRONT);
}

CBitmap* CRockPilePic::GetRockPilePic(bool attacking, int flip) {
	if (attacking) {
		return m_pRockPileAttack[flip];
	}
	else {
		return m_pRockPileFront[flip];
	}
}

