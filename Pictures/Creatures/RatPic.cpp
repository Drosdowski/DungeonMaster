#include "stdafx.h"
#include "..\..\resource.h"
#include "RatPic.h"

CPainRatPic::CPainRatPic(CDC* pDC) : CBasePictures(pDC)
{
	InitPics();
}

CPainRatPic::~CPainRatPic() {
	for (int flip = 0; flip < 2; flip++)
	{
		delete m_pPainRatFront[flip];
		delete m_pPainRatAttack[flip];
	}
	delete m_pPainRatLeft;
	delete m_pPainRatRight;
	delete m_pPainRatBack;
}

void CPainRatPic::InitPics() {
	LoadPic(m_pPainRatAttack[0], IDB_MONSTER_PAINRAT_ATTACK);
	LoadPic(m_pPainRatFront[0], IDB_MONSTER_PAINRAT_FRONT);

	LoadPicAndFlip(m_pPainRatAttack[1], IDB_MONSTER_PAINRAT_ATTACK);
	LoadPicAndFlip(m_pPainRatFront[1], IDB_MONSTER_PAINRAT_FRONT);
	LoadPic(m_pPainRatRight, IDB_MONSTER_PAINRAT_RIGHT);
	LoadPicAndFlip(m_pPainRatLeft, IDB_MONSTER_PAINRAT_RIGHT);
	LoadPic(m_pPainRatBack, IDB_MONSTER_PAINRAT_BACK);
}

CBitmap* CPainRatPic::GetPainRatPic(int richt, bool attacking, int flip) {
	if (richt == 0) {
		if (attacking) {
			return m_pPainRatAttack[flip];
		}
		else {
			return m_pPainRatFront[flip];
		}
	}
	if (richt == 1) return m_pPainRatRight;
	if (richt == 2) return m_pPainRatBack;
	if (richt == 3) return m_pPainRatLeft;

	return NULL;
}