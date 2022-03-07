#pragma once
#include "CBasePictures.h"
class CFloorOrnatePic : public CBasePictures
{
public:
	CFloorOrnatePic(CDC* pDC);
	~CFloorOrnatePic();

	CBitmap* GetPuddlePic(int ebene, int xx);
	CBitmap* GetMossPic(int ebene, int xx);

	//CPoint GetPos(int x, int ebene);

private:
	void InitOrnatePics();

	CBitmap* m_pPuddleLeft[4];
	CBitmap* m_pPuddleRight[4];
	CBitmap* m_pPuddleFront[4];

	CBitmap* m_pMossLeft[4];
	CBitmap* m_pMossRight[4];
	CBitmap* m_pMossFront[4];

};