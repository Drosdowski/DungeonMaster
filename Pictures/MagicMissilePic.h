#pragma once
#include "CBasePictures.h"
class CMagicMissilePic : public CBasePictures
{
public:
	CMagicMissilePic(CDC* pDC);
	~CMagicMissilePic();

	CBitmap* GetFireball(bool isExploding) { return isExploding ? m_pExplodeFireball : m_pFireball; }
	CBitmap* GetPoison(bool isExploding) { return isExploding ? m_pExplodePoison : m_pPoison; }
	CBitmap* GetPoisonBlob(bool isExploding) { return isExploding ? m_pExplodePoison : m_pPoisonBlob; }
	CBitmap* GetAntiMaterial(bool isExploding) { return isExploding ? m_pExplodeAntimat : m_pAntiMaterial; }

private:
	void InitBitmap();

	CBitmap* m_pFireball;
	CBitmap* m_pPoison;
	CBitmap* m_pPoisonBlob;
	CBitmap* m_pAntiMaterial;

	CBitmap* m_pExplodeFireball;
	CBitmap* m_pExplodePoison;
	CBitmap* m_pExplodeAntimat;
};

