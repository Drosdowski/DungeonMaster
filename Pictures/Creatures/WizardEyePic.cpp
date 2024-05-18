#include "stdafx.h"
#include "..\..\resource.h"
#include "WizardEyePic.h"

CWizardEyePic::CWizardEyePic(CDC* pDC) : CBasePictures(pDC)
{
	InitPics();
}

CWizardEyePic:: ~CWizardEyePic() {
	for (int flip = 0; flip < 2; flip++)
	{
		delete m_pWizardEyeAttack[flip];
		delete m_pWizardEyeFront[flip];
	}
}

void CWizardEyePic::InitPics() {
	LoadPic(m_pWizardEyeAttack[0], IDB_MONSTER_WIZARDEYE_ATTACK);
	LoadPic(m_pWizardEyeFront[0], IDB_MONSTER_WIZARDEYE_FRONT);

	LoadPicAndFlip(m_pWizardEyeAttack[1], IDB_MONSTER_WIZARDEYE_ATTACK);
	LoadPicAndFlip(m_pWizardEyeFront[1], IDB_MONSTER_WIZARDEYE_FRONT);
}

CBitmap* CWizardEyePic::GetWizardEyePic(bool attacking, int flip) {
	if (attacking) {
		return m_pWizardEyeAttack[flip];
	}
	else {
		return m_pWizardEyeFront[flip];
	}
}

