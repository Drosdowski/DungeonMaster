#include "stdafx.h"
#include "..\..\Mobs\Monster.h"
#include "CMonsterPic.h"
#include "CMummyPic.h"
#include "CSkeletonPic.h"

CMonsterPic::CMonsterPic(CDC* pDC) : CBasePictures(pDC) {
	m_pMummyPic = new CMummyPic(pDC);
	m_pSkeletonPic = new CSkeletonPic(pDC);
}

CMonsterPic::~CMonsterPic() {
	delete m_pSkeletonPic;
	delete m_pMummyPic;
}

CBitmap* CMonsterPic::GetBitmap(CMonster* pMonster, int richtHero) {
	int iRicht = (6 - pMonster->m_chrDirection + richtHero) % 4;
	switch (pMonster->getType())
	{
	case CMonster::MonsterTyp::MUMIE:
		return m_pMummyPic->GetMummyPic(iRicht, pMonster->isAttacking());
	case CMonster::MonsterTyp::SKELETT:
		return m_pSkeletonPic->GetSkeletonPic(iRicht, pMonster->isAttacking());
	default:
		break;
	}
	return NULL;

}