#include "stdafx.h"
#include "..\..\resource.h"
#include "RockPilePic.h"

CRockPilePic::CRockPilePic(CDC* pDC) : CBasePictures(pDC)
{
	InitPics();
}

CRockPilePic:: ~CRockPilePic() {
	delete m_pRockPileAttack;
	delete m_pRockPileFront;
}


void CRockPilePic::InitPics() {

	LoadPic(m_pRockPileAttack, IDB_MONSTER_ROCKPILE_ATTACK);
	LoadPic(m_pRockPileFront, IDB_MONSTER_ROCKPILE_FRONT);
}

CBitmap* CRockPilePic::GetRockPilePic(bool attacking) {
	if (attacking) {
		return m_pRockPileAttack;
	}
	else {
		return m_pRockPileFront;
	}
}

