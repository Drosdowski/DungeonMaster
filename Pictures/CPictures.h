#include "CBasePictures.h"
#pragma once
class CPictures : CBasePictures
{
public:
	
	CPictures(CDC* pDC);
	~CPictures();

	double getFaktor(int iEntfernung);

	CBitmap* GetRucksack() { return m_pBmpRuck; }
	CBitmap* GetHintergrund() { return m_pBmpHintergrund; }
	CBitmap* GetInversePfeile() { return m_pBmpInversePfeile; }
	CBitmap* GetActionsArea() { return m_pActionsArea; }
	CBitmap* GetKram() { return m_pBmpKram; }
	CBitmap* GetMagicBG() { return m_pMagicBG; }
	CBitmap* GetOneHand() { return m_pOneHand; }
	CBitmap* GetActionDamage(int dmg);

private:
	void InitBitmaps();
	int m_iWunschRichtung;
	
	CBitmap* m_pBmpRuck;
	CBitmap* m_pBmpHintergrund;
	CBitmap* m_pBmpInversePfeile;
	CBitmap* m_pBmpKram;
	CBitmap* m_pMagicBG;
	CBitmap* m_pActionsArea;
	CBitmap* m_pActionsDamage;
	CBitmap* m_pOneHand;
	
};

