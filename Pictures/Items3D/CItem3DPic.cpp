#include "stdafx.h"
#include "..\..\resource.h"
#include "CItem3DPic.h"

CItem3DPic::CItem3DPic(CDC* pDC) : CBasePictures(pDC)
{
	InitBitmap();
}

CItem3DPic ::~CItem3DPic() {
	delete m_pApple;
}
	

void CItem3DPic::InitBitmap() {
	LoadPic(m_pApple, IDB_ITEM3D_APPLE);
}
