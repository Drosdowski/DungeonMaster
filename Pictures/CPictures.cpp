#include "stdafx.h"
#include "DM.h"
#include "CPictures.h"
#include "Decoration.h"
#include "CLeverPic.h"
#include "CWallPic.h"

CPictures::CPictures(CDC* pDC) : CBasePictures(pDC)
{	
	InitBitmaps();
}

CPictures::~CPictures() 
{

	delete m_pBmpHintergrund;
	delete m_pBmpInversePfeile;
	delete m_pBmpRuck;
	delete m_pBmpKram;
	delete m_pMagicBG;
	delete m_pActionsArea;
	delete m_pActionsDamage;
	delete m_pOneHand;
}


double CPictures::getFaktor(int iEntfernung) {
	if (iEntfernung == 2) return 0.75;
	if (iEntfernung == 3) return 0.5;
	return 1.0;
}


void CPictures::InitBitmaps()
{
	// raus hier -> zu Init Dungeon

	LoadPic(m_pBmpHintergrund, IDB_BITMAP_E);
	LoadPic(m_pBmpInversePfeile, IDB_BITMAP_PINV);

	LoadPic(m_pBmpRuck, IDB_BITMAP_RUCK);
	LoadPic(m_pBmpKram, IDB_BITMAP_KRAM);
	LoadPic(m_pMagicBG, IDB_MAGICBG);
	LoadPic(m_pActionsArea, IDB_ACTIONS_AREA);
	LoadPic(m_pActionsDamage, IDB_ACTIONS_DAMAGE);
	LoadPic(m_pOneHand, IDB_ONE_HAND);

}

CBitmap* CPictures::GetActionDamage(int dmg) {

	// TODO Zahl dazu!
	return m_pActionsDamage;
}