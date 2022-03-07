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
		delete m_pPressurePadFront[erbse];
		delete m_pPressurePadLeft[erbse];
		delete m_pPressurePadRight[erbse];
	}
}

void CPressurePadPic::InitPressurePads() {
	LoadPic(m_pPressurePadFront[1], IDB_PRESSURE_PAD_1F); 
	LoadPic(m_pPressurePadLeft[1], IDB_PRESSURE_PAD_1L);
	LoadPicAndFlip(m_pPressurePadRight[1], IDB_PRESSURE_PAD_1L);

	LoadPic(m_pPressurePadFront[2], IDB_PRESSURE_PAD_2F);
	LoadPic(m_pPressurePadLeft[2], IDB_PRESSURE_PAD_2L);
	LoadPicAndFlip(m_pPressurePadRight[2], IDB_PRESSURE_PAD_2L);

	LoadPic(m_pPressurePadFront[3], IDB_PRESSURE_PAD_3F);
	LoadPic(m_pPressurePadLeft[3], IDB_PRESSURE_PAD_3L);
	LoadPicAndFlip(m_pPressurePadRight[3], IDB_PRESSURE_PAD_3L);
}

CBitmap* CPressurePadPic::GetPressurePadPic(int xxx, int ebene) {
	if (ebene > 0) {
		if (xxx == 2) return m_pPressurePadLeft[ebene];
		if (xxx == 3) return m_pPressurePadRight[ebene];
		if (xxx == 4) return m_pPressurePadFront[ebene];
	}
	return NULL;
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