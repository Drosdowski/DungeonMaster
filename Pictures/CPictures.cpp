#include "stdafx.h"
#include "DM.h"
#include "CPictures.h"
#include "..\SpecialTile\Decoration.h"
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
	for (int i = 1; i < 5; i++) {
		delete m_pWizardTabs[i];
		if (i < 4) {
			delete m_pRunes[i];
		}
	}
	delete m_pActionsArea;
	delete m_pActionsDamage;
	delete m_pOneHand;
}


double CPictures::getFaktor(int iEntfernung) {
	if (iEntfernung == 1) return 1;
	if (iEntfernung == 2) return 0.75;
	if (iEntfernung == 3) return 0.5;
	return 1.5; // todo 1 !
}


void CPictures::InitBitmaps()
{
	// raus hier -> zu Init Dungeon

	LoadPic(m_pBmpHintergrund, IDB_BITMAP_E);
	LoadPic(m_pBmpInversePfeile, IDB_BITMAP_PINV);

	LoadPic(m_pBmpRuck, IDB_BITMAP_RUCK);
	LoadPic(m_pBmpKram, IDB_BITMAP_KRAM);
	LoadPic(m_pRunes[1], IDB_RUNES1);
	LoadPic(m_pRunes[2], IDB_RUNES2);
	LoadPic(m_pRunes[3], IDB_RUNES3);
	LoadPic(m_pWizardTabs[3], IDB_REITER3);
	LoadPic(m_pWizardTabs[4], IDB_REITER4);
	LoadPicAndFlip(m_pWizardTabs[1], IDB_REITER4);
	LoadPicAndFlip(m_pWizardTabs[2], IDB_REITER3);
	LoadPic(m_pActionsArea, IDB_ACTIONS_AREA);
	LoadPic(m_pActionsDamage, IDB_ACTIONS_DAMAGE);
	LoadPic(m_pOneHand, IDB_ONE_HAND);

}

CBitmap* CPictures::GetActionDamage(int dmg) {

	// TODO Zahl dazu!
	return m_pActionsDamage;
}