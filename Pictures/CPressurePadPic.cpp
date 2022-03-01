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