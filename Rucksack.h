#if !defined(AFX_RUCKSACK_H__D25A0501_91C7_11D2_9F0B_008048898454__INCLUDED_)
#define AFX_RUCKSACK_H__D25A0501_91C7_11D2_9F0B_008048898454__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Rucksack.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CRucksack view

class CHeld;
class CRucksack 
{
public:
	CRucksack();
	virtual ~CRucksack();

// Operations
public:
	void handleLButtonDown(CDC* pDC, CPoint point, CHeld* pHeld);
	void handleLButtonUp();

// Implementation
public:
	void SetzeModusExtend(int iModusExtend);
	int HoleModusExtend() { return m_iModusExtend; };
	CString GetTitle(long exp) { return m_title(exp); };
	CString GetClass(int index) { return KLASSE[index]; }
	
protected:
	CString m_title(long exp);
	int m_iModusExtend;
	CString KLASSE[5];
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RUCKSACK_H__D25A0501_91C7_11D2_9F0B_008048898454__INCLUDED_)
