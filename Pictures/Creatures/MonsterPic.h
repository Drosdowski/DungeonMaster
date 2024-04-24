#pragma once
#include "..\CBasePictures.h"
class CMonster;
class CMummyPic;
class CSkeletonPic;
class CScreamerPic;
class CGhostPic;
class CWizardEyePic;
class CMagentaWormPic;
class CRockPilePic;
class CTrolinPic;
class CGigglerPic;
class CPainRatPic;
class CVexirkPic;
class CRusterPic;
class CSwampSlimePic;
class CWaterElementalPic;
class CBlackFlamePic;
class CMonsterPic : public CBasePictures
{
public:
	CMonsterPic(CDC* pDC);
	~CMonsterPic();

	CBitmap* GetBitmap(CMonster* monster, int richtHero);

private:
	CSkeletonPic* m_pSkeletonPic;
	CMummyPic* m_pMummyPic;
	CGhostPic* m_pGhostPic;
	CWizardEyePic* m_pWIzardEyePic;
	CScreamerPic* m_pScreamerPic;
	CRockPilePic* m_pRockPilePic;
	CMagentaWormPic* m_pMagentaWormPic;
	CTrolinPic* m_pTrolinPic;
	CGigglerPic* m_pGigglerPic;
	CPainRatPic* m_pPainRatPic;
	CVexirkPic* m_pVexirkPic;
	CRusterPic* m_pRusterPic;
	CWaterElementalPic* m_pWaterElementalPic;
	CSwampSlimePic* m_pSwampSlimePic;
	CBlackFlamePic* m_pBlackFlamePic;
};

