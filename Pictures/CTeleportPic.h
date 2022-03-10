#pragma once
#include "CBasePictures.h"
class CTeleportPic : public CBasePictures
{
public:
	#define maxPhases 4

	CTeleportPic(CDC* pDC);
	~CTeleportPic();

	CBitmap* GetFrontPic();

private:
	
	void InitPics();
	CBitmap* InitPic(int phase);
	CBitmap* m_pTeleportPic[maxPhases];

	int m_phase;
};

