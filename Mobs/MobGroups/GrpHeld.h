#ifndef AFX_GRPHELD_H__7404A901_99F7_11D2_A630_008048898454__INCLUDED_
#define AFX_GRPHELD_H__7404A901_99F7_11D2_A630_008048898454__INCLUDED_

// GrpHeld.h : Header-Datei
//
#include "GrpChar.h"
/////////////////////////////////////////////////////////////////////////////
// Ansicht CGrpChar 

class CHeld;
class CMonster;
class CGrpHeld: public CGrpChar
{
public:
	CGrpHeld();
protected:
	DECLARE_DYNCREATE(CGrpHeld)

// Attribute
public:
	int m_iAktiverHeld = 1;
	int m_iAktiverZauberer;
	
// Operationen
public:

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CGrpChar)
	protected:
	virtual void OnDraw(CDC* pDC);      // Überschrieben zum Zeichnen dieser Ansicht
	//}}AFX_VIRTUAL

// Implementierung
public:
	void UpdateRucksack(CDC* pDC);
	void Aktiviere(int n);
	void InitHeld(CPictures* pPictures, int nr);
	CHeld* GetActiveHero() { return (CHeld*)m_pMember[m_iAktiverHeld]; }
	CHeld* GetHero(int iID) { return (CHeld*)m_pMember[iID]; }
	CHeld* GetAttackingHero();
	int GetActionPhase() { return m_iPhase;  }
	void PassAction();
	void ChooseHeroForAction(int ID);
	void DoActionForChosenHero(int ID, CGrpChar* pVictims);
	void DrinkFountain();
	//CHeld* GetHeroForAction() { return GetHero(m_iHeroForAction); }
	CHeld* ClosestHeroTo(CMonster* monster);
// überschriebene Methoden
	
	bool SetzeModus(CDC* pDC, int iModus);	
	void Zeichnen(CDC* pDC, int iModus);

	virtual ~CGrpHeld();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	int m_iPhase = 1;
	int m_iHeroForAction = 1;
public:
	int m_iAnzHelden;
	bool Altern();
	//{{AFX_MSG(CGrpChar)
	afx_msg void OnLButtonDown(CDC* pDC, UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(CDC* pDC, UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_GRPHELD_H__7404A901_99F7_11D2_A630_008048898454__INCLUDED_
