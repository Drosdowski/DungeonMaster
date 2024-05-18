#include "stdafx.h"
#include "..\..\resource.h"
#include "GhostPic.h"

CGhostPic::CGhostPic(CDC* pDC) : CBasePictures(pDC)
{
	InitPics();
}

CGhostPic:: ~CGhostPic() {
	for (int flip = 0; flip < 2; flip++)
	{
		delete m_pGhostAttack[flip];
		delete m_pGhostFront[flip];
	}
}

void CGhostPic::InitPics() {
	LoadPic(m_pGhostAttack[0], IDB_MONSTER_GHOST_ATTACK);
	LoadPic(m_pGhostFront[0], IDB_MONSTER_GHOST_FRONT);

	LoadPicAndFlip(m_pGhostAttack[1], IDB_MONSTER_GHOST_ATTACK);
	LoadPicAndFlip(m_pGhostFront[1], IDB_MONSTER_GHOST_FRONT);
}

CBitmap* CGhostPic::GetGhostPic(bool attacking, int flip) {
	if (attacking) {
		return m_pGhostAttack[flip];
	}
	else {
		return m_pGhostFront[flip];
	}
}

