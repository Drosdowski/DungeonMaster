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

		delete m_pRoundGrateLeft[gurke];
		delete m_pRoundGrateRight[gurke];
		delete m_pRoundGrateFront[gurke];

		delete m_pSquareGrateLeft[gurke];
		delete m_pSquareGrateRight[gurke];
		delete m_pSquareGrateFront[gurke];

		delete m_pBlackFlamePitLeft[gurke];
		delete m_pBlackFlamePitRight[gurke];
		delete m_pBlackFlamePitFront[gurke];

		delete m_pCrackLeft[gurke];
		delete m_pCrackRight[gurke];
		delete m_pCrackFront[gurke];
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

CBitmap* CFloorOrnatePic::GetRoundGratePic(int ebene, int xxx) {
	if (ebene > 0) {
		if (xxx == 2) return m_pRoundGrateLeft[ebene];
		if (xxx == 3) return m_pRoundGrateRight[ebene];
		if (xxx == 4) return m_pRoundGrateFront[ebene];
	}
	return NULL;
}
CBitmap* CFloorOrnatePic::GetSquareGratePic(int ebene, int xxx) {
	if (ebene > 0) {
		if (xxx == 2) return m_pSquareGrateLeft[ebene];
		if (xxx == 3) return m_pSquareGrateRight[ebene];
		if (xxx == 4) return m_pSquareGrateFront[ebene];
	}
	return NULL;
}
CBitmap* CFloorOrnatePic::GetBlackFlamePitPic(int ebene, int xxx) {
	if (ebene > 0) {
		if (xxx == 2) return m_pBlackFlamePitLeft[ebene];
		if (xxx == 3) return m_pBlackFlamePitRight[ebene];
		if (xxx == 4) return m_pBlackFlamePitFront[ebene];
	}
	return NULL;
}
CBitmap* CFloorOrnatePic::GetCrackPic(int ebene, int xxx) {
	if (ebene > 0) {
		if (xxx == 2) return m_pCrackLeft[ebene];
		if (xxx == 3) return m_pCrackRight[ebene];
		if (xxx == 4) return m_pCrackFront[ebene];
	}
	return NULL;
}


void CFloorOrnatePic::InitOrnatePics() {
	LoadPic(m_pPuddleFront[1], IDB_FLOOR_PUDDLE_F1);
	LoadPic(m_pPuddleLeft[1], IDB_FLOOR_PUDDLE_L1);
	LoadPicAndFlip(m_pPuddleRight[1], IDB_FLOOR_PUDDLE_L1);

	LoadPic(m_pPuddleFront[2], IDB_FLOOR_PUDDLE_F2);
	LoadPic(m_pPuddleLeft[2], IDB_FLOOR_PUDDLE_L2);
	LoadPicAndFlip(m_pPuddleRight[2], IDB_FLOOR_PUDDLE_L2);
	
	LoadPic(m_pPuddleFront[3], IDB_FLOOR_PUDDLE_F3);
	LoadPic(m_pPuddleLeft[3], IDB_FLOOR_PUDDLE_L3);
	LoadPicAndFlip(m_pPuddleRight[3], IDB_FLOOR_PUDDLE_L3);
	
	
	LoadPic(m_pMossFront[1], IDB_FLOOR_MOSS_F1);
	LoadPic(m_pMossLeft[1], IDB_FLOOR_MOSS_L1);
	LoadPicAndFlip(m_pMossRight[1], IDB_FLOOR_MOSS_L1);
		
	LoadPic(m_pMossFront[2], IDB_FLOOR_MOSS_F2);
	LoadPic(m_pMossLeft[2], IDB_FLOOR_MOSS_L2);
	LoadPicAndFlip(m_pMossRight[2], IDB_FLOOR_MOSS_L2);
		
	LoadPic(m_pMossFront[3], IDB_FLOOR_MOSS_F3);
	LoadPic(m_pMossLeft[3], IDB_FLOOR_MOSS_L3);
	LoadPicAndFlip(m_pMossRight[3], IDB_FLOOR_MOSS_L3);


	LoadPic(m_pRoundGrateFront[1], IDB_FLOOR_ROUND_GRATE_F1);
	LoadPic(m_pRoundGrateLeft[1], IDB_FLOOR_ROUND_GRATE_L1);
	LoadPicAndFlip(m_pRoundGrateRight[1], IDB_FLOOR_ROUND_GRATE_L1);

	LoadPic(m_pRoundGrateFront[2], IDB_FLOOR_ROUND_GRATE_F2);
	LoadPic(m_pRoundGrateLeft[2], IDB_FLOOR_ROUND_GRATE_L2);
	LoadPicAndFlip(m_pRoundGrateRight[2], IDB_FLOOR_ROUND_GRATE_L2);

	LoadPic(m_pRoundGrateFront[3], IDB_FLOOR_ROUND_GRATE_F3);
	LoadPic(m_pRoundGrateLeft[3], IDB_FLOOR_ROUND_GRATE_L3);
	LoadPicAndFlip(m_pRoundGrateRight[3], IDB_FLOOR_ROUND_GRATE_L3);

	LoadPic(m_pSquareGrateFront[1], IDB_FLOOR_SQUARE_GRATE_F1);
	LoadPic(m_pSquareGrateLeft[1], IDB_FLOOR_SQUARE_GRATE_L1);
	LoadPicAndFlip(m_pSquareGrateRight[1], IDB_FLOOR_SQUARE_GRATE_L1);

	LoadPic(m_pSquareGrateFront[2], IDB_FLOOR_SQUARE_GRATE_F2);
	LoadPic(m_pSquareGrateLeft[2], IDB_FLOOR_SQUARE_GRATE_L2);
	LoadPicAndFlip(m_pSquareGrateRight[2], IDB_FLOOR_SQUARE_GRATE_L2);

	LoadPic(m_pSquareGrateFront[3], IDB_FLOOR_SQUARE_GRATE_F3);
	LoadPic(m_pSquareGrateLeft[3], IDB_FLOOR_SQUARE_GRATE_L3);
	LoadPicAndFlip(m_pSquareGrateRight[3], IDB_FLOOR_SQUARE_GRATE_L3);


	LoadPic(m_pBlackFlamePitFront[1], IDB_FLOOR_BLACKFLAME_PIT_F1);
	LoadPic(m_pBlackFlamePitLeft[1], IDB_FLOOR_BLACKFLAME_PIT_L1);
	LoadPicAndFlip(m_pBlackFlamePitRight[1], IDB_FLOOR_BLACKFLAME_PIT_L1);

	LoadPic(m_pBlackFlamePitFront[2], IDB_FLOOR_BLACKFLAME_PIT_F2);
	LoadPic(m_pBlackFlamePitLeft[2], IDB_FLOOR_BLACKFLAME_PIT_L2);
	LoadPicAndFlip(m_pBlackFlamePitRight[2], IDB_FLOOR_BLACKFLAME_PIT_L2);

	LoadPic(m_pBlackFlamePitFront[3], IDB_FLOOR_BLACKFLAME_PIT_F3);
	LoadPic(m_pBlackFlamePitLeft[3], IDB_FLOOR_BLACKFLAME_PIT_L3);
	LoadPicAndFlip(m_pBlackFlamePitRight[3], IDB_FLOOR_BLACKFLAME_PIT_L3);


	LoadPic(m_pCrackFront[1], IDB_FLOOR_CRACK_F1);
	LoadPic(m_pCrackLeft[1], IDB_FLOOR_CRACK_L1);
	LoadPicAndFlip(m_pCrackRight[1], IDB_FLOOR_CRACK_L1);

	LoadPic(m_pCrackFront[2], IDB_FLOOR_CRACK_F2);
	LoadPic(m_pCrackLeft[2], IDB_FLOOR_CRACK_L2);
	LoadPicAndFlip(m_pCrackRight[2], IDB_FLOOR_CRACK_L2);

	LoadPic(m_pCrackFront[3], IDB_FLOOR_CRACK_F3);
	LoadPic(m_pCrackLeft[3], IDB_FLOOR_CRACK_L3);
	LoadPicAndFlip(m_pCrackRight[3], IDB_FLOOR_CRACK_L3);
}