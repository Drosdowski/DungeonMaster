#include "stdafx.h"
#include "..\resource.h"
#include "CLeverPic.h"

CLeverPic::CLeverPic(CDC* pDC) : CBasePictures(pDC)
{
	InitLevers();
}

CLeverPic:: ~CLeverPic() {
	delete m_pLeverUpFront;
	delete m_pLeverUpRight;
	delete m_pLeverUpLeft;
	delete m_pLeverDownFront;
	delete m_pLeverDownRight;
	delete m_pLeverDownLeft;
}


void CLeverPic::InitLevers() {

	LoadPic(m_pLeverUpFront, IDB_LEVER_UP_FRONT);
	LoadPic(m_pLeverUpRight, IDB_LEVER_UP_RIGHT);
	LoadPicAndFlip(m_pLeverUpLeft, IDB_LEVER_UP_RIGHT);
	LoadPic(m_pLeverDownFront, IDB_LEVER_DOWN_FRONT);
	LoadPic(m_pLeverDownRight, IDB_LEVER_DOWN_RIGHT);
	LoadPicAndFlip(m_pLeverDownLeft, IDB_LEVER_DOWN_RIGHT);
}

CBitmap* CLeverPic::GetLeverFront(int state) {
	if (state == 0) {
		return m_pLeverUpFront;
	}
	else {
		return m_pLeverDownFront;
	}
}

CBitmap* CLeverPic::GetLeverSide(int state, bool left) {
	if (state == 0) {
		if (left)
			return m_pLeverUpLeft;
		else
			return m_pLeverUpRight;
	}
	else {
		if (left)
			return m_pLeverDownLeft;
		else
			return m_pLeverDownRight;
	}
}