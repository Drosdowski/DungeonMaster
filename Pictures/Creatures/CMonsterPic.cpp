#include "stdafx.h"
#include "..\..\Attributes\CCreatureAttributes.h"
#include "..\..\Mobs\Monster.h"
#include "CMonsterPic.h"
#include "CMummyPic.h"
#include "CSkeletonPic.h"
#include "ScreamerPic.h"
#include "RockPilePic.h"
#include "MagentaWormPic.h"
#include "TrolinPic.h"

CMonsterPic::CMonsterPic(CDC* pDC) : CBasePictures(pDC) {
	m_pMummyPic = new CMummyPic(pDC);
	m_pSkeletonPic = new CSkeletonPic(pDC);
	m_pScreamerPic = new CScreamerPic(pDC);
	m_pRockPilePic = new CRockPilePic(pDC);
	m_pMagentaWorm = new CMagentaWormPic(pDC);
	m_pTrolin = new CTrolinPic(pDC);
}

CMonsterPic::~CMonsterPic() {
	delete m_pSkeletonPic;
	delete m_pMummyPic;
	delete m_pScreamerPic;
	delete m_pRockPilePic;
	delete m_pMagentaWorm;
	delete m_pTrolin;
}

CBitmap* CMonsterPic::GetBitmap(CMonster* pMonster, int richtHero) {
	int iRicht = (6 - pMonster->GetDirection() + richtHero) % 4;
	switch (pMonster->getType())
	{
	case MonsterTyp::MUMMY:
		return m_pMummyPic->GetMummyPic(iRicht, pMonster->isAttacking());
	case MonsterTyp::SKELETON:
		return m_pSkeletonPic->GetSkeletonPic(iRicht, pMonster->isAttacking());
	case MonsterTyp::SCREAMER:
		return m_pScreamerPic->GetScreamerPic(pMonster->isAttacking());
	case MonsterTyp::ROCKPILE:
		return m_pRockPilePic->GetRockPilePic(pMonster->isAttacking());
	case MonsterTyp::MAGENTA_WORM:
		return m_pMagentaWorm->GetMagentaWormPic(pMonster->isAttacking());
	case MonsterTyp::TROLIN:
		return m_pTrolin->GetTrolinPic(iRicht, pMonster->isAttacking());
	default:
		break;
	}
	return NULL;

}