#include "stdafx.h"
#include "..\..\resource.h"
#include "MagentaWormPic.h"

CMagentaWormPic::CMagentaWormPic(CDC* pDC) : CBasePictures(pDC)
{
	InitPics();
}

CMagentaWormPic:: ~CMagentaWormPic() {
	for (int flip = 0; flip < 2; flip++)
	{
		delete m_pMagentaWormAttack[flip];
		delete m_pMagentaWormFront[flip];
	}
}

void CMagentaWormPic::InitPics() {
	LoadPic(m_pMagentaWormAttack[0], IDB_MONSTER_WORM_ATTACK);
	LoadPic(m_pMagentaWormFront[0], IDB_MONSTER_WORM_FRONT);

	LoadPicAndFlip(m_pMagentaWormAttack[1], IDB_MONSTER_WORM_ATTACK);
	LoadPicAndFlip(m_pMagentaWormFront[1], IDB_MONSTER_WORM_FRONT);
}

CBitmap* CMagentaWormPic::GetMagentaWormPic(bool attacking, int flip) {
	if (attacking) {
		return m_pMagentaWormAttack[flip];
	}
	else {
		return m_pMagentaWormFront[flip];
	}
}

