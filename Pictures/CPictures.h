#include "CBasePictures.h"
#include "Items2D/CItemPic.h"

#pragma once
class CHeld;
class CGrpHeld;
class CItemInfos;
class CScroll;
class CContainer;
class CDMFont;
class CChampionPortrait;
class CPictures : CBasePictures
{
public:
	
	CPictures(CDC* pDC);
	~CPictures();

	double getFaktor(int iEntfernung);

	CBitmap* GetRucksack() { return m_pBmpRuck; }
	CBitmap* GetHintergrund() { return m_pBmpHintergrund; }
	CBitmap* GetRunes(int i) { return m_pRunes[i]; }
	CBitmap* GetWizardTabs(int i) { return m_pWizardTabs[i]; }
	CBitmap* GetOneHand() { return m_pOneHand; }
	CBitmap* GetIconBitmap(CDC* pDC, CItem* pMisc);
	CBitmap* GetInterface(int index) { return m_pInterface[index]; }
	CBitmap* GetDamageReceived(int index) { return m_pDamageReceived[index]; }
	CBitmap* GetChampions();
	CPoint GetKoords(int heroId);
	
	void DrawActionAreaChoice(CDC* pDC, CItemInfos* m_pItemInfos, int weaponIndex);
	void DrawActionAreaDamage(CDC* pDC, int dmg);
	void DrawActiveWeapon(CDC* pDC, CHeld* held, int id);
	void DrawSpecialFont(CDC* pDC, CPoint pos, CString text, int size);
	void DrawItemInfoText(CDC* pDC, CItem* item);
	void RucksackZeichnen(CDC* pDC, CGrpHeld* pGrpHelden);
	void SymbolZeichnen(CDC* pDC, int heldIndex, SUBPOS relPos);
	// void WaffeZeichnen(CDC* pDC);
	void PfeilZeichnen(CDC* pDC, int index);
	void DrawFontText(CDC* pDC, int x, int y, CString text, bool darkFont);
	void DrawHand(CDC* pDC, CHeld* pHeld, int index);

private:
	void InitBitmaps();
	int m_iWunschRichtung;

	void ZeichnenHauptbereichHintergrund(CDC* pDC, bool bLooking, bool bEating);
	void ZeichneSkills(CDC* pDC, CHeld* pHeld);
	void ZeichneHpStMa(CDC* pDC, CHeld* pHeld);
	void ZeichneHungerDurst(CDC* pDC, int i, int j);
	void ZeichneIcons(CDC* pDC, CHeld* pHeld);
	void ZeichneItemInfo(CDC* pDC, CItem* item);
	void ZeichneScroll(CDC* pDC, CScroll* scroll);
	void ZeichneContainer(CDC* pDC, CContainer* pContainer);
	void GewichtZeichnen(CDC* pDC, CHeld* pHeld);	// todo einheitliche Namen!
	void ZeichneVitalText(CDC* pDC, CString text, int index, int y);

	void DrawText(CDC* pDC, int x, int y, CString text, int h, COLORREF fc, COLORREF bc);

	CChampionPortrait* m_pChampionPortraits;

	CString GetText(CItem* item);
	CBitmap* GetOrigFontLetter(CDC* pDC, char letter);
	CBitmap* GetScrollFontLetter(CDC* pDC, char letter);

	CBitmap* m_pBmpRuck;
	CBitmap* m_pBmpHintergrund;
	CBitmap* m_pBmpInversePfeile;
	CBitmap* m_pBmpPfeile;
	CBitmap* m_pRunes[5];
	CBitmap* m_pWizardTabs[5];
	CBitmap* m_pActionInactive;
	CBitmap* m_pActionsArea;
	CBitmap* m_pActionsDamage;
	CBitmap* m_pOneHand;
	CBitmap* m_pInterface[2];
	CBitmap* m_pDamageReceived[2];
	CBitmap* m_pOpenScroll;
	CBitmap* m_pOpenChest;
	CBitmap* m_pItemCircle;

	CItemPic* m_pItemPic;
	CDMFont* m_pDMFont;
};

