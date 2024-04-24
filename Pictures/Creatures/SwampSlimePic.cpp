#include "stdafx.h"
#include "..\..\resource.h"
#include "SwampSlimePic.h"


CSwampSlimePic::CSwampSlimePic(CDC* pDC) : CBasePictures(pDC)
{
	InitPics();
}

CSwampSlimePic:: ~CSwampSlimePic() {
	delete m_pSwampSlimeAttack;
	delete m_pSwampSlimeFront;
}


void CSwampSlimePic::InitPics() {

	LoadPic(m_pSwampSlimeAttack, IDB_MONSTER_SWAMPSLIME_ATTACK);
	LoadPic(m_pSwampSlimeFront, IDB_MONSTER_SWAMPSLIME_FRONT);
}

CBitmap* CSwampSlimePic::GetSwampSlimePic(bool attacking) {
	if (attacking) {
		return m_pSwampSlimeAttack;
	}
	else {
		return m_pSwampSlimeFront;
	}
}

