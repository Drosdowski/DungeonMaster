#if !defined(AFX_RUCKSACK_H__D25A0501_91C7_11D2_9F0B_008048898454__INCLUDED_)
#define AFX_RUCKSACK_H__D25A0501_91C7_11D2_9F0B_008048898454__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Rucksack.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CRucksack view

class CPictures;
class CRucksack : public CView
{
public:
	CRucksack(CPictures* pPictures);
protected:
	CRucksack();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CRucksack)

// Attributes
public:

// Operations
public:
	virtual void OnLButtonDown(CDC* pDC, UINT nFlags, CPoint point);
	virtual void OnLButtonUp(CDC* pDC, UINT nFlags, CPoint point);
	void Zeichnen(CDC* pDC);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRucksack)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetzeModusExtend(int iModusExtend);
	void ZeichneSkills(CDC* pDC, long sExp[5], VITALS sVitals);
	int HoleModusExtend() {return m_iModusExtend;};
	void ZeichneHpStMa(CDC* pDC, WERTE hp, WERTE st, WERTE ma);
	void ZeichneHungerDurst(CDC* pDC, int i, int j);
	virtual ~CRucksack();
protected:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	CString Titel(long exp);
	int m_iModusExtend;
	CString KLASSE[5];
	CPictures* m_pPictures;
	//{{AFX_MSG(CRucksack)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RUCKSACK_H__D25A0501_91C7_11D2_9F0B_008048898454__INCLUDED_)
