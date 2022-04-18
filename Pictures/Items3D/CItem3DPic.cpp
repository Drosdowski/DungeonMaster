#include "stdafx.h"
#include "..\..\resource.h"
#include "CItem3DPic.h"

CItem3DPic::CItem3DPic(CDC* pDC) : CBasePictures(pDC)
{
	InitBitmap();
}

CItem3DPic ::~CItem3DPic() {
	delete m_pApple;
	delete m_pBread;
	delete m_pGoldKey;
	delete m_pIronKey;
	for (int w = 0; w<2; w++)
		delete m_pWaterskin[w];
}
	

void CItem3DPic::InitBitmap() {
	LoadPic(m_pApple, IDB_ITEM3D_APPLE);
	LoadPic(m_pBread, IDB_ITEM3D_BREAD);
	LoadPic(m_pGoldKey, IDB_ITEM3D_GOLDKEY);
	LoadPic(m_pIronKey, IDB_ITEM3D_IRONKEY);
	LoadPic(m_pWaterskin[0], IDB_ITEM3D_WATERSKIN_E);
	LoadPic(m_pWaterskin[1], IDB_ITEM3D_WATERSKIN_F);
}

CPoint CItem3DPic::GetFloorMiddle(int x, int ebene) {
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
			middle.y = 260; break;
		case 2:
			middle.y = 225;	break;
		case 3:
			middle.y = 200; break;
		}
	}

	return middle;
}