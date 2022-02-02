#include "stdafx.h"
#include "..\resource.h"
#include "CFountainPic.h"

CFountainPic::CFountainPic(CDC* pDC) : CBasePictures(pDC)
{
	InitFountain();
}

CFountainPic:: ~CFountainPic() {
	delete m_pFountainFront;
	delete m_pFountainRight;
	delete m_pFountainLeft;
}


void CFountainPic::InitFountain() {

	LoadPic(m_pFountainFront, IDB_FOUNTAIN_F);
	LoadPic(m_pFountainRight, IDB_FOUNTAIN_L);
	LoadPicAndFlip(m_pFountainLeft, IDB_FOUNTAIN_L);
}

CBitmap* CFountainPic::GetFountainFront() {
	return m_pFountainFront;
}

CBitmap* CFountainPic::GetFountainSide(bool left) {
	if (left)
		return m_pFountainLeft;
	else
		return m_pFountainRight;
}