#include "stdafx.h"
#include "..\resource.h"
#include "CPressurePadPic.h"

CPressurePadPic::CPressurePadPic(CDC* pDC) : CBasePictures(pDC)
{
	InitPressurePads();
}

CPressurePadPic::~CPressurePadPic()
{
	for (int erbse = 1; erbse < 4; erbse++) {
		delete m_pSquarePressurePadFront[erbse];
		delete m_pSquarePressurePadLeft[erbse];
		delete m_pSquarePressurePadRight[erbse];

		delete m_pRoundPressurePadFront[erbse];
		delete m_pRoundPressurePadLeft[erbse];
		delete m_pRoundPressurePadRight[erbse];
	}
}

void CPressurePadPic::InitPressurePads() {
	LoadPic(m_pSquarePressurePadFront[1], IDB_FLOOR_SQUARE_PRESSURE_PAD_F1); 
	LoadPic(m_pSquarePressurePadLeft[1], IDB_FLOOR_SQUARE_PRESSURE_PAD_L1);
	LoadPicAndFlip(m_pSquarePressurePadRight[1], IDB_FLOOR_SQUARE_PRESSURE_PAD_L1);

	LoadPic(m_pSquarePressurePadFront[2], IDB_FLOOR_SQUARE_PRESSURE_PAD_F2);
	LoadPic(m_pSquarePressurePadLeft[2], IDB_FLOOR_SQUARE_PRESSURE_PAD_L2);
	LoadPicAndFlip(m_pSquarePressurePadRight[2], IDB_FLOOR_SQUARE_PRESSURE_PAD_L2);

	LoadPic(m_pSquarePressurePadFront[3], IDB_FLOOR_SQUARE_PRESSURE_PAD_F3);
	LoadPic(m_pSquarePressurePadLeft[3], IDB_FLOOR_SQUARE_PRESSURE_PAD_L3);
	LoadPicAndFlip(m_pSquarePressurePadRight[3], IDB_FLOOR_SQUARE_PRESSURE_PAD_L3);

	LoadPic(m_pRoundPressurePadFront[1], IDB_FLOOR_ROUND_PRESSURE_PAD_F1);
	LoadPic(m_pRoundPressurePadLeft[1], IDB_FLOOR_ROUND_PRESSURE_PAD_L1);
	LoadPicAndFlip(m_pRoundPressurePadRight[1], IDB_FLOOR_ROUND_PRESSURE_PAD_F1);

	LoadPic(m_pRoundPressurePadFront[2], IDB_FLOOR_ROUND_PRESSURE_PAD_F2);
	LoadPic(m_pRoundPressurePadLeft[2], IDB_FLOOR_ROUND_PRESSURE_PAD_L2);
	LoadPicAndFlip(m_pRoundPressurePadRight[2], IDB_FLOOR_ROUND_PRESSURE_PAD_L2);

	LoadPic(m_pRoundPressurePadFront[3], IDB_FLOOR_ROUND_PRESSURE_PAD_F3);
	LoadPic(m_pRoundPressurePadLeft[3], IDB_FLOOR_ROUND_PRESSURE_PAD_L3);
	LoadPicAndFlip(m_pRoundPressurePadRight[3], IDB_FLOOR_ROUND_PRESSURE_PAD_L3);
}

CBitmap* CPressurePadPic::GetPressurePadPic(int xxx, int ebene, boolean isRound) {
	if (ebene > 0) {
		if (xxx == 2) return isRound ? m_pRoundPressurePadLeft[ebene] : m_pSquarePressurePadLeft[ebene];
		if (xxx == 3) return isRound ? m_pRoundPressurePadRight[ebene] : m_pSquarePressurePadRight[ebene];
		if (xxx == 4) return isRound ? m_pRoundPressurePadFront[ebene] : m_pSquarePressurePadFront[ebene];
	}
	return NULL;
}

CPoint CPressurePadPic::GetCeilingPos(int x, int ebene) {
	CPoint middle;
	middle.x = GetPos(x, ebene).x;

	switch (ebene) {
	case 0:
		middle.y = 68; break;
	case 1:
		middle.y = 82; break;
	case 2:
		middle.y = 102;	break;
	case 3:
		middle.y = 115; break;
	}
	return middle;
}

CPoint CPressurePadPic::GetPos(int x, int ebene) {
	CPoint middle;
	switch (x) {
	case 2:
		if (ebene == 1) middle.x = 20;
		if (ebene == 2) middle.x = 90;
		break;
	case 3:
		if (ebene == 1) middle.x = 418; // tuned for pressure plate
		if (ebene == 2) middle.x = 360;
		break;
	case 4:
		middle.x = 225;
		break;
	}
	if (middle.x != 0) {
		switch (ebene) {
		case 0:
			// nur oben links / rechts
			middle.y = 325; break;
		case 1:
			middle.y = 290; break;
		case 2:
			middle.y = 235;	break;
		case 3:
			middle.y = 200; break;
		}
	}

	return middle;
}