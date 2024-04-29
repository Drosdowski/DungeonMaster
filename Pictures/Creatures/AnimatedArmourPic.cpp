#include "stdafx.h"
#include "..\..\resource.h"
#include "AnimatedArmourPic.h"

CAnimatedArmourPic::CAnimatedArmourPic(CDC* pDC) : CBasePictures(pDC)
{
	InitPics();
}

CAnimatedArmourPic:: ~CAnimatedArmourPic() {
	delete m_pAnimatedArmourAttack;
	delete m_pAnimatedArmourFront;
	delete m_pAnimatedArmourLeft;
	delete m_pAnimatedArmourRight;
	delete m_pAnimatedArmourBack;
}

void CAnimatedArmourPic::InitPics() {

	LoadPic(m_pAnimatedArmourAttack, IDB_MONSTER_ANIMATEDARMOUR_ATTACK);
	LoadPic(m_pAnimatedArmourFront, IDB_MONSTER_ANIMATEDARMOUR_FRONT);
	LoadPic(m_pAnimatedArmourRight, IDB_MONSTER_ANIMATEDARMOUR_RIGHT);
	LoadPicAndFlip(m_pAnimatedArmourLeft, IDB_MONSTER_ANIMATEDARMOUR_RIGHT);
	LoadPic(m_pAnimatedArmourBack, IDB_MONSTER_ANIMATEDARMOUR_BACK);
}

CBitmap* CAnimatedArmourPic::GetAnimatedArmourPic(int index, bool attacking) {
	if (index == 0) {
		if (attacking) {
			return m_pAnimatedArmourAttack;
		}
		else {
			return m_pAnimatedArmourFront;
		}
	}
	if (index == 1) return m_pAnimatedArmourRight;
	if (index == 2) return m_pAnimatedArmourBack;
	if (index == 3) return m_pAnimatedArmourLeft;

	return NULL;
}