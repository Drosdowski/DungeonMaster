#include "stdafx.h"
#include "..\..\resource.h"
#include "WaterElementalPic.h"

CWaterElementalPic::CWaterElementalPic(CDC* pDC) : CBasePictures(pDC)
{
	InitPics();
}

CWaterElementalPic:: ~CWaterElementalPic() {
	for (int flip = 0; flip < 2; flip++)
	{
		delete m_pWaterElementalAttack[flip];
		delete m_pWaterElementalFront[flip];
	}
}


void CWaterElementalPic::InitPics() {
	LoadPic(m_pWaterElementalAttack[0], IDB_MONSTER_WATERELEMENTAL_ATTACK);
	LoadPic(m_pWaterElementalFront[0], IDB_MONSTER_WATERELEMENTAL_FRONT);

	LoadPicAndFlip(m_pWaterElementalAttack[1], IDB_MONSTER_WATERELEMENTAL_ATTACK);
	LoadPicAndFlip(m_pWaterElementalFront[1], IDB_MONSTER_WATERELEMENTAL_FRONT);
}

CBitmap* CWaterElementalPic::GetWaterElementalPic(bool attacking, int flip) {
	if (attacking) {
		return m_pWaterElementalAttack[flip];
	}
	else {
		return m_pWaterElementalFront[flip];
	}
}
