#include "stdafx.h"
#include "..\resource.h"
#include "CFloorOrnatePic.h"

CFloorOrnatePic::CFloorOrnatePic(CDC* pDC) : CBasePictures(pDC)
{
	InitOrnatePics();
}

CFloorOrnatePic::~CFloorOrnatePic()
{
	for (int gurke = 1; gurke < 4; gurke++) {
		delete m_pPuddleLeft[gurke];
		delete m_pPuddleRight[gurke];
		delete m_pPuddleFront[gurke];

		delete m_pMossLeft[gurke];
		delete m_pMossRight[gurke];
		delete m_pMossFront[gurke];
	}
}

CBitmap* CFloorOrnatePic::GetPuddlePic(int ebene, int xxx) {
	if (ebene > 0) {
		if (xxx == 2) return m_pPuddleLeft[ebene];
		if (xxx == 3) return m_pPuddleRight[ebene];
		if (xxx == 4) return m_pPuddleFront[ebene];
	}
	return NULL;
}
CBitmap* CFloorOrnatePic::GetMossPic(int ebene, int xxx) {
	if (ebene > 0) {
		if (xxx == 2) return m_pMossLeft[ebene];
		if (xxx == 3) return m_pMossRight[ebene];
		if (xxx == 4) return m_pMossFront[ebene];
	}
	return NULL;
}


void CFloorOrnatePic::InitOrnatePics() {
	LoadPic(m_pPuddleFront[1], IDB_FLOOR_PUDDLE_F1);
	LoadPic(m_pPuddleLeft[1], IDB_FLOOR_PUDDLE_L1);
	LoadPicAndFlip(m_pPuddleRight[1], IDB_FLOOR_PUDDLE_L1);

	LoadPic(m_pMossFront[1], IDB_FLOOR_MOSS_F1);
	LoadPic(m_pMossLeft[1], IDB_FLOOR_MOSS_L1);
	LoadPicAndFlip(m_pMossRight[1], IDB_FLOOR_MOSS_L1);

	LoadPic(m_pPuddleFront[2], IDB_FLOOR_PUDDLE_F2);
	LoadPic(m_pPuddleLeft[2], IDB_FLOOR_PUDDLE_L2);
	LoadPicAndFlip(m_pPuddleRight[2], IDB_FLOOR_PUDDLE_L2);

	LoadPic(m_pMossFront[2], IDB_FLOOR_MOSS_F2);
	LoadPic(m_pMossLeft[2], IDB_FLOOR_MOSS_L2);
	LoadPicAndFlip(m_pMossRight[2], IDB_FLOOR_MOSS_L2);

	LoadPic(m_pPuddleFront[3], IDB_FLOOR_PUDDLE_F3);
	LoadPic(m_pPuddleLeft[3], IDB_FLOOR_PUDDLE_L3);
	LoadPicAndFlip(m_pPuddleRight[3], IDB_FLOOR_PUDDLE_L3);

	LoadPic(m_pMossFront[3], IDB_FLOOR_MOSS_F3);
	LoadPic(m_pMossLeft[3], IDB_FLOOR_MOSS_L3);
	LoadPicAndFlip(m_pMossRight[3], IDB_FLOOR_MOSS_L3);
}