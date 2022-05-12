#include "stdafx.h"
#include "..\..\Mobs\Monster.h"
#include "CMonsterPic.h"
#include "CMummyPic.h"
#include "CSkeletonPic.h"
#include "ScreamerPic.h"

CMonsterPic::CMonsterPic(CDC* pDC) : CBasePictures(pDC) {
	m_pMummyPic = new CMummyPic(pDC);
	m_pSkeletonPic = new CSkeletonPic(pDC);
	m_pScreamerPic = new CScreamerPic(pDC);
}

CMonsterPic::~CMonsterPic() {
	delete m_pSkeletonPic;
	delete m_pMummyPic;
	delete m_pScreamerPic;
}

CBitmap* CMonsterPic::GetBitmap(CMonster* pMonster, int richtHero) {
	int iRicht = (6 - pMonster->GetDirection() + richtHero) % 4;
	switch (pMonster->getType())
	{
	case CMonster::MonsterTyp::MUMMY:
		return m_pMummyPic->GetMummyPic(iRicht, pMonster->isAttacking());
	case CMonster::MonsterTyp::SKELETON:
		return m_pSkeletonPic->GetSkeletonPic(iRicht, pMonster->isAttacking());
	case CMonster::MonsterTyp::SCREAMER:
		return m_pScreamerPic->GetScreamerPic(pMonster->isAttacking());
	default:
		break;
	}
	return NULL;

}