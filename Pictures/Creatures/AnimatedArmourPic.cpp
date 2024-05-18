#include "stdafx.h"
#include "..\..\resource.h"
#include "AnimatedArmourPic.h"

CAnimatedArmourPic::CAnimatedArmourPic(CDC* pDC) : CBasePictures(pDC)
{
	InitPics();
}

CAnimatedArmourPic:: ~CAnimatedArmourPic() {
	for (int flip = 0; flip < 2; flip++)
	{
		delete m_pAnimatedArmourAttack[flip];
		delete m_pAnimatedArmourFront[flip];
	}
	delete m_pAnimatedArmourLeft;
	delete m_pAnimatedArmourRight;
	delete m_pAnimatedArmourBack;
}

void CAnimatedArmourPic::InitPics() {

	LoadPic(m_pAnimatedArmourAttack[0], IDB_MONSTER_ANIMATEDARMOUR_ATTACK);
	LoadPic(m_pAnimatedArmourFront[0], IDB_MONSTER_ANIMATEDARMOUR_FRONT);
	LoadPic(m_pAnimatedArmourRight, IDB_MONSTER_ANIMATEDARMOUR_RIGHT);
	LoadPicAndFlip(m_pAnimatedArmourLeft, IDB_MONSTER_ANIMATEDARMOUR_RIGHT);
	LoadPic(m_pAnimatedArmourBack, IDB_MONSTER_ANIMATEDARMOUR_BACK);

	LoadPicAndFlip(m_pAnimatedArmourAttack[1], IDB_MONSTER_ANIMATEDARMOUR_ATTACK);
	LoadPicAndFlip(m_pAnimatedArmourFront[1], IDB_MONSTER_ANIMATEDARMOUR_FRONT);
}

CBitmap* CAnimatedArmourPic::GetAnimatedArmourPic(int index, bool attacking, int flip) {
	if (index == 0) {
		if (attacking) {
			return m_pAnimatedArmourAttack[flip];
		}
		else {
			return m_pAnimatedArmourFront[flip];
		}
	}
	if (index == 1) return m_pAnimatedArmourRight;
	if (index == 2) return m_pAnimatedArmourBack;
	if (index == 3) return m_pAnimatedArmourLeft;

	return NULL;
}