#pragma once
#include "..\CBasePictures.h"
class CMonster;
class CMummyPic;
class CSkeletonPic;
class CScreamerPic;
class CMagentaWormPic;
class CRockPilePic;
class CTrolinPic;
class CMonsterPic : public CBasePictures
{
public:
	CMonsterPic(CDC* pDC);
	~CMonsterPic();

	CBitmap* GetBitmap(CMonster* monster, int richtHero);

private:
	CSkeletonPic* m_pSkeletonPic;
	CMummyPic* m_pMummyPic;
	CScreamerPic* m_pScreamerPic;
	CRockPilePic* m_pRockPilePic;
	CMagentaWormPic* m_pMagentaWorm;
	CTrolinPic* m_pTrolin;
};

