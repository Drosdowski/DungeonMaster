#include "stdafx.h"
#include "..\..\resource.h"
#include "RusterPic.h"

CRusterPic::CRusterPic(CDC* pDC): CBasePictures(pDC)
{
	InitPics();
}

CRusterPic:: ~CRusterPic() {
	for (int flip = 0; flip < 2; flip++)
	{
		delete m_pRusterFront[flip];
	}
	delete m_pRusterLeft;
	delete m_pRusterRight;
	delete m_pRusterBack;
}

void CRusterPic::InitPics() {
	LoadPic(m_pRusterFront[0], IDB_MONSTER_RUSTER_FRONT);

	LoadPicAndFlip(m_pRusterFront[1], IDB_MONSTER_RUSTER_FRONT);
	LoadPic(m_pRusterRight, IDB_MONSTER_RUSTER_RIGHT);
	LoadPicAndFlip(m_pRusterLeft, IDB_MONSTER_RUSTER_RIGHT);
	LoadPic(m_pRusterBack, IDB_MONSTER_RUSTER_BACK);
}

CBitmap* CRusterPic::GetRusterPic(int index, int flip) {
	if (index == 0) return m_pRusterFront[flip];
	if (index == 1) return m_pRusterRight;
	if (index == 2) return m_pRusterBack;
	if (index == 3) return m_pRusterLeft;

	return NULL;
}