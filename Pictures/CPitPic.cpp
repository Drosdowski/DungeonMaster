#include "stdafx.h"
#include "..\resource.h"
#include "CPitPic.h"

CPitPic::CPitPic(CDC* pDC) : CBasePictures(pDC)
{
	InitPitPics();
}

CPitPic::~CPitPic()
{
	for (int gurke = 0; gurke < 4; gurke++) {
		delete m_pPitLeft[gurke];
		delete m_pPitRight[gurke];
		delete m_pPitFront[gurke];

		if (gurke < 3) {

			delete m_pPitInvLeft[gurke];
			delete m_pPitInvRight[gurke];
			delete m_pPitInvFront[gurke];

			delete m_pPitCeilingLeft[gurke];
			delete m_pPitCeilingRight[gurke];
			delete m_pPitCeilingFront[gurke];
		}
	}
}

CBitmap* CPitPic::GetPitPic(int ebene, int xxx) {	
	if (xxx == 2) return m_pPitLeft[ebene];
	if (xxx == 3) return m_pPitRight[ebene];
	if (xxx == 4) return m_pPitFront[ebene];
	return NULL;
}

CBitmap* CPitPic::GetInvPitPic(int ebene, int xxx) {
	if (ebene < 3) {
		if (xxx == 2) return m_pPitInvLeft[ebene];
		if (xxx == 3) return m_pPitInvRight[ebene];
		if (xxx == 4) return m_pPitInvFront[ebene];
	}
	return NULL;
}

CBitmap* CPitPic::GetPitCeilingPic(int ebene, int xxx) {
	if (ebene < 3) {
		if (xxx == 2) return m_pPitCeilingLeft[ebene];
		if (xxx == 3) return m_pPitCeilingRight[ebene];
		if (xxx == 4) return m_pPitCeilingFront[ebene];
	}
	return NULL;
}

void CPitPic::InitPitPics() {
	LoadPic(m_pPitFront[0], IDB_FLOOR_PIT_F0);
	LoadPic(m_pPitLeft[0], IDB_FLOOR_PIT_L0);
	LoadPicAndFlip(m_pPitRight[0], IDB_FLOOR_PIT_L0);

	LoadPic(m_pPitInvFront[0], IDB_FLOOR_PIT_INV_F0);
	LoadPic(m_pPitInvLeft[0], IDB_FLOOR_PIT_INV_L0);
	LoadPicAndFlip(m_pPitInvRight[0], IDB_FLOOR_PIT_INV_L0);

	LoadPic(m_pPitCeilingFront[0], IDB_FLOOR_PIT_CEILING_F0);
	LoadPic(m_pPitCeilingLeft[0], IDB_FLOOR_PIT_CEILING_L0);
	LoadPicAndFlip(m_pPitCeilingRight[0], IDB_FLOOR_PIT_CEILING_L0);



	LoadPic(m_pPitFront[1], IDB_FLOOR_PIT_F1);
	LoadPic(m_pPitLeft[1], IDB_FLOOR_PIT_L1);
	LoadPicAndFlip(m_pPitRight[1], IDB_FLOOR_PIT_L1);

	LoadPic(m_pPitInvFront[1], IDB_FLOOR_PIT_INV_F1);
	LoadPic(m_pPitInvLeft[1], IDB_FLOOR_PIT_INV_L1);
	LoadPicAndFlip(m_pPitInvRight[1], IDB_FLOOR_PIT_INV_L1);

	LoadPic(m_pPitCeilingFront[1], IDB_FLOOR_PIT_CEILING_F1);
	LoadPic(m_pPitCeilingLeft[1], IDB_FLOOR_PIT_CEILING_L1);
	LoadPicAndFlip(m_pPitCeilingRight[1], IDB_FLOOR_PIT_CEILING_L1);



	LoadPic(m_pPitFront[2], IDB_FLOOR_PIT_F2);
	LoadPic(m_pPitLeft[2], IDB_FLOOR_PIT_L2);
	LoadPicAndFlip(m_pPitRight[2], IDB_FLOOR_PIT_L2);

	LoadPic(m_pPitInvFront[2], IDB_FLOOR_PIT_INV_F2);
	LoadPic(m_pPitInvLeft[2], IDB_FLOOR_PIT_INV_L2);
	LoadPicAndFlip(m_pPitInvRight[2], IDB_FLOOR_PIT_INV_L2);

	LoadPic(m_pPitCeilingFront[2], IDB_FLOOR_PIT_CEILING_F2);
	LoadPic(m_pPitCeilingLeft[2], IDB_FLOOR_PIT_CEILING_L2);
	LoadPicAndFlip(m_pPitCeilingRight[2], IDB_FLOOR_PIT_CEILING_L2);



	LoadPic(m_pPitFront[3], IDB_FLOOR_PIT_F3);
	LoadPic(m_pPitLeft[3], IDB_FLOOR_PIT_L3);
	LoadPicAndFlip(m_pPitRight[3], IDB_FLOOR_PIT_L3);

}

CPoint CPitPic::GetCeilingPos(int x, int ebene) {
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

CPoint CPitPic::GetPos(int x, int ebene) {
	CPoint middle;
	switch (x) {
	case 2:
		if (ebene == 1) middle.x = 54;
		if (ebene == 2) middle.x = 70;
		if (ebene == 3) middle.x = 90;
		break;
	case 3:
		if (ebene == 1) middle.x = 418; // tuned for pressure plate
		if (ebene == 2) middle.x = 380;
		if (ebene == 3) middle.x = 360;
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
			middle.y = 280; break;
		case 2:
			middle.y = 235;	break;
		case 3:
			middle.y = 200; break;
		}
	}

	return middle;
}