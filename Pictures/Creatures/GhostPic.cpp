#include "stdafx.h"
#include "..\..\resource.h"
#include "GhostPic.h"

CGhostPic::CGhostPic(CDC* pDC) : CBasePictures(pDC)
{
	InitPics();
}

CGhostPic:: ~CGhostPic() {
	delete m_pGhostAttack;
	delete m_pGhostFront;
}


void CGhostPic::InitPics() {

	LoadPic(m_pGhostAttack, IDB_MONSTER_GHOST_ATTACK);
	LoadPic(m_pGhostFront, IDB_MONSTER_GHOST_FRONT);
}

CBitmap* CGhostPic::GetGhostPic(bool attacking) {
	if (attacking) {
		return m_pGhostAttack;
	}
	else {
		return m_pGhostFront;
	}
}

