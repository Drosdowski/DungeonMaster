#include "stdafx.h"
#include "..\..\resource.h"
#include "GiantScorpionPic.h"

CGiantScorpionPic::CGiantScorpionPic(CDC* pDC) : CBasePictures(pDC)
{
	InitPics();
}

CGiantScorpionPic:: ~CGiantScorpionPic() {
	for (int flip = 0; flip < 2; flip++)
	{
		delete m_pGiantScorpionAttack[flip];
		delete m_pGiantScorpionFront[flip];
	}
	delete m_pGiantScorpionLeft;
	delete m_pGiantScorpionRight;
	delete m_pGiantScorpionBack;
}

void CGiantScorpionPic::InitPics() {

	LoadPic(m_pGiantScorpionAttack[0], IDB_MONSTER_GIANTSCORPION_ATTACK);
	LoadPic(m_pGiantScorpionFront[0], IDB_MONSTER_GIANTSCORPION_FRONT);
	LoadPic(m_pGiantScorpionRight, IDB_MONSTER_GIANTSCORPION_RIGHT);
	LoadPicAndFlip(m_pGiantScorpionLeft, IDB_MONSTER_GIANTSCORPION_RIGHT);
	LoadPic(m_pGiantScorpionBack, IDB_MONSTER_GIANTSCORPION_BACK);

	LoadPicAndFlip(m_pGiantScorpionAttack[1], IDB_MONSTER_GIANTSCORPION_ATTACK);
	LoadPicAndFlip(m_pGiantScorpionFront[1], IDB_MONSTER_GIANTSCORPION_FRONT);
}

CBitmap* CGiantScorpionPic::GetGiantScorpionPic(int index, bool attacking, int flip) {
	if (index == 0) {
		if (attacking) {
			return m_pGiantScorpionAttack[flip];
		}
		else {
			return m_pGiantScorpionFront[flip];
		}
	}
	if (index == 1) return m_pGiantScorpionRight;
	if (index == 2) return m_pGiantScorpionBack;
	if (index == 3) return m_pGiantScorpionLeft;

	return NULL;
}