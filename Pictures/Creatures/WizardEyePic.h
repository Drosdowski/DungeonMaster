#pragma once
#include "..\CBasePictures.h"
class CWizardEyePic : public CBasePictures
{
public:
	CWizardEyePic(CDC* pDC);
	~CWizardEyePic();

	CBitmap* GetWizardEyePic(bool attacking, int flip);

private:
	void InitPics();

	CBitmap* m_pWizardEyeFront[2];
	CBitmap* m_pWizardEyeAttack[2];

};

