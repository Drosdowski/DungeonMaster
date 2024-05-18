#include "stdafx.h"
#include "..\..\resource.h"
#include "StoneGolemPic.h"

CStoneGolemPic::CStoneGolemPic(CDC* pDC) : CBasePictures(pDC)
{
	InitPics();
}

CStoneGolemPic:: ~CStoneGolemPic() {
	for (int flip = 0; flip < 2; flip++)
	{
		delete m_pStoneGolemAttack[flip];
		delete m_pStoneGolemFront[flip];
	}
	delete m_pStoneGolemLeft;
	delete m_pStoneGolemRight;
	delete m_pStoneGolemBack;
}

void CStoneGolemPic::InitPics() {
	LoadPic(m_pStoneGolemAttack[0], IDB_MONSTER_STONEGOLEM_ATTACK);
	LoadPic(m_pStoneGolemFront[0], IDB_MONSTER_STONEGOLEM_FRONT);

	LoadPicAndFlip(m_pStoneGolemAttack[1], IDB_MONSTER_STONEGOLEM_ATTACK);
	LoadPicAndFlip(m_pStoneGolemFront[1], IDB_MONSTER_STONEGOLEM_FRONT);
	LoadPic(m_pStoneGolemRight, IDB_MONSTER_STONEGOLEM_RIGHT);
	LoadPicAndFlip(m_pStoneGolemLeft, IDB_MONSTER_STONEGOLEM_RIGHT);
	LoadPic(m_pStoneGolemBack, IDB_MONSTER_STONEGOLEM_BACK);
}

CBitmap* CStoneGolemPic::GetStoneGolemPic(int index, bool attacking, int flip) {
	if (index == 0) {
		if (attacking) {
			return m_pStoneGolemAttack[flip];
		}
		else {
			return m_pStoneGolemFront[flip];
		}
	}
	if (index == 1) return m_pStoneGolemRight;
	if (index == 2) return m_pStoneGolemBack;
	if (index == 3) return m_pStoneGolemLeft;

	return NULL;
}