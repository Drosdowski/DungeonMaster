#if !defined(AFX_RAUMVIEW_H__E9C070C1_89FD_11D2_9F0B_008048898454__INCLUDED_)
#define AFX_RAUMVIEW_H__E9C070C1_89FD_11D2_9F0B_008048898454__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RaumView.h : header file
//
#include "Feld.h"

/////////////////////////////////////////////////////////////////////////////
// CRaumView view


class CMonster;
class CDMDoc;
class CPictures;
class CDoorPic;
class CWallPic;
class CLeverPic;
class CFountainPic;
class CMonsterPic;
class CHelpfulValues;
class CDecorationType;
class CDungeonMap;
class CRaumView : public CView
{
public:
	CRaumView();
protected:
	//CRaumView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CRaumView)

// Attributes
	CBrush m_BlackBrush;
//	LPDIRECTDRAWSURFACE     lpDDSPrimary;
//	LPDIRECTDRAWSURFACE     lpDDSOffOne;
public:
	CDMDoc* m_pDoc;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRaumView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
public:
	void OnTrigger();
	void MoveAnythingNearby();

	void InitDungeon(CDMDoc* pDoc, CDC* pDC, CPictures* pPictures); // TODO: pDOC & pDC private merken
	bool Betrete(VEKTOR pos);
	CGrpMonster* GetMonsterGroup(VEKTOR pos);
	void TriggerMoveAnimation();
	void Zeichnen(CDC* pDC);

	virtual ~CRaumView();
protected:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	bool m_bMirror;
	CPictures* m_pPictures;
	CDoorPic* m_pDoorPic;	
	CWallPic* m_pWallPic;
	CLeverPic* m_pLeverPic;
	CFountainPic* m_pFountainPic;
	CMonsterPic* m_pMonsterPic;

	VEKTOR MonsterMoveOrAttack(CGrpMonster* pGrpMon);
	void DrawWall(CDC* pDC, CDC* cdc, int xxx, int ebene, int richt, CField* pField);
	void DrawDoor(CDC* pDC, CDC* cdc, int xxx, int ebene, int richt, CField* pField);
	void DrawFrame(CDC* pDC, CDC* cdc, int xxx, int ebene, bool left);
	void DrawMonster(CDC* pDC, CDC* cdc, int xxx, int ebene, int richt, CField* pField);
	void DrawInArea(int x, int y, int w, int h, double faktor, CDC* pDC, CDC* cdc, COLORREF col);
	// VEKTOR NextFieldWithoutTurn(CGrpMonster* pGrpMon, VEKTOR heroPos);

	CDungeonMap* m_pMap;
	//{{AFX_MSG(CRaumView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int wallXFactor[5];
	CHelpfulValues* m_values;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RAUMVIEW_H__E9C070C1_89FD_11D2_9F0B_008048898454__INCLUDED_)
