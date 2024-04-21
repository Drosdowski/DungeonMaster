#include "stdafx.h"
#include "..\..\resource.h"
#include "WizardEyePic.h"

CWizardEyePic::CWizardEyePic(CDC* pDC) : CBasePictures(pDC)
{
	InitPics();
}

CWizardEyePic:: ~CWizardEyePic() {
	delete m_pWizardEyeAttack;
	delete m_pWizardEyeFront;
}


void CWizardEyePic::InitPics() {

	LoadPic(m_pWizardEyeAttack, IDB_MONSTER_WIZARDEYE_ATTACK);
	LoadPic(m_pWizardEyeFront, IDB_MONSTER_WIZARDEYE_FRONT);
}

CBitmap* CWizardEyePic::GetWizardEyePic(bool attacking) {
	if (attacking) {
		return m_pWizardEyeAttack;
	}
	else {
		return m_pWizardEyeFront;
	}
}

