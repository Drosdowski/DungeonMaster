#include "stdafx.h"
#include "..\..\resource.h"
#include "SkeletonPic.h"

CSkeletonPic::CSkeletonPic(CDC* pDC) : CBasePictures(pDC)
{
	InitPics();
}

CSkeletonPic:: ~CSkeletonPic() {
	for (int flip = 0; flip < 2; flip++)
	{
		delete m_pSkeletonAttack[flip];
		delete m_pSkeletonFront[flip];
	}
	delete m_pSkeletonLeft;
	delete m_pSkeletonRight;
	delete m_pSkeletonBack;
}

void CSkeletonPic::InitPics() {
	LoadPic(m_pSkeletonAttack[0], IDB_MONSTER_SKELETON_ATTACK);
	LoadPic(m_pSkeletonFront[0], IDB_MONSTER_SKELETON_FRONT);

	LoadPicAndFlip(m_pSkeletonAttack[1], IDB_MONSTER_SKELETON_ATTACK);
	LoadPicAndFlip(m_pSkeletonFront[1], IDB_MONSTER_SKELETON_FRONT);
	LoadPic(m_pSkeletonRight, IDB_MONSTER_SKELETON_RIGHT);
	LoadPicAndFlip(m_pSkeletonLeft, IDB_MONSTER_SKELETON_RIGHT);
	LoadPic(m_pSkeletonBack, IDB_MONSTER_SKELETON_BACK);
}

CBitmap* CSkeletonPic::GetSkeletonPic(int index, bool attacking, int flip) {
	if (index == 0) {
		if (attacking) {
			return m_pSkeletonAttack[flip];
		}
		else {
			return m_pSkeletonFront[flip];
		}
	}
	if (index == 1) return m_pSkeletonRight;
	if (index == 2) return m_pSkeletonBack;
	if (index == 3) return m_pSkeletonLeft;
	
	return NULL;
}

