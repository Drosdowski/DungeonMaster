#if !defined(AFX_HELD_H__E9C070C2_89FD_11D2_9F0B_008048898454__INCLUDED_)
#define AFX_HELD_H__E9C070C2_89FD_11D2_9F0B_008048898454__INCLUDED_

#include "..\StdAfx.h"	// Added by ClassView
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Held.h : header file
//
#include "Character.h"
/////////////////////////////////////////////////////////////////////////////
// CHeld view

class CRucksack;
class CPictures;
class CHeld : public CCharacter
{
public:
	CHeld(CPictures* pPictures, int iIndex, CString strName);
protected:
	CHeld();           // protected constructor used by dynamic creation

// Attributes
public:
// Operations
public:
	void KnochenZeichnen(CDC* pDC, CPictures* pPictures);
	void NameZeichnen(CDC* pDC);
	void RucksackZeichnen(CDC* pDC);
	void HaendeZeichnen(CDC* pDC, CPictures* pPictures);
	void SymbolZeichnen(CDC* pDC, CPictures* pPictures, int heroGrpDir);
	void WaffeZeichnen(CDC* pDC);
	void WerteZeichnen(CDC* pDC);
	void BildZeichnen(CDC* pDC);
	void SchadenZeichnen(CDC* pDC, CPictures* pPictures);

	void Trinken(int amount);
	void Essen(int amount);

	int CalcDmg(int ID, CGrpChar* pOpponents);

// Implementation
public:
	virtual bool Altern();
	virtual ~CHeld();

	bool m_bAktiv;
	CRucksack* m_pRucksack; // todo raus hier! Parameter mitgeben!

protected:

	CString m_strName;
	long m_sExp[5];
	VITALS m_sVitals;
	int m_iFood;
	int m_iWater;
private:
	COLORREF m_Farbe[5];
	int m_iIndex;
	int maxFood = 200;
	int maxWater = 200;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HELD_H__E9C070C2_89FD_11D2_9F0B_008048898454__INCLUDED_)
