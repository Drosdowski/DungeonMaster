#pragma once
#include "CBasePictures.h"
class CDoor;
class CDoorPic : public CBasePictures
{
public:
	CDoorPic(CDC* pDC);
	~CDoorPic();

	CBitmap* GetDoorFrontPic(CDoor* pDoor, int ebene);
	CBitmap* GetDoorTopPic(int ebene);
	CBitmap* GetDoorFramePic(int ebene, bool left);
	CBitmap* GetButtonPic(int ebene);
	CPoint GetDoorFrontPos(int x, int ebene, CPoint wallPos);
	CPoint GetDoorTopPos(int x, int ebene, CPoint wallPos);
	CPoint GetDoorFramePos(int x, int ebene, bool left, CPoint wallPos);
	CPoint GetButtonPos(int x, int ebene, CPoint wallPos);

private:
	void InitDoors();

	CBitmap* m_pDoorSwitch;
	CBitmap* m_pDoorFrameFront;
	CBitmap* m_pDoorFrameLeft[4];
	CBitmap* m_pDoorFrameRight[4];
	CBitmap* m_pDoorFrameFarLeft;
	CBitmap* m_pDoorFrameFarRight;
	CBitmap* m_pDoorFrontTop[3];
	CBitmap* m_pDoorIron[4];
	CBitmap* m_pDoorIronFull[4];
	CBitmap* m_pDoorWood[4];
	CBitmap* m_pDoorRa[4];
	CBitmap* m_pDoorBlack[4];
	CBitmap* m_pDoorWoodSmashed[4];

};

