#include "stdafx.h"
#include "..\..\resource.h"
#include "MagentaWormPic.h"

CMagentaWormPic::CMagentaWormPic(CDC* pDC) : CBasePictures(pDC)
{
	InitPics();
}

CMagentaWormPic:: ~CMagentaWormPic() {
	delete m_pMagentaWormAttack;
	delete m_pMagentaWormFront;
}


void CMagentaWormPic::InitPics() {

	LoadPic(m_pMagentaWormAttack, IDB_MONSTER_WORM_ATTACK);
	LoadPic(m_pMagentaWormFront, IDB_MONSTER_WORM_FRONT);
}

CBitmap* CMagentaWormPic::GetMagentaWormPic(bool attacking) {
	if (attacking) {
		return m_pMagentaWormAttack;
	}
	else {
		return m_pMagentaWormFront;
	}
}

