#pragma once
#include "..\CBasePictures.h"
class CWizardEyePic : public CBasePictures
{
public:
	CWizardEyePic(CDC* pDC);
	~CWizardEyePic();

	CBitmap* GetWizardEyePic(bool attacking);

private:
	void InitPics();

	CBitmap* m_pWizardEyeFront;
	CBitmap* m_pWizardEyeAttack;

};

