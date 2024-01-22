#include "stdafx.h"
#include "..\..\resource.h"
#include "RatPic.h"

CPainRatPic::CPainRatPic(CDC* pDC) : CBasePictures(pDC)
{
	InitPics();
}

CPainRatPic::~CPainRatPic() {
	delete m_pPainRatFront;
	delete m_pPainRatLeft;
	delete m_pPainRatRight;
	delete m_pPainRatBack;
	delete m_pPainRatAttack;
}

void CPainRatPic::InitPics() {

	LoadPic(m_pPainRatAttack, IDB_MONSTER_PAINRAT_ATTACK);
	LoadPic(m_pPainRatFront, IDB_MONSTER_PAINRAT_FRONT);
	LoadPic(m_pPainRatRight, IDB_MONSTER_PAINRAT_RIGHT);
	LoadPicAndFlip(m_pPainRatLeft, IDB_MONSTER_PAINRAT_RIGHT);
	LoadPic(m_pPainRatBack, IDB_MONSTER_PAINRAT_BACK);
}

CBitmap* CPainRatPic::GetPainRatPic(int richt, bool attacking) {
	if (richt == 0) {
		if (attacking) {
			return m_pPainRatAttack;
		}
		else {
			return m_pPainRatFront;
		}
	}
	if (richt == 1) return m_pPainRatRight;
	if (richt == 2) return m_pPainRatBack;
	if (richt == 3) return m_pPainRatLeft;

	return NULL;
}