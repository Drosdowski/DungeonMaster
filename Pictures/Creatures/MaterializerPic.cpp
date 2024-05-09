#include "stdafx.h"
#include "..\..\resource.h"
#include "MaterializerPic.h"

CMaterializerPic::CMaterializerPic(CDC* pDC) : CBasePictures(pDC)
{
	InitPics();
	m_iPhase = 2;
}

CMaterializerPic:: ~CMaterializerPic() {
	delete m_pMaterializerAttack;
	for (int phase = 0; phase < 3; phase++)
	{
		delete m_pMaterializerFront[phase];
	}
}


void CMaterializerPic::InitPics() {

	LoadPic(m_pMaterializerAttack, IDB_MONSTER_MATERIALIZER_ATTACK);
	LoadPic(m_pMaterializerFront[0], IDB_MONSTER_MATERIALIZER_FRONT1);
	LoadPic(m_pMaterializerFront[1], IDB_MONSTER_MATERIALIZER_FRONT2);
	LoadPic(m_pMaterializerFront[2], IDB_MONSTER_MATERIALIZER_FRONT3);
}

CBitmap* CMaterializerPic::GetMaterializerPic(bool attacking) {
	if (attacking) {
		return m_pMaterializerAttack;
	}
	else {
		return m_pMaterializerFront[m_iPhase];
		if (m_iPhase > 0) {
			m_iPhase--;
		}
		else {
			m_iPhase = 2;
		}
	}
}

