#include "stdafx.h"
#include "..\resource.h"
#include "CDoorPic.h"
#include "..\SpecialTile\CDoor.h"

CDoorPic::CDoorPic(CDC* pDC) : CBasePictures(pDC)
{
	InitDoors();
}

CDoorPic::~CDoorPic()
{
	delete m_pDoorFrameFront;
	for (int zwiebel = 1; zwiebel < 4; zwiebel++) {
		delete m_pDoorFrameLeft[zwiebel];
		delete m_pDoorFrameRight[zwiebel];
		delete m_pDoorIron[zwiebel];
		delete m_pDoorWood[zwiebel];
	}
	delete m_pDoorFrameFarLeft;
	delete m_pDoorFrameFarRight;
	delete m_pDoorFrontTop[1];
	delete m_pDoorFrontTop[2];
	delete m_pDoorSwitch;
	delete m_pDoorWoodSmashed;
}

CBitmap* CDoorPic::GetDoorFrontPic(CDoor* pDoor, int ebene) {

	if (ebene > 0)
	{
		if (pDoor->getType() == CDoorAttributes::DoorType::Iron)
			return m_pDoorIron[ebene];
		if (pDoor->getType() == CDoorAttributes::DoorType::Wood)
			if (pDoor->getState() == CDoor::DESTROYED)
				return m_pDoorWoodSmashed;
			else
				return m_pDoorWood[ebene];

		else
			return NULL;
	}
	else
		return m_pDoorFrameFront;
}

CBitmap* CDoorPic::GetDoorTopPic(int ebene) {
	if (ebene == 1 || ebene == 2) {
		return m_pDoorFrontTop[ebene];
	}
	else
		return NULL;
}

CBitmap* CDoorPic::GetDoorFramePic(int ebene, bool left) {
	if (left) {
		return m_pDoorFrameLeft[ebene];
	}
	else {
		return m_pDoorFrameRight[ebene];
	}
}

CBitmap* CDoorPic::GetButtonPic(int ebene) {
	return m_pDoorSwitch;
}

CPoint CDoorPic::GetButtonPos(int x, int ebene, CPoint wallPos) {
	switch (ebene)
	{
	case 1:
		if (x == 2 || x == 4)
			return CPoint(wallPos.x + 128 * 2, wallPos.y + 34 * 2);
		break;
	case 2:
		if (x == 2 || x == 4)   
			return CPoint(wallPos.x + 84 * 2, wallPos.y + 22 * 2);
		break;
	case 3:
		if (x != 1) 
			return CPoint(wallPos.x + 57 * 2, wallPos.y + 15 * 2);
		break;
	}
	return CPoint(0, 0);
}


CPoint CDoorPic::GetDoorFrontPos(int x, int ebene, CPoint wallPos) {
	
	switch (ebene)
	{
	case 0:
		if (x == 4) return CPoint(wallPos.x + 96 * 2, wallPos.y);
		break;
	case 1:
		if (x == 2) return CPoint(-32 * 2, wallPos.y + 8 * 2);
		if (x == 3) return CPoint(wallPos.x + 32 * 2, wallPos.y + 8 * 2);
		if (x == 4) return CPoint(wallPos.x + 32 * 2, wallPos.y + 8 * 2);
		break;
	case 2:
		if (x == 2) return CPoint(wallPos.x, wallPos.y + 5 * 2);
		if (x > 1)	return CPoint(wallPos.x + 21 * 2, wallPos.y + 5 * 2);
		break;
	case 3:
		if (x == 0) return CPoint(wallPos.x, wallPos.y + 2 * 2);
		return CPoint(wallPos.x + 11 * 2, wallPos.y + 2 * 2);
	}
	return CPoint(0, 0);
}

CPoint CDoorPic::GetDoorFramePos(int x, int ebene, bool left, CPoint wallPos) {
	switch (ebene)
	{
	case 0:
		if (x == 4) return CPoint(64 * 2, 0); // Innenrahmen
	case 1:
		if (left && (x == 3 || x == 4))
			return CPoint(wallPos.x + 12 * 2, wallPos.y + 4 * 2);
		else if (!left && x == 2 || x == 4)
			return CPoint(wallPos.x + 116 * 2, wallPos.y + 4 * 2);
		break;
	case 2:
		if (left && (x == 3 || x == 4))  return CPoint(wallPos.x + 4 * 2, wallPos.y + 2 * 2);
		else if (!left && x == 2 || x == 4)   return CPoint(wallPos.x + 81 * 2, wallPos.y + 2 * 2);
		break;
	case 3:
		if (left && x > 0) return CPoint(wallPos.x, wallPos.y + 2 * 2);
		else if (!left && x != 1) return CPoint(wallPos.x + 57 * 2, wallPos.y + 2 * 2);
		break;
	}
	return CPoint(0, 0);
}


CPoint CDoorPic::GetDoorTopPos(int x, int ebene, CPoint wallPos) {
	switch (ebene)
	{
	case 0:
		break;
	case 1:
		if (x == 2) return CPoint(-16 * 2, wallPos.y + 3 * 2);
		if (x == 3) return CPoint(wallPos.x + 16 * 2, wallPos.y + 3 * 2);
		if (x == 4) return CPoint(wallPos.x + 12 * 2, wallPos.y + 3 * 2);
		break;
	case 2:
		return CPoint(wallPos.x + 6 * 2, wallPos.y);
	case 3:
		break;
	}
	return CPoint(0, 0);
}

void CDoorPic::InitDoors() {
	LoadPic(m_pDoorFrameFront, IDB_DOOR_FRAME_0); // Ansicht Tür von innen zur Seite gedreht
	LoadPic(m_pDoorFrameLeft[1], IDB_DOOR_FRAME_1L);
	LoadPic(m_pDoorFrameLeft[2], IDB_DOOR_FRAME_2L);
	LoadPic(m_pDoorFrameLeft[3], IDB_DOOR_FRAME_3L);
	LoadPic(m_pDoorFrameFarLeft, IDB_DOOR_FRAME_3FL);
	LoadPicAndFlip(m_pDoorFrameRight[1], IDB_DOOR_FRAME_1L);
	LoadPicAndFlip(m_pDoorFrameRight[2], IDB_DOOR_FRAME_2L);
	LoadPicAndFlip(m_pDoorFrameRight[3], IDB_DOOR_FRAME_3L);
	LoadPicAndFlip(m_pDoorFrameFarRight, IDB_DOOR_FRAME_3FL);
	LoadPic(m_pDoorFrontTop[1], IDB_DOOR_FRONT_1T);
	LoadPic(m_pDoorFrontTop[2], IDB_DOOR_FRONT_2T);
	LoadPic(m_pDoorIron[1], IDB_DOOR_IRON_1);
	LoadPic(m_pDoorIron[2], IDB_DOOR_IRON_2);
	LoadPic(m_pDoorIron[3], IDB_DOOR_IRON_3);
	LoadPic(m_pDoorWood[1], IDB_DOOR_WOOD_1);
	LoadPic(m_pDoorWood[2], IDB_DOOR_WOOD_2);
	LoadPic(m_pDoorWood[3], IDB_DOOR_WOOD_3);
	LoadPic(m_pDoorWoodSmashed, IDB_DOOR_WOOD_BASHED);
	LoadPic(m_pDoorSwitch, IDB_DOOR_SWITCH);
}