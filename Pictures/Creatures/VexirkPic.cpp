#include "stdafx.h"
#include "..\..\resource.h"
#include "VexirkPic.h"


CVexirkPic::CVexirkPic(CDC* pDC) : CBasePictures(pDC)
{
	InitPics();
}

CVexirkPic:: ~CVexirkPic() {
	for (int flip = 0; flip < 2; flip++)
	{
		delete m_pVexirkAttack[flip];
		delete m_pVexirkFront[flip];
	}
	delete m_pVexirkLeft;
	delete m_pVexirkRight;
	delete m_pVexirkBack;
}

void CVexirkPic::InitPics() {
	LoadPic(m_pVexirkAttack[0], IDB_MONSTER_VEXIRK_ATTACK);
	LoadPic(m_pVexirkFront[0], IDB_MONSTER_VEXIRK_FRONT);

	LoadPicAndFlip(m_pVexirkAttack[1], IDB_MONSTER_VEXIRK_ATTACK);
	LoadPicAndFlip(m_pVexirkFront[1], IDB_MONSTER_VEXIRK_FRONT);
	LoadPic(m_pVexirkRight, IDB_MONSTER_VEXIRK_RIGHT);
	LoadPicAndFlip(m_pVexirkLeft, IDB_MONSTER_VEXIRK_RIGHT);
	LoadPic(m_pVexirkBack, IDB_MONSTER_VEXIRK_BACK);
}

CBitmap* CVexirkPic::GetVexirkPic(int index, bool attacking, int flip) {
	if (index == 0) {
		if (attacking) {
			return m_pVexirkAttack[flip];
		}
		else {
			return m_pVexirkFront[flip];
		}
	}
	if (index == 1) return m_pVexirkRight;
	if (index == 2) return m_pVexirkBack;
	if (index == 3) return m_pVexirkLeft;

	return NULL;
}
