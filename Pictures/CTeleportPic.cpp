#include "stdafx.h"
#include "..\resource.h"
#include "CTeleportPic.h"


CTeleportPic::CTeleportPic(CDC* pDC) : CBasePictures(pDC)
{
	InitPics();
	m_phase = 0;
}

CTeleportPic::~CTeleportPic() {
}

CBitmap* CTeleportPic::GetFrontPic() {
	m_phase++;
	if (m_phase > maxPhases) m_phase = 0;

	return m_pTeleportPic[m_phase];
}

void CTeleportPic::InitPics() {

	for (int phase = 0; phase < maxPhases; phase++) {
		m_pTeleportPic[phase] = InitPic(phase);
	}
}

CBitmap* CTeleportPic::InitPic(int phase) {
	CDC compDC;
	compDC.CreateCompatibleDC(m_pDC);

	CBitmap* bmp = new CBitmap();
	LoadPic(bmp, IDB_TELEPORTER_SEGMENT);
		
	int dx = 4 * phase % 32;
	BITMAP bmpInfo;
	bmp->GetBitmap(&bmpInfo);

	// dx - end an 0/0 kopieren
	compDC.StretchBlt(	0, 0, 
						bmpInfo.bmWidth - dx, bmpInfo.bmHeight,
						&compDC, 
						dx, 0, 
						bmpInfo.bmWidth - dx, bmpInfo.bmHeight, 
						SRCCOPY
					  );
	// anf - dx-1 an dx/0 kopieren
	compDC.StretchBlt(bmpInfo.bmWidth - dx, 0,
						dx, bmpInfo.bmHeight,
						&compDC,
						0, 0,
						dx, bmpInfo.bmHeight,
						SRCCOPY
					);

	DeleteDC(compDC);
	return bmp;
}