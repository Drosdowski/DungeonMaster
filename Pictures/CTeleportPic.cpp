#include "stdafx.h"
#include "..\resource.h"
#include "CTeleportPic.h"


CTeleportPic::CTeleportPic(CDC* pDC) : CBasePictures(pDC)
{
	InitPics();
	m_phase = 0;
}

CTeleportPic::~CTeleportPic() {
	for (int guardian = 0; guardian < maxPhases; guardian++) {
		delete m_pTeleportPic[guardian];
	}
}

CBitmap* CTeleportPic::GetFrontPic() {
	m_phase++;
	if (m_phase >= maxPhases) m_phase = 0;

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
	bmp->LoadBitmap(IDB_TELEPORTER);
		
	BITMAP bmpInfo;
	bmp->GetBitmap(&bmpInfo);
	compDC.SelectObject(bmp);

	const int dx = 8 * (phase + 1);
	const int dy = 10 * (phase + 1);

	const int wx = bmpInfo.bmWidth - dx;
	const int wy = bmpInfo.bmHeight - dy;

	//        dx
	//     A  | B	 B |  C
	// dy  -----  => ------		
	//     C  | D    D |  A 
	
	// A: 0/0 => wx / dy
	compDC.StretchBlt(  wx, wy,
						dx, dy,
						&compDC, 
						0, 0, 
						dx, dy, 
						SRCCOPY
					  );
	
	// B: wx/0 => 0 / 0
	compDC.StretchBlt(  0, 0,
						wx, dy,
						&compDC,
						dx, 0,
						wx, dy,
						SRCCOPY
	);

	// C: 0/dy => wx / dy
	compDC.StretchBlt(  wx, 0,
						dx, wy,
						&compDC,
						0, dy,
						dx, wy,
						SRCCOPY
					);

	// D: wx/dy => 0 / dy
	compDC.StretchBlt(  0, dy,
						wx, wy,
						&compDC,
						dx, dy,
						wx, wy,
						SRCCOPY
					);


	DeleteDC(compDC);
	return bmp;
}