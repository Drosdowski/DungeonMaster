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
class CRucksack 
{
public:
	CRucksack();
	virtual ~CRucksack();

// Operations
public:
	virtual void OnLButtonDown(CDC* pDC, UINT nFlags, CPoint point);
	virtual void OnLButtonUp(CDC* pDC, UINT nFlags, CPoint point);
	void Zeichnen(CDC* pDC, CPictures* pPictures);

// Implementation
public:
	void SetzeModusExtend(int iModusExtend);
	int HoleModusExtend() { return m_iModusExtend; };
	
	void ZeichneSkills(CDC* pDC, long sExp[5], VITALS sVitals);
	void ZeichneHpStMa(CDC* pDC, WERTE hp, WERTE st, WERTE ma);
	void ZeichneHungerDurst(CDC* pDC, int i, int j);
protected:
	CString Titel(long exp);
	int m_iModusExtend;
	CString KLASSE[5];
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RUCKSACK_H__D25A0501_91C7_11D2_9F0B_008048898454__INCLUDED_)
