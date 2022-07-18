#include "stdafx.h"
#include "..\resource.h"
#include "CStairsPic.h"

CStairsPic::CStairsPic(CDC* pDC) : CBasePictures(pDC)
{
	InitStairs();
}
#
CStairsPic::~CStairsPic()
{
	for (int i = 0; i < 4; i++)
	{
		delete m_pStairsDownFront[i];
		delete m_pStairsUpFront[i];
		if (i > 0) {
			delete m_pStairsUpLeft[i];
			delete m_pStairsUpRight[i];
			delete m_pStairsDownLeft[i];
			delete m_pStairsDownRight[i];

			delete m_pStairsDownSideLeft[i];
			delete m_pStairsUpSideLeft[i];
			delete m_pStairsDownSideRight[i];
			delete m_pStairsUpSideRight[i];
		}
	}
}

void CStairsPic::InitStairs() {
	LoadPic(m_pStairsDownFront[0], IDB_STAIRS_DOWN_0F);
	
	LoadPic(m_pStairsDownLeft[1], IDB_STAIRS_DOWN_1L);
	LoadPicAndFlip(m_pStairsDownRight[1], IDB_STAIRS_DOWN_1L);
	LoadPic(m_pStairsDownFront[1], IDB_STAIRS_DOWN_1F);

	LoadPic(m_pStairsDownLeft[2], IDB_STAIRS_DOWN_2L);
	LoadPicAndFlip(m_pStairsDownRight[2], IDB_STAIRS_DOWN_2L);
	LoadPic(m_pStairsDownFront[2], IDB_STAIRS_DOWN_2F);

	LoadPic(m_pStairsDownLeft[3], IDB_STAIRS_DOWN_3L);
	LoadPicAndFlip(m_pStairsDownRight[3], IDB_STAIRS_DOWN_3L);
	LoadPic(m_pStairsDownFront[3], IDB_STAIRS_DOWN_3F);

	LoadPic(m_pStairsDownSideLeft[1], IDB_STAIRS_S1L);
	LoadPic(m_pStairsDownSideLeft[2], IDB_STAIRS_DOWN_S2L);
	LoadPic(m_pStairsDownSideLeft[3], IDB_STAIRS_S3L);
	LoadPicAndFlip(m_pStairsDownSideRight[1], IDB_STAIRS_S1L);
	LoadPicAndFlip(m_pStairsDownSideRight[2], IDB_STAIRS_DOWN_S2L);
	LoadPicAndFlip(m_pStairsDownSideRight[3], IDB_STAIRS_S3L);


	LoadPic(m_pStairsUpFront[0], IDB_STAIRS_UP_0F);
	
	LoadPic(m_pStairsUpLeft[1], IDB_STAIRS_UP_1L);
	LoadPicAndFlip(m_pStairsUpRight[1], IDB_STAIRS_UP_1L);
	LoadPic(m_pStairsUpFront[1], IDB_STAIRS_UP_1F);

	LoadPic(m_pStairsUpLeft[2], IDB_STAIRS_UP_2L);
	LoadPicAndFlip(m_pStairsUpRight[2], IDB_STAIRS_UP_2L);
	LoadPic(m_pStairsUpFront[2], IDB_STAIRS_UP_2F);

	LoadPic(m_pStairsUpLeft[3], IDB_STAIRS_UP_3L);
	LoadPicAndFlip(m_pStairsUpRight[3], IDB_STAIRS_UP_3L);
	LoadPic(m_pStairsUpFront[3], IDB_STAIRS_UP_3F);

	LoadPic(m_pStairsUpSideLeft[1], IDB_STAIRS_S1L);
	LoadPic(m_pStairsUpSideLeft[2], IDB_STAIRS_UP_S2L);
	LoadPic(m_pStairsUpSideLeft[3], IDB_STAIRS_S3L);
	LoadPicAndFlip(m_pStairsUpSideRight[1], IDB_STAIRS_S1L);
	LoadPicAndFlip(m_pStairsUpSideRight[2], IDB_STAIRS_UP_S2L);
	LoadPicAndFlip(m_pStairsUpSideRight[3], IDB_STAIRS_S3L);


}

CBitmap* CStairsPic::GetStairUpFrontPic(int xx, int ebene) {

	if (ebene > 0) {
		if (xx == 2) return m_pStairsUpLeft[ebene];
		if (xx == 3) return m_pStairsUpRight[ebene];
	}
	if (xx == 4) return m_pStairsUpFront[ebene];
	return NULL;
}
CBitmap* CStairsPic::GetStairDownFrontPic(int xx, int ebene) {
	if (ebene > 0) {
		if (xx == 2) return m_pStairsDownLeft[ebene];
		if (xx == 3) return m_pStairsDownRight[ebene];
	}
	if (xx == 4) return m_pStairsDownFront[ebene];
	return NULL;
}

CBitmap* CStairsPic::GetStairUpSidePic(int xx, int ebene) {
	if (ebene < 3) {
		if (xx == 2) return m_pStairsUpSideLeft[ebene + 1];
		if (xx == 3) return m_pStairsUpSideRight[ebene + 1];
	}
	return NULL;
}
CBitmap* CStairsPic::GetStairDownSidePic(int xx, int ebene) {
	if (ebene < 3) {
		if (xx == 2) return m_pStairsDownSideLeft[ebene + 1];
		if (xx == 3) return m_pStairsDownSideRight[ebene + 1];
	}
	return NULL;
}

CPoint CStairsPic::GetStairsUpFrontPos(int xx, int ebene, CPoint wallPos) {
	switch (ebene) {
	case 0:
		return CPoint(wallPos.x, wallPos.y + 104);
		break;
	case 1:
		if (xx == 4) return  CPoint(wallPos.x - 2, wallPos.y + 2);
		//if (xx == 4) return  CPoint(wallPos.x, wallPos.y);
		if (xx == 3) return  CPoint(wallPos.x + 58, wallPos.y);
		return wallPos;
		break;
	case 2:
		if (xx == 4) return CPoint(wallPos.x + 10, wallPos.y + 2);
		return wallPos;
		break;
	case 3:
		if (xx == 4) return CPoint(wallPos.x - 26, wallPos.y + 2);
		return wallPos;
		break;
	}
	return CPoint(0, 0);
}

CPoint CStairsPic::GetStairsDownFrontPos(int xx, int ebene, CPoint wallPos) {
	switch (ebene) {
	case 0:
		return CPoint(wallPos.x, wallPos.y + 138);
		break;
	case 1:
		if (xx == 2) return  CPoint(wallPos.x, wallPos.y + 16);
		if (xx == 3) return  CPoint(wallPos.x + 58, wallPos.y + 16);
		if (xx == 4) return  CPoint(wallPos.x, wallPos.y + 16);
		return wallPos;
		break;
	case 2:
		if (xx == 4) return  CPoint(wallPos.x + 6, wallPos.y + 10);
		return wallPos;
		break;
	case 3:
		if (xx == 4) return  CPoint(wallPos.x - 24, wallPos.y + 4);
		return wallPos;
		break;
	}
	return CPoint(0, 0);
}


CPoint CStairsPic::GetStairsUpSidePos(int xx, int ebene, CPoint wallPos) {
	switch (ebene) {
	case 0:
		if (xx == 2) return CPoint(wallPos.x, wallPos.y + 148);
		if (xx == 3) return CPoint(wallPos.x + 34, wallPos.y + 148);
		break;
	case 1:
		if (xx == 2) return  CPoint(wallPos.x + 58, wallPos.y + 98);
		if (xx == 3) return  CPoint(wallPos.x - 8, wallPos.y + 98);
		return wallPos;
		break;
	case 2:
		if (xx == 2) return  CPoint(wallPos.x + 120, wallPos.y + 72);
		if (xx == 3) return  CPoint(wallPos.x + 4, wallPos.y + 72);
		break;
	case 3:
		return wallPos;
		break;
	}
	return CPoint(0, 0);
}

CPoint CStairsPic::GetStairsDownSidePos(int xx, int ebene, CPoint wallPos) {
	switch (ebene) {
	case 0:
		if (xx == 2) return CPoint(wallPos.x, wallPos.y + 146);
		if (xx == 3) return CPoint(wallPos.x + 34, wallPos.y + 146);
		break;
	case 1:
		if (xx == 2) return  CPoint(wallPos.x + 58, wallPos.y + 104);
		if (xx == 3) return  CPoint(wallPos.x - 8, wallPos.y + 104);
		return wallPos;
		break;
	case 2:
		if (xx == 2) return  CPoint(wallPos.x + 120, wallPos.y + 72);
		if (xx == 3) return  CPoint(wallPos.x + 4, wallPos.y + 72);
		return wallPos;
		break;
	case 3:
		return wallPos;
		break;
	}
	return CPoint(0, 0);
}

