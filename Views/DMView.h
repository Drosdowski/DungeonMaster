// DMView.h : interface of the CDMView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DMVIEW_H__0852F62D_89E0_11D2_9F0B_008048898454__INCLUDED_)
#define AFX_DMVIEW_H__0852F62D_89E0_11D2_9F0B_008048898454__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <deque>
#include "..\Items\MagicMissile.h";


class CActuator;
class CDMDoc;
class CHeld;
class CField;
class CGrpHeld;
class CRaumView;
class CGroupView;
class CZauberView;
class CPictures;
class CDMView : public CView
{
protected: // create from serialization only
	CDMView();
	DECLARE_DYNCREATE(CDMView)

// Attributes
public:

	CDMDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDMView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	void InitDungeon(CDMDoc* pDoc);
	virtual ~CDMView();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	int m_iDir;
	CPictures* m_pPictures;
	CZauberView* m_pZauberView;
	CGroupView* m_pGroupView;
	CRaumView* m_pRaumView;

	void UpdateGrafik();
	void HeldenGrafikZeichnen(CGrpHeld* pGrpHeld, CDC* pDC, CPictures* pPictures);
	void ZauberReiterZeichnen(CDC* pDC, int iActiveWizard);
	void ActionAreaZeichnen(CDC* pDC, int weaponIndex);
	void ActionDamageZeichnen(CDC* pDC, int dmg);
	void WaffenZeichnen(CDC* pDC, CGrpHeld* pGrpHeroes);
	void DrawBMP(CDC* pDC, CBitmap* pBMP, int posX, int posY);
	void FrameZeichnen(CDC* pDC);
	bool m_bPause;
	bool m_bSleep;
	DMMode m_iModus;
	DMMode lastModus;
	//{{AFX_MSG(CDMView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void ParseClickArrows(CPoint point);
	void ParseClickMagic(CPoint point);
	void ParseClickWizardChoice(CPoint point, CGrpHeld* grpHelden);
	void ParseClickRunes(CPoint point, CGrpHeld* grpHelden);
	void ParseClickSpell(CPoint point, CGrpHeld* grpHelden);
	void ParseClickAction(CPoint point);
	void ParseClickBackpack(CPoint point, CHeld* pHeld);
	void ParseClickPortrait(CPoint point);
	bool ParseClickPortraitHands(CPoint point, bool backpackMode);
	void ParseClickFloor(CPoint point);
	void ParseClickAir(CPoint point);
	bool ParseClickActuator(CPoint point, std::deque<CActuator*> &actuators, COMPASS_DIRECTION dir, CSize size);
	void ParseClickDoorButton(CPoint point, CField* FeldVorHeld);
	void ParseClickFountain(CPoint point, CField* FeldVorHeld, COMPASS_DIRECTION dir);

	void InvokeRemoteActuator(CActuator* activeActuator);
	void ChangeMouseCursor();

	// Spells
	void CastMagicMissile(CMagicMissile::MagicMissileType missileType, int size);

};

#ifndef _DEBUG  // debug version in DMView.cpp
inline CDMDoc* CDMView::GetDocument()
   { return (CDMDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DMVIEW_H__0852F62D_89E0_11D2_9F0B_008048898454__INCLUDED_)
