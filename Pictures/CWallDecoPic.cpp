#include "stdafx.h"
#include "..\resource.h"
#include "CWallDecoPic.h"

CWallDecoPic::CWallDecoPic(CDC* pDC) : CBasePictures(pDC)
{
	InitPics();
}

CWallDecoPic:: ~CWallDecoPic() {
	for (int gullideckel = 0; gullideckel < maxAnz; gullideckel++) {
		if (m_pDecoFront[gullideckel]) {
			delete m_pDecoFront[gullideckel];
			delete m_pDecoLeft[gullideckel];
			delete m_pDecoRight[gullideckel];
		}
	}
}

CBitmap* CWallDecoPic::GetPicFront(WallDecorationType index) {
	return m_pDecoFront[index];
}

CBitmap* CWallDecoPic::GetPicSide(WallDecorationType  index, bool left) {
	if (left)
		return m_pDecoLeft[index];
	else
		return m_pDecoRight[index];
}


void CWallDecoPic::InitPics() {
	for (int gullideckel = 0; gullideckel < maxAnz; gullideckel++) {
		m_pDecoFront[gullideckel] = NULL;
		m_pDecoLeft[gullideckel] = NULL;
		m_pDecoRight[gullideckel] = NULL;
	}

	LoadPic(m_pDecoFront[WallDecorationType::Fountain], IDB_FOUNTAIN_F);
	LoadPic(m_pDecoRight[WallDecorationType::Fountain], IDB_FOUNTAIN_L);
	LoadPicAndFlip(m_pDecoLeft[WallDecorationType::Fountain], IDB_FOUNTAIN_L);

	LoadPic(m_pDecoFront[WallDecorationType::LeverUp], IDB_LEVER_UP_FRONT);
	LoadPic(m_pDecoRight[WallDecorationType::LeverUp], IDB_LEVER_UP_RIGHT);
	LoadPicAndFlip(m_pDecoLeft[WallDecorationType::LeverUp], IDB_LEVER_UP_RIGHT);
	LoadPic(m_pDecoFront[WallDecorationType::LeverDown], IDB_LEVER_DOWN_FRONT);
	LoadPic(m_pDecoRight[WallDecorationType::LeverDown], IDB_LEVER_DOWN_RIGHT);
	LoadPicAndFlip(m_pDecoLeft[WallDecorationType::LeverDown], IDB_LEVER_DOWN_RIGHT);


}