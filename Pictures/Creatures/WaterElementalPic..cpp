#include "stdafx.h"
#include "..\..\resource.h"
#include "WaterElementalPic.h"

CWaterElementalPic::CWaterElementalPic(CDC* pDC) : CBasePictures(pDC)
{
	InitPics();
}

CWaterElementalPic:: ~CWaterElementalPic() {
	delete m_pWaterElementalAttack;
	delete m_pWaterElementalFront;
}


void CWaterElementalPic::InitPics() {

	LoadPic(m_pWaterElementalAttack, IDB_MONSTER_WATERELEMENTAL_ATTACK);
	LoadPic(m_pWaterElementalFront, IDB_MONSTER_WATERELEMENTAL_FRONT);
}

CBitmap* CWaterElementalPic::GetWaterElementalPic(bool attacking) {
	if (attacking) {
		return m_pWaterElementalAttack;
	}
	else {
		return m_pWaterElementalFront;
	}
}

