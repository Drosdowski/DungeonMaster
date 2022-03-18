#include "stdafx.h"
#include "..\resource.h"
#include "CWallDecoPic.h"

CWallDecoPic::CWallDecoPic(CDC* pDC) : CBasePictures(pDC)
{
	InitPics();
}

CWallDecoPic:: ~CWallDecoPic() {
	delete m_pFountainFront;
	delete m_pFountainRight;
	delete m_pFountainLeft;

	delete m_pLeverUpFront;
	delete m_pLeverUpRight;
	delete m_pLeverUpLeft;
	delete m_pLeverDownFront;
	delete m_pLeverDownRight;
	delete m_pLeverDownLeft;
}

CBitmap* CWallDecoPic::GetPicFront(WallDecorationType  index) {
	switch (index) {
	case Fountain: 
		return m_pFountainFront;
	case LeverDown:
		return m_pLeverDownFront;
	case LeverUp:
		return m_pLeverUpFront;
	
	}
	return NULL;
}

CBitmap* CWallDecoPic::GetPicSide(WallDecorationType  index, bool left) {
	switch (index) {
	case Fountain: 
		if (left)
			return m_pFountainLeft;
		else
			return m_pFountainRight;
	case LeverDown:
		if (left)
			return m_pLeverDownLeft;
		else
			return m_pLeverDownRight;
	case LeverUp:
		if (left)
			return m_pLeverUpLeft;
		else
			return m_pLeverUpRight;

	}
	return NULL;
}


void CWallDecoPic::InitPics() {
	LoadPic(m_pFountainFront, IDB_FOUNTAIN_F);
	LoadPic(m_pFountainRight, IDB_FOUNTAIN_L);
	LoadPicAndFlip(m_pFountainLeft, IDB_FOUNTAIN_L);

	LoadPic(m_pLeverUpFront, IDB_LEVER_UP_FRONT);
	LoadPic(m_pLeverUpRight, IDB_LEVER_UP_RIGHT);
	LoadPicAndFlip(m_pLeverUpLeft, IDB_LEVER_UP_RIGHT);
	LoadPic(m_pLeverDownFront, IDB_LEVER_DOWN_FRONT);
	LoadPic(m_pLeverDownRight, IDB_LEVER_DOWN_RIGHT);
	LoadPicAndFlip(m_pLeverDownLeft, IDB_LEVER_DOWN_RIGHT);
}