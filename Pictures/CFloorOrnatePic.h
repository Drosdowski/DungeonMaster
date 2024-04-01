#pragma once
#include "CBasePictures.h"
class CFloorOrnatePic : public CBasePictures
{
public:
	CFloorOrnatePic(CDC* pDC);
	~CFloorOrnatePic();

	CBitmap* GetPuddlePic(int ebene, int xx);
	CBitmap* GetMossPic(int ebene, int xx);
	CBitmap* GetRoundGratePic(int ebene, int xx);
	CBitmap* GetSquareGratePic(int ebene, int xx);

private:
	void InitOrnatePics();

	CBitmap* m_pPuddleLeft[4];
	CBitmap* m_pPuddleRight[4];
	CBitmap* m_pPuddleFront[4];

	CBitmap* m_pMossLeft[4];
	CBitmap* m_pMossRight[4];
	CBitmap* m_pMossFront[4];

	CBitmap* m_pRoundGrateLeft[4];
	CBitmap* m_pRoundGrateRight[4];
	CBitmap* m_pRoundGrateFront[4];

	CBitmap* m_pSquareGrateLeft[4];
	CBitmap* m_pSquareGrateRight[4];
	CBitmap* m_pSquareGrateFront[4];


};