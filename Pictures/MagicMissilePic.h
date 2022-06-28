#pragma once
#include "CBasePictures.h"
class CMagicMissilePic : public CBasePictures
{
public:
	CMagicMissilePic(CDC* pDC);
	~CMagicMissilePic();

private:
	void InitBitmap();

	CBitmap* m_pFireball;
	CBitmap* m_pPoison;
	CBitmap* m_pPoisonBlob;
	CBitmap* m_pAntiMaterial;

};

