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
#include "RedDragonPic.h"
#include "GiantWaspPic.h"
#include "GiantScorpionPic.h"
#include "AnimatedArmourPic.h"
#include "CouatlPic.h"
#include "OituPic.h"
#include "StoneGolemPic.h"
#include "DemonPic.h"
#include "MaterializerPic.h"

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
	m_pRedDragonPic = new CRedDragonPic(pDC);
	m_pGiantWaspPic = new CGiantWaspPic(pDC);
	m_pGiantScorpionPic = new CGiantScorpionPic(pDC);
	m_pAnimatedArmourPic = new CAnimatedArmourPic(pDC);
	m_pCouatlPic = new CCouatlPic(pDC);
	m_pOituPic = new COituPic(pDC);
	m_pStoneGolemPic = new CStoneGolemPic(pDC);
	m_pDemonPic = new CDemonPic(pDC);
	m_pMaterializerPic = new CMaterializerPic(pDC);
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
	delete m_pRedDragonPic;
	delete m_pGiantWaspPic;
	delete m_pGiantScorpionPic;
	delete m_pAnimatedArmourPic;
	delete m_pCouatlPic;
	delete m_pOituPic;
	delete m_pStoneGolemPic;
	delete m_pDemonPic;
	delete m_pMaterializerPic;
}

CBitmap* CMonsterPic::GetBitmap(CMonster* pMonster, int richtHero) {
	int iRicht = (6 - pMonster->GetDirection() + richtHero) % 4;
	int flip = rand() % 2;
	switch (pMonster->getType())
	{
	case MUMMY:
		return m_pMummyPic->GetMummyPic(iRicht, pMonster->isAttacking(), flip);
	case SKELETON:
		return m_pSkeletonPic->GetSkeletonPic(iRicht, pMonster->isAttacking(), flip);
	case WIZARDS_EYE:
		return m_pWIzardEyePic->GetWizardEyePic(pMonster->isAttacking(), flip);
	case SCREAMER:
		return m_pScreamerPic->GetScreamerPic(pMonster->isAttacking(), flip);
	case ROCKPILE:
		return m_pRockPilePic->GetRockPilePic(pMonster->isAttacking(), flip);
	case MAGENTA_WORM:
		return m_pMagentaWormPic->GetMagentaWormPic(pMonster->isAttacking(), flip);
	case TROLIN:
		return m_pTrolinPic->GetTrolinPic(iRicht, pMonster->isAttacking(), flip);
	case GIGGLER:
		return m_pGigglerPic->GetGigglerPic(iRicht, pMonster->isAttacking(), flip);
	case PAINRAT:
		return m_pPainRatPic->GetPainRatPic(iRicht, pMonster->isAttacking(), flip);
	case GHOST:
		return m_pGhostPic->GetGhostPic(pMonster->isAttacking(), flip);
	case VEXIRK:
		return m_pVexirkPic->GetVexirkPic(iRicht, pMonster->isAttacking(), flip);
	case RUSTER:
		return m_pRusterPic->GetRusterPic(iRicht, flip);
	case WATER_ELEMENTAL:
		return m_pWaterElementalPic->GetWaterElementalPic(pMonster->isAttacking(), flip);
	case SWAMP_SLIME:
		return m_pSwampSlimePic->GetSwampSlimePic(pMonster->isAttacking(), flip);
	case BLACK_FLAME:
		return m_pBlackFlamePic->GetBlackFlamePic(pMonster->isAttacking(), flip);
	case RED_DRAGON:
		return m_pRedDragonPic->GetRedDragonPic(iRicht, pMonster->isAttacking(), flip);
	case GIANT_WASP:
		return m_pGiantWaspPic->GetGiantWaspPic(iRicht, pMonster->isAttacking(), flip);
	case GIANT_SCORPION:
		return m_pGiantScorpionPic->GetGiantScorpionPic(iRicht, pMonster->isAttacking(), flip);
	case ANIMATED_ARMOUR:
		return m_pAnimatedArmourPic->GetAnimatedArmourPic(iRicht, pMonster->isAttacking(), flip);
	case COUATL:
		return m_pCouatlPic->GetCouatlPic(iRicht, pMonster->isAttacking(), flip);
	case OITU:
		return m_pOituPic->GetOituPic(iRicht, pMonster->isAttacking(), flip);
	case STONE_GOLEN:
		return m_pStoneGolemPic->GetStoneGolemPic(iRicht, pMonster->isAttacking(), flip);
	case DEMON:
		return m_pDemonPic->GetDemonPic(iRicht, pMonster->isAttacking(), flip);
	case MATERIALIZER:
		return m_pMaterializerPic->GetMaterializerPic(pMonster->isAttacking(), flip);
	default:
		break;
	}
	return NULL;

}