#pragma once
#include "..\CBasePictures.h"
class CMonster;
class CMummyPic;
class CSkeletonPic;
class CScreamerPic;
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
};

