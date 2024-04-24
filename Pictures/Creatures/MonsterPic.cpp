#include "stdafx.h"
#include "..\..\Attributes\CreatureAttributes.h"
#include "..\..\Mobs\Monster.h"
#include "MonsterPic.h"
#include "MummyPic.h"
#include "SkeletonPic.h"
#include "ScreamerPic.h"
#include "GhostPic.h"
#include "WizardEyePic.h"
#include "RockPilePic.h"
#include "MagentaWormPic.h"
#include "TrolinPic.h"
#include "GigglerPic.h"
#include "RatPic.h"
#include "VexirkPic.h"
#include "RusterPic.h"
#include "WaterElementalPic.h"
#include "SwampSlimePic.h"
#include "BlackFlamePic.h"

CMonsterPic::CMonsterPic(CDC* pDC) : CBasePictures(pDC) {
	m_pMummyPic = new CMummyPic(pDC);
	m_pSkeletonPic = new CSkeletonPic(pDC);
	m_pScreamerPic = new CScreamerPic(pDC);
	m_pGhostPic= new CGhostPic(pDC);
	m_pWIzardEyePic = new CWizardEyePic(pDC);
	m_pRockPilePic = new CRockPilePic(pDC);
	m_pMagentaWormPic = new CMagentaWormPic(pDC);
	m_pTrolinPic = new CTrolinPic(pDC);
	m_pGigglerPic = new CGigglerPic(pDC);
	m_pPainRatPic = new CPainRatPic(pDC);
	m_pVexirkPic = new CVexirkPic(pDC);
	m_pRusterPic = new CRusterPic(pDC);
	m_pWaterElementalPic = new CWaterElementalPic(pDC);
	m_pSwampSlimePic = new CSwampSlimePic(pDC);
	m_pBlackFlamePic = new CBlackFlamePic(pDC);
}

CMonsterPic::~CMonsterPic() {
	delete m_pSkeletonPic;
	delete m_pMummyPic;
	delete m_pScreamerPic;
	delete m_pGhostPic;
	delete m_pWIzardEyePic;
	delete m_pRockPilePic;
	delete m_pMagentaWormPic;
	delete m_pTrolinPic;
	delete m_pGigglerPic;
	delete m_pPainRatPic;
	delete m_pVexirkPic;
	delete m_pRusterPic;
	delete m_pWaterElementalPic;
	delete m_pSwampSlimePic;
	delete m_pBlackFlamePic;
}

CBitmap* CMonsterPic::GetBitmap(CMonster* pMonster, int richtHero) {
	int iRicht = (6 - pMonster->GetDirection() + richtHero) % 4;
	switch (pMonster->getType())
	{
	case MUMMY:
		return m_pMummyPic->GetMummyPic(iRicht, pMonster->isAttacking());
	case SKELETON:
		return m_pSkeletonPic->GetSkeletonPic(iRicht, pMonster->isAttacking());
	case WIZARDS_EYE:
		return m_pWIzardEyePic->GetWizardEyePic(pMonster->isAttacking());
	case SCREAMER:
		return m_pScreamerPic->GetScreamerPic(pMonster->isAttacking());
	case ROCKPILE:
		return m_pRockPilePic->GetRockPilePic(pMonster->isAttacking());
	case MAGENTA_WORM:
		return m_pMagentaWormPic->GetMagentaWormPic(pMonster->isAttacking());
	case TROLIN:
		return m_pTrolinPic->GetTrolinPic(iRicht, pMonster->isAttacking());
	case GIGGLER:
		return m_pGigglerPic->GetGigglerPic(iRicht, pMonster->isAttacking());
	case PAINRAT:
		return m_pPainRatPic->GetPainRatPic(iRicht, pMonster->isAttacking());
	case GHOST:
		return m_pGhostPic->GetGhostPic(pMonster->isAttacking());
	case VEXIRK:
		return m_pVexirkPic->GetVexirkPic(iRicht, pMonster->isAttacking());
	case RUSTER:
		return m_pRusterPic->GetRusterPic(iRicht);
	case WATER_ELEMENTAL:
		return m_pWaterElementalPic->GetWaterElementalPic(pMonster->isAttacking());
	case SWAMP_SLIME:
		return m_pSwampSlimePic->GetSwampSlimePic(pMonster->isAttacking());
	case BLACK_FLAME:
		return m_pBlackFlamePic->GetBlackFlamePic(pMonster->isAttacking());

	default:
		break;
	}
	return NULL;

}