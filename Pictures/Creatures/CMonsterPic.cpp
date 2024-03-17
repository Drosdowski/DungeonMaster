#include "stdafx.h"
#include "..\..\Attributes\CreatureAttributes.h"
#include "..\..\Mobs\Monster.h"
#include "CMonsterPic.h"
#include "CMummyPic.h"
#include "CSkeletonPic.h"
#include "ScreamerPic.h"
#include "GhostPic.h"
#include "RockPilePic.h"
#include "MagentaWormPic.h"
#include "TrolinPic.h"
#include "GigglerPic.h"
#include "RatPic.h"
#include "VexirkPic.h"
#include "RusterPic.h"
#include "WaterElementalPic.h"

CMonsterPic::CMonsterPic(CDC* pDC) : CBasePictures(pDC) {
	m_pMummyPic = new CMummyPic(pDC);
	m_pSkeletonPic = new CSkeletonPic(pDC);
	m_pScreamerPic = new CScreamerPic(pDC);
	m_pGhostPic= new CGhostPic(pDC);
	m_pRockPilePic = new CRockPilePic(pDC);
	m_pMagentaWormPic = new CMagentaWormPic(pDC);
	m_pTrolinPic = new CTrolinPic(pDC);
	m_pGigglerPic = new CGigglerPic(pDC);
	m_pPainRatPic = new CPainRatPic(pDC);
	m_pVexirkPic = new CVexirkPic(pDC);
	m_pRusterPic = new CRusterPic(pDC);
	m_pWaterElementalPic = new CWaterElementalPic(pDC);
}

CMonsterPic::~CMonsterPic() {
	delete m_pSkeletonPic;
	delete m_pMummyPic;
	delete m_pScreamerPic;
	delete m_pGhostPic;
	delete m_pRockPilePic;
	delete m_pMagentaWormPic;
	delete m_pTrolinPic;
	delete m_pGigglerPic;
	delete m_pPainRatPic;
	delete m_pVexirkPic;
	delete m_pRusterPic;
	delete m_pWaterElementalPic;
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
		return m_pMagentaWormPic->GetMagentaWormPic(pMonster->isAttacking());
	case MonsterTyp::TROLIN:
		return m_pTrolinPic->GetTrolinPic(iRicht, pMonster->isAttacking());
	case MonsterTyp::GIGGLER:
		return m_pGigglerPic->GetGigglerPic(iRicht, pMonster->isAttacking());
	case MonsterTyp::PAINRAT:
		return m_pPainRatPic->GetPainRatPic(iRicht, pMonster->isAttacking());
	case MonsterTyp::GHOST:
		return m_pGhostPic->GetGhostPic(pMonster->isAttacking());
	case MonsterTyp::VEXIRK:
		return m_pVexirkPic->GetVexirkPic(iRicht, pMonster->isAttacking());
	case MonsterTyp::RUSTER:
		return m_pRusterPic->GetRusterPic(iRicht);
	case MonsterTyp::WATER_ELEMENTAL:
		return m_pWaterElementalPic->GetWaterElementalPic(pMonster->isAttacking());
	default:
		break;
	}
	return NULL;

}