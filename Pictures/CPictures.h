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
	void DrawBackback(CDC* pDC, CGrpHeld* pGrpHelden);
	void DrawSymbol(CDC* pDC, int heldIndex, SUBPOS relPos);
	void DrawArrow(CDC* pDC, int index);
	void DrawFontText(CDC* pDC, int x, int y, CString text, bool darkFont);
	void DrawHand(CDC* pDC, CHeld* pHeld, int index);

private:
	void InitBitmaps();
	int m_iWunschRichtung;

	void DrawMainAreaBackground(CDC* pDC, bool bLooking, bool bEating);
	void DrawSkills(CDC* pDC, CHeld* pHeld);
	void DrawHpStMa(CDC* pDC, CHeld* pHeld);
	void DrawVitals(CDC* pDC, int i, int j);
	void DrawVitalText(CDC* pDC, CString text, int index, int y);
	void DrawIcons(CDC* pDC, CHeld* pHeld);
	void DrawItemInfo(CDC* pDC, CItem* item);
	void DrawScroll(CDC* pDC, CScroll* scroll);
	void DrawContainer(CDC* pDC, CContainer* pContainer);
	void DrawWeight(CDC* pDC, CHeld* pHeld);	

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

