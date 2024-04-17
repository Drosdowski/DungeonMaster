#pragma once
#include "CBasePictures.h"
#include "..\Items\MagicMissile.h"

class CMagicMissilePic : public CBasePictures
{
public:
	CMagicMissilePic(CDC* pDC);
	~CMagicMissilePic();

	CBitmap* GetFireball(bool isExploding, bool isInside, int size) { return isExploding ? isInside ? m_pInsideFire[sizeToIndex(size)] :  m_pExplodeFireball : m_pFireball; }
	CBitmap* GetLightning(bool isExploding, bool isInside, int size) { return isExploding ? isInside ? m_pInsideFire[sizeToIndex(size)] : m_pExplodeFireball : m_pLightning; }
	CBitmap* GetPoison(bool isExploding, bool isInside, int size) { return isExploding ? isInside ? m_pInsidePoison[sizeToIndex(size)] :  m_pExplodePoison : m_pPoison; }
	CBitmap* GetPoisonBlob(bool isExploding, bool isInside) { return isExploding ? m_pExplodePoison : m_pPoisonBlob; }
	CBitmap* GetAntiMaterial(bool isExploding, bool isInside) { return isExploding ? m_pExplodeAntimat : m_pAntiMaterial; }
	CBitmap* GetDust(bool isInside, int strength) { return m_pExplodeDust; }

	CBitmap* GetMagicMissileBitmap(CMagicMissile::MagicMissileType type, bool exploding, bool inside, int size);


private:
	void InitBitmap();

	CBitmap* m_pFireball;
	CBitmap* m_pLightning;
	CBitmap* m_pPoison;
	CBitmap* m_pPoisonBlob;
	CBitmap* m_pAntiMaterial;

	CBitmap* m_pExplodeFireball;
	CBitmap* m_pExplodePoison;
	CBitmap* m_pExplodeAntimat;
	CBitmap* m_pExplodeDust;

	CBitmap* m_pInsideDust[3];
	CBitmap* m_pInsidePoison[3];
	CBitmap* m_pInsideFire[3];

	int sizeToIndex(int size) { return min((int)(size / 2), 2); }
};

