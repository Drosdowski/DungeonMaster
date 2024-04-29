#include "stdafx.h"
#include "..\..\resource.h"
#include "StoneGolemPic.h"

CStoneGolemPic::CStoneGolemPic(CDC* pDC) : CBasePictures(pDC)
{
	InitPics();
}

CStoneGolemPic:: ~CStoneGolemPic() {
	delete m_pStoneGolemAttack;
	delete m_pStoneGolemFront;
	delete m_pStoneGolemLeft;
	delete m_pStoneGolemRight;
	delete m_pStoneGolemBack;
}

void CStoneGolemPic::InitPics() {

	LoadPic(m_pStoneGolemAttack, IDB_MONSTER_STONEGOLEM_ATTACK);
	LoadPic(m_pStoneGolemFront, IDB_MONSTER_STONEGOLEM_FRONT);
	LoadPic(m_pStoneGolemRight, IDB_MONSTER_STONEGOLEM_RIGHT);
	LoadPicAndFlip(m_pStoneGolemLeft, IDB_MONSTER_STONEGOLEM_RIGHT);
	LoadPic(m_pStoneGolemBack, IDB_MONSTER_STONEGOLEM_BACK);
}

CBitmap* CStoneGolemPic::GetStoneGolemPic(int index, bool attacking) {
	if (index == 0) {
		if (attacking) {
			return m_pStoneGolemAttack;
		}
		else {
			return m_pStoneGolemFront;
		}
	}
	if (index == 1) return m_pStoneGolemRight;
	if (index == 2) return m_pStoneGolemBack;
	if (index == 3) return m_pStoneGolemLeft;

	return NULL;
}