#pragma once
#include "CBasePictures.h"
class CChampionPortrait : public CBasePictures
{
public:
	CChampionPortrait(CDC* pDC);
	~CChampionPortrait();

	CBitmap* GetChampions() { return m_portraits; }
	CPoint GetKoords(int id);
private:
	void InitPics();
	CBitmap* m_portraits;
};

