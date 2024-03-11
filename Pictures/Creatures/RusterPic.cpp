#include "stdafx.h"
#include "..\..\resource.h"
#include "RusterPic.h"

CRusterPic::CRusterPic(CDC* pDC): CBasePictures(pDC)
{
	InitPics();
}

CRusterPic:: ~CRusterPic() {
	delete m_pRusterFront;
	delete m_pRusterLeft;
	delete m_pRusterRight;
	delete m_pRusterBack;
}

void CRusterPic::InitPics() {

	LoadPic(m_pRusterFront, IDB_MONSTER_RUSTER_FRONT);
	LoadPic(m_pRusterRight, IDB_MONSTER_RUSTER_RIGHT);
	LoadPicAndFlip(m_pRusterLeft, IDB_MONSTER_RUSTER_RIGHT);
	LoadPic(m_pRusterBack, IDB_MONSTER_RUSTER_BACK);
}

CBitmap* CRusterPic::GetRusterPic(int index) {
	if (index == 0) return m_pRusterFront;
	if (index == 1) return m_pRusterRight;
	if (index == 2) return m_pRusterBack;
	if (index == 3) return m_pRusterLeft;

	return NULL;
}