#if !defined(AFX_RUCKSACK_H__D25A0501_91C7_11D2_9F0B_008048898454__INCLUDED_)
#define AFX_RUCKSACK_H__D25A0501_91C7_11D2_9F0B_008048898454__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Rucksack.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CRucksack view

class CRucksack 
{
public:
	CRucksack();
	virtual ~CRucksack();

// Operations

// Implementation
public:
	void SetzeModusExtend(int iModusExtend); // Auf Auge geklickt - Anzeige wechselt!
	int HoleModusExtend() { return m_iModusExtend; };
	
protected:
	int m_iModusExtend;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RUCKSACK_H__D25A0501_91C7_11D2_9F0B_008048898454__INCLUDED_)
