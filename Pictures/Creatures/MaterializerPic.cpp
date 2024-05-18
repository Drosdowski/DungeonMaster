#include "stdafx.h"
#include "..\..\resource.h"
#include "MaterializerPic.h"

CMaterializerPic::CMaterializerPic(CDC* pDC) : CBasePictures(pDC)
{
	InitPics();
	m_iPhase = 2;
}

CMaterializerPic:: ~CMaterializerPic() {
	for (int flip = 0; flip < 2; flip++)
	{
		delete m_pMaterializerAttack[flip];
		for (int phase = 0; phase < 3; phase++)
		{
			delete m_pMaterializerFront[phase][flip];
		}
	}
}

void CMaterializerPic::InitPics() {
	LoadPic(m_pMaterializerAttack[0], IDB_MONSTER_MATERIALIZER_ATTACK);
	LoadPic(m_pMaterializerFront[0][0], IDB_MONSTER_MATERIALIZER_FRONT1);
	LoadPic(m_pMaterializerFront[1][0], IDB_MONSTER_MATERIALIZER_FRONT2);
	LoadPic(m_pMaterializerFront[2][0], IDB_MONSTER_MATERIALIZER_FRONT3);

	LoadPicAndFlip(m_pMaterializerAttack[1], IDB_MONSTER_MATERIALIZER_ATTACK);
	LoadPicAndFlip(m_pMaterializerFront[0][1], IDB_MONSTER_MATERIALIZER_FRONT1);
	LoadPicAndFlip(m_pMaterializerFront[1][1], IDB_MONSTER_MATERIALIZER_FRONT2);
	LoadPicAndFlip(m_pMaterializerFront[2][1], IDB_MONSTER_MATERIALIZER_FRONT3);
}

CBitmap* CMaterializerPic::GetMaterializerPic(bool attacking, int flip) {
	if (attacking) {
		return m_pMaterializerAttack[flip];
	}
	else {
		return m_pMaterializerFront[m_iPhase][flip];
		if (m_iPhase > 0) {
			m_iPhase--;
		}
		else {
			m_iPhase = 2;
		}
	}
}

