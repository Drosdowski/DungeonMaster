#include "stdafx.h"
#include "..\resource.h"
#include "MagicMissilePic.h"

CMagicMissilePic::CMagicMissilePic(CDC* pDC) : CBasePictures(pDC)
{
	InitBitmap();
}

CMagicMissilePic ::~CMagicMissilePic() {
	delete m_pAntiMaterial;
	delete m_pLightning;
	delete m_pFireball;
	delete m_pPoison;
	delete m_pPoisonBlob;

	delete m_pExplodeFireball;
	delete m_pExplodePoison;
	delete m_pExplodeAntimat;
	delete m_pExplodeDust;

	for (int i = 0; i < 3; i++) {
		delete m_pInsideFire[i];
		delete m_pInsidePoison[i];
	}
}

void CMagicMissilePic::InitBitmap() {
	LoadPic(m_pAntiMaterial, IDB_MISSILE_ANTIMAT);
	LoadPic(m_pFireball, IDB_MISSILE_FIREBALL);
	LoadPic(m_pLightning, IDB_MISSILE_ANTIMAT); // TODO PIC!
	LoadPic(m_pPoison, IDB_MISSILE_POISON);
	LoadPic(m_pPoisonBlob, IDB_MISSILE_POISONBLOB);

	LoadPic(m_pExplodeAntimat, IDB_EXPLODE_ANTIMAT);
	LoadPic(m_pExplodeFireball, IDB_EXPLODE_FIREBALL);
	LoadPic(m_pExplodePoison, IDB_EXPLODE_POISON);
	LoadPic(m_pExplodeDust, IDB_EXPLODE_DUST);

	LoadPic(m_pInsideFire[0], IDB_INSIDE_FIREBALL_LIGHT);
	LoadPic(m_pInsideFire[1], IDB_INSIDE_FIREBALL_MEDIUM);
	LoadPic(m_pInsideFire[2], IDB_INSIDE_FIREBALL_STRONG);

	LoadPic(m_pInsidePoison[0], IDB_INSIDE_POISON_LIGHT);
	LoadPic(m_pInsidePoison[1], IDB_INSIDE_POISON_MEDIUM);
	LoadPic(m_pInsidePoison[2], IDB_INSIDE_POISON_STRONG);

}


CBitmap* CMagicMissilePic::GetMagicMissileBitmap(CMagicMissile::MagicMissileType type, bool exploding, bool inside, int size) {
	if (type == CMagicMissile::AntiMagic || type == CMagicMissile::OpenDoor)
		return GetAntiMaterial(exploding, inside);
	else if (type == CMagicMissile::Lightning)
		return GetLightning(exploding, inside, size);
	else if (type == CMagicMissile::Fireball)
		return GetFireball(exploding, inside, size);
	else if (type == CMagicMissile::Poison)
		return GetPoison(exploding, inside, size);
	else if (type == CMagicMissile::PoisonBlob)
		return GetPoisonBlob(exploding, inside);
	else if (type == CMagicMissile::Dust)
		return GetDust(exploding, inside);
	else
		return NULL;
}