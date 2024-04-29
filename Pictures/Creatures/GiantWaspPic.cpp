#include "stdafx.h"
#include "..\..\resource.h"
#include "GiantWaspPic.h"

CGiantWaspPic::CGiantWaspPic(CDC* pDC) : CBasePictures(pDC)
{
	InitPics();
}

CGiantWaspPic:: ~CGiantWaspPic() {
	delete m_pGiantWaspAttack;
	delete m_pGiantWaspFront;
	delete m_pGiantWaspLeft;
	delete m_pGiantWaspRight;
	delete m_pGiantWaspBack;
}

void CGiantWaspPic::InitPics() {

	LoadPic(m_pGiantWaspAttack, IDB_MONSTER_GIANTWASP_ATTACK);
	LoadPic(m_pGiantWaspFront, IDB_MONSTER_GIANTWASP_FRONT);
	LoadPic(m_pGiantWaspRight, IDB_MONSTER_GIANTWASP_RIGHT);
	LoadPicAndFlip(m_pGiantWaspLeft, IDB_MONSTER_GIANTWASP_RIGHT);
	LoadPic(m_pGiantWaspBack, IDB_MONSTER_GIANTWASP_BACK);
}

CBitmap* CGiantWaspPic::GetGiantWaspPic(int index, bool attacking) {
	if (index == 0) {
		if (attacking) {
			return m_pGiantWaspAttack;
		}
		else {
			return m_pGiantWaspFront;
		}
	}
	if (index == 1) return m_pGiantWaspRight;
	if (index == 2) return m_pGiantWaspBack;
	if (index == 3) return m_pGiantWaspLeft;

	return NULL;
}