#include "CBasePictures.h"
#pragma once
class CHeld;
class CRucksack;
class CPictures : CBasePictures
{
public:
	
	CPictures(CDC* pDC);
	~CPictures();

	double getFaktor(int iEntfernung);

	CBitmap* GetRucksack() { return m_pBmpRuck; }
	CBitmap* GetHintergrund() { return m_pBmpHintergrund; }
	CBitmap* GetActionsArea() { return m_pActionsArea; }
	CBitmap* GetKram() { return m_pBmpKram; }
	CBitmap* GetRunes(int i) { return m_pRunes[i]; }
	CBitmap* GetWizardTabs(int i) { return m_pWizardTabs[i]; }
	CBitmap* GetOneHand() { return m_pOneHand; }
	CBitmap* GetActionDamage(int dmg);

	void KnochenZeichnen(CDC* pDC, int index);
	void NameZeichnen(CDC* pDC, bool aktiv, int index, CString strName);
	void RucksackZeichnen(CDC* pDC, CHeld* pHeld);
	void HaendeZeichnen(CDC* pDC, int index);
	void SymbolZeichnen(CDC* pDC, int heldIndex, SUBPOS relPos);
	void WaffeZeichnen(CDC* pDC);
	void WerteZeichnen(CDC* pDC, CHeld* pHeld);
	void BildZeichnen(CDC* pDC, bool aktiv, int index);
	void SchadenZeichnen(CDC* pDC, int index);
	void PfeilZeichnen(CDC* pDC, int index);


private:
	void InitBitmaps();
	int m_iWunschRichtung;

	void Zeichnen(CDC* pDC, int iModusExtended);
	void ZeichneSkills(CDC* pDC, CHeld* pHeld, CRucksack* pRucksack);
	void ZeichneHpStMa(CDC* pDC, WERTE hp, WERTE st, WERTE ma);
	void ZeichneHungerDurst(CDC* pDC, int i, int j);
	
	CBitmap* m_pBmpRuck;
	CBitmap* m_pBmpHintergrund;
	CBitmap* m_pBmpInversePfeile;
	CBitmap* m_pBmpKram;
	CBitmap* m_pRunes[4];
	CBitmap* m_pWizardTabs[5];
	CBitmap* m_pActionsArea;
	CBitmap* m_pActionsDamage;
	CBitmap* m_pOneHand;
	
};

