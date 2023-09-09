#include "stdafx.h"
#include "..\resource.h"
#include "ChampionPortrait.h"

CChampionPortrait::CChampionPortrait(CDC* pDC) : CBasePictures(pDC)
{
	InitPics();
}

CChampionPortrait:: ~CChampionPortrait() {
	delete m_portraits;
}

void CChampionPortrait::InitPics() {
	LoadPic(m_portraits, IDB_CHAMPIONS);
}

CPoint CChampionPortrait::GetKoords(int id) {
	int x = (id % 8) * 32;
	int y = ((int)(id / 8)) * 29;
	return CPoint(x, y);
}
