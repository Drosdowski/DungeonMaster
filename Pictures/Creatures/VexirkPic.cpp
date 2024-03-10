#include "stdafx.h"
#include "..\..\resource.h"
#include "VexirkPic.h"


CVexirkPic::CVexirkPic(CDC* pDC) : CBasePictures(pDC)
{
	InitPics();
}

CVexirkPic:: ~CVexirkPic() {
	delete m_pVexirkAttack;
	delete m_pVexirkFront;
	delete m_pVexirkLeft;
	delete m_pVexirkRight;
	delete m_pVexirkBack;
}

void CVexirkPic::InitPics() {

	LoadPic(m_pVexirkAttack, IDB_MONSTER_VEXIRK_ATTACK);
	LoadPic(m_pVexirkFront, IDB_MONSTER_VEXIRK_FRONT);
	LoadPic(m_pVexirkRight, IDB_MONSTER_VEXIRK_RIGHT);
	LoadPicAndFlip(m_pVexirkLeft, IDB_MONSTER_VEXIRK_RIGHT);
	LoadPic(m_pVexirkBack, IDB_MONSTER_VEXIRK_BACK);
}

CBitmap* CVexirkPic::GetVexirkPic(int index, bool attacking) {
	if (index == 0) {
		if (attacking) {
			return m_pVexirkAttack;
		}
		else {
			return m_pVexirkFront;
		}
	}
	if (index == 1) return m_pVexirkRight;
	if (index == 2) return m_pVexirkBack;
	if (index == 3) return m_pVexirkLeft;

	return NULL;
}
