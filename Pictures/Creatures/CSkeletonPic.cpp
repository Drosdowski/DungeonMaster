#include "stdafx.h"
#include "..\..\resource.h"
#include "CSkeletonPic.h"

CSkeletonPic::CSkeletonPic(CDC* pDC) : CBasePictures(pDC)
{
	InitPics();
}

CSkeletonPic:: ~CSkeletonPic() {
	delete m_pSkeletonAttack;
	delete m_pSkeletonFront;
	delete m_pSkeletonLeft;
	delete m_pSkeletonRight;
	delete m_pSkeletonBack;
}


void CSkeletonPic::InitPics() {

	LoadPic(m_pSkeletonAttack, IDB_SKELETON_ATTACK);
	LoadPic(m_pSkeletonFront, IDB_SKELETON_FRONT);
	LoadPic(m_pSkeletonRight, IDB_SKELETON_RIGHT);
	LoadPicAndFlip(m_pSkeletonLeft, IDB_SKELETON_RIGHT);
	LoadPic(m_pSkeletonBack, IDB_SKELETON_BACK);
}

CBitmap* CSkeletonPic::GetSkeletonPic(int index, bool attacking) {
	if (index == 0) {
		if (attacking) {
			return m_pSkeletonAttack;
		}
		else {
			return m_pSkeletonFront;
		}
	}
	if (index == 1) return m_pSkeletonRight;
	if (index == 2) return m_pSkeletonBack;
	if (index == 3) return m_pSkeletonLeft;
	
	return NULL;
}

