#include "stdafx.h"
#include "..\..\resource.h"
#include "ScreamerPic.h"

CScreamerPic::CScreamerPic(CDC* pDC) : CBasePictures(pDC)
{
	InitPics();
}

CScreamerPic:: ~CScreamerPic() {
	delete m_pScreamerAttack;
	delete m_pScreamerFront;
}


void CScreamerPic::InitPics() {

	LoadPic(m_pScreamerAttack, IDB_MONSTER_SCREAMER_ATTACK);
	LoadPic(m_pScreamerFront, IDB_MONSTER_SCREAMER_FRONT);
}

CBitmap* CScreamerPic::GetScreamerPic(bool attacking) {
	if (attacking) {
		return m_pScreamerAttack;
	}
	else {
		return m_pScreamerFront;
	}
}

