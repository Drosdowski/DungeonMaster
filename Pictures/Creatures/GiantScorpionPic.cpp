#include "stdafx.h"
#include "..\..\resource.h"
#include "GiantScorpionPic.h"

CGiantScorpionPic::CGiantScorpionPic(CDC* pDC) : CBasePictures(pDC)
{
	InitPics();
}

CGiantScorpionPic:: ~CGiantScorpionPic() {
	delete m_pGiantScorpionAttack;
	delete m_pGiantScorpionFront;
	delete m_pGiantScorpionLeft;
	delete m_pGiantScorpionRight;
	delete m_pGiantScorpionBack;
}

void CGiantScorpionPic::InitPics() {

	LoadPic(m_pGiantScorpionAttack, IDB_MONSTER_GIANTSCORPION_ATTACK);
	LoadPic(m_pGiantScorpionFront, IDB_MONSTER_GIANTSCORPION_FRONT);
	LoadPic(m_pGiantScorpionRight, IDB_MONSTER_GIANTSCORPION_RIGHT);
	LoadPicAndFlip(m_pGiantScorpionLeft, IDB_MONSTER_GIANTSCORPION_RIGHT);
	LoadPic(m_pGiantScorpionBack, IDB_MONSTER_GIANTSCORPION_BACK);
}

CBitmap* CGiantScorpionPic::GetGiantScorpionPic(int index, bool attacking) {
	if (index == 0) {
		if (attacking) {
			return m_pGiantScorpionAttack;
		}
		else {
			return m_pGiantScorpionFront;
		}
	}
	if (index == 1) return m_pGiantScorpionRight;
	if (index == 2) return m_pGiantScorpionBack;
	if (index == 3) return m_pGiantScorpionLeft;

	return NULL;
}