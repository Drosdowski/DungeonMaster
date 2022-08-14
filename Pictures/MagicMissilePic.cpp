#include "stdafx.h"
#include "..\resource.h"
#include "MagicMissilePic.h"

CMagicMissilePic::CMagicMissilePic(CDC* pDC) : CBasePictures(pDC)
{
	InitBitmap();
}

CMagicMissilePic ::~CMagicMissilePic() {
	delete m_pAntiMaterial;
	delete m_pFireball;
	delete m_pPoison;
	delete m_pPoisonBlob;

	delete m_pExplodeFireball;
	delete m_pExplodePoison;
	delete m_pExplodeAntimat;
	delete m_pExplodeDust;
}

void CMagicMissilePic::InitBitmap() {
	LoadPic(m_pAntiMaterial, IDB_MISSILE_ANTIMAT);
	LoadPic(m_pFireball, IDB_MISSILE_FIREBALL);
	LoadPic(m_pPoison, IDB_MISSILE_POISON);
	LoadPic(m_pPoisonBlob, IDB_MISSILE_POISONBLOB);

	LoadPic(m_pExplodeAntimat, IDB_EXPLODE_ANTIMAT);
	LoadPic(m_pExplodeFireball, IDB_EXPLODE_FIREBALL);
	LoadPic(m_pExplodePoison, IDB_EXPLODE_POISON);
	LoadPic(m_pExplodeDust, IDB_EXPLODE_DUST);
}
