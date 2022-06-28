#pragma once
#include "CBasePictures.h"
class CMagicMissilePic : public CBasePictures
{
public:
	CMagicMissilePic(CDC* pDC);
	~CMagicMissilePic();

	CBitmap* GetFireball() { return m_pFireball; }
	CBitmap* GetPoison() { return m_pPoison; }
	CBitmap* GetPoisonBlob() { return m_pPoisonBlob; }
	CBitmap* GetAntiMaterial() { return m_pAntiMaterial; }

private:
	void InitBitmap();

	CBitmap* m_pFireball;
	CBitmap* m_pPoison;
	CBitmap* m_pPoisonBlob;
	CBitmap* m_pAntiMaterial;

};

