#include "stdafx.h"
#include "..\resource.h"
#include "..\SpecialTile\Decoration.h"
#include "CWallPic.h"

CWallPic::CWallPic(CDC* pDC) : CBasePictures(pDC)
{
	InitWalls();
}

CWallPic:: ~CWallPic() {
	for (int i = 0; i < 4; i++)
	{
		delete m_pWallLeft[i];
		delete m_pWallLeftF[i];
		delete m_pWallRight[i];
		delete m_pWallRightF[i];
		if (i > 0) // Front 0 ex. nicht.!
		{
			delete m_pWallFront[i];
			delete m_pWallFrontF[i];
			if (i > 1) {
				delete m_pWallFarLeft[i];
				delete m_pWallFarRight[i];
			}
		}
	}
}

void CWallPic::InitWalls() {
	/// <summary>
	/// Ebene 0 - Neben Person
	/// </summary>
	LoadPic(m_pWallLeft[0], IDB_BITMAP_E0L);
	LoadPic(m_pWallLeftF[0], IDB_BITMAP_E0LF);

	LoadPic(m_pWallRight[0], IDB_BITMAP_E0R);
	LoadPic(m_pWallRightF[0], IDB_BITMAP_E0RF);

	/// <summary>
	/// Ebene 1 - Direkt vor Person
	/// </summary>
	LoadPic(m_pWallLeft[1], IDB_BITMAP_E1L);
	LoadPic(m_pWallLeftF[1], IDB_BITMAP_E1LF);

	LoadPic(m_pWallFront[1], IDB_BITMAP_E1M);
	LoadPic(m_pWallFrontF[1], IDB_BITMAP_E1MF);

	LoadPic(m_pWallRight[1], IDB_BITMAP_E1R);
	LoadPic(m_pWallRightF[1], IDB_BITMAP_E1RF);

	/// <summary>
	/// Ebene 2 - Zwei Ebenen vor Person
	/// </summary>
	LoadPic(m_pWallLeft[2], IDB_BITMAP_E2L);
	LoadPic(m_pWallLeftF[2], IDB_BITMAP_E2LF);

	LoadPic(m_pWallFront[2], IDB_BITMAP_E2M);
	LoadPic(m_pWallFrontF[2], IDB_BITMAP_E2MF);

	LoadPic(m_pWallRight[2], IDB_BITMAP_E2R);
	LoadPic(m_pWallRightF[2], IDB_BITMAP_E2RF);

	LoadPic(m_pWallFarLeft[2], IDB_BITMAP_E2FL);
	LoadPic(m_pWallFarRight[2], IDB_BITMAP_E2FR);

	/// <summary>
	/// Ebene 3 - Drei Ebenen vor Person
	/// </summary>
	LoadPic(m_pWallLeft[3], IDB_BITMAP_E3L);
	LoadPic(m_pWallLeftF[3], IDB_BITMAP_E3LF);

	LoadPic(m_pWallFront[3], IDB_BITMAP_E3M);
	LoadPic(m_pWallFrontF[3], IDB_BITMAP_E3MF);

	LoadPic(m_pWallRight[3], IDB_BITMAP_E3R);
	LoadPic(m_pWallRightF[3], IDB_BITMAP_E3RF);

	LoadPic(m_pWallFarLeft[3], IDB_BITMAP_E3FL);
	LoadPic(m_pWallFarRight[3], IDB_BITMAP_E3FR);
}

CBitmap* CWallPic::GetWallPic(int x, int ebene, bool bMirror)
{
	switch (x) {
	case 0:
		return m_pWallFarLeft[ebene];
	case 1:
		return m_pWallFarRight[ebene];
	case 2:
		if (bMirror)
			return m_pWallLeftF[ebene];
		else
			return m_pWallLeft[ebene];
		break;
	case 3:
		if (bMirror)
			return m_pWallRightF[ebene];
		else
			return m_pWallRight[ebene];
		break;
	case 4:
		if (bMirror)
			return m_pWallFrontF[ebene];
		else
			return m_pWallFront[ebene];
		break;
	}
}

CPoint CWallPic::GetWallPos(int x, int ebene) {
	CPoint p = CPoint(0, 0);
	switch (ebene) {
	case 0:
		if (x == 2) p.x = 0;
		if (x == 3) p.x = 382;
		p.y = 64;
		break;
	case 1:
		if (x == 2) p.x = 0;
		if (x == 3) p.x = 326;
		if (x == 4) p.x = 64;
		p.y = 82;
		break;
	case 2:
		if (x == 0) p.x = 0;
		if (x == 1) p.x = 430;
		if (x == 2) p.x = 0;
		if (x == 3) p.x = 292;
		if (x == 4) p.x = 118;
		if (x < 2) {
			p.y = 113;
		}
		else {
			p.y = 102;
		}
		break;
	case 3:
		if (x == 0) p.x = 0;
		if (x == 1) p.x = 358;
		if (x == 2) p.x = 8 * 2 - 2;
		if (x == 3) p.x = 282 - 8 * 2;
		if (x == 4) p.x = 152;
		p.y = 115;
		break;
	}
	return p;

}

CPoint CWallPic::GetCenterFromFrontWall(int x, int ebene) {
	int xKoord = 0, yKoord = 0;
	switch (ebene) {
	case 0:
		break;
	case 1:
		if (x == 4) { xKoord = 80 * 2; yKoord = 40 * 2; }
		break;
	case 2:
		if (x == 2) { xKoord = 10 * 2; yKoord = 25 * 2; }
		if (x == 3) { xKoord = 67 * 2; yKoord = 25 * 2; }
		if (x == 4) { xKoord = 53 * 2; yKoord = 25 * 2; }
		break;
	case 3:
		if (x == 2) { xKoord = 37 * 2; yKoord = 17 * 2; }
		if (x == 3) { xKoord = 45 * 2; yKoord = 17 * 2; }
		if (x == 4) { xKoord = 35 * 2; yKoord = 17 * 2; }
		break;
	}
	return CPoint(xKoord, yKoord);
}

CPoint CWallPic::GetCenterFromSideWall(int x, int ebene) {
	int xKoord = 0, yKoord = 0;
	switch (ebene) {
	case 0:
		break;
	case 1:
		if (x == 2) { xKoord = 49 * 2; yKoord = 38 * 2; }  // Linke Schräge Mitte des großen Steins
		if (x == 3) { xKoord = 10 * 2; yKoord = 38 * 2; }  // Rechte Schräge Mitte des großen Steins
		break;
	case 2:
		if (x == 2) { xKoord = 67 * 2; yKoord = 25 * 2; }  // Linke Schräge Mitte des großen Steins
		if (x == 3) { xKoord = 10 * 2; yKoord = 25 * 2; }  // Rechte Schräge Mitte des großen Steins
		break;
	case 3:
		if (x == 0) { xKoord = 29 * 2; yKoord = 16 * 2; }  // Entferne Schräge links 
		if (x == 1) { xKoord = 13 * 2; yKoord = 16 * 2; }
		if (x == 2) { xKoord = 75 * 2; yKoord = 16 * 2; }
		if (x == 3) { xKoord = 7 * 2; yKoord = 16 * 2; }
		break;
	}
	return CPoint(xKoord, yKoord);
}
