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
class CHeld : public CCharacter
{
public:
	CHeld(int iIndex, CString strName);
protected:
	CHeld();           // protected constructor used by dynamic creation

// Attributes
public:
	int getFood() { return m_iFood; }
	int getWater() { return m_iWater; }
	long* getExp() { return m_sExp; }
	VITALS getVitals() { return m_sVitals;  }
// Operations
public:
	void Trinken(int amount);
	void Essen(int amount);

	int CalcDmg(int ID, CGrpChar* pOpponents);
	int LifePart() { return m_HP.Aktuell / m_HP.Max; }
	int StaminaPart() { return m_ST.Aktuell / m_ST.Max; }
	int ManaPart() { return m_MA.Aktuell / m_MA.Max; }
	COLORREF Farbe() { return m_Farbe[m_iIndex]; }

	CRucksack* GetRucksack() { return m_pRucksack; }

// Implementation
public:
	virtual bool Altern();
	virtual ~CHeld();

	bool m_bAktiv;
	int m_iIndex; // todo getter...
	CString m_strName;

protected:

	long m_sExp[5];
	VITALS m_sVitals;
	int m_iFood;
	int m_iWater;
private:
	CRucksack* m_pRucksack;
	COLORREF m_Farbe[5];
	int maxFood = 200;
	int maxWater = 200;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HELD_H__E9C070C2_89FD_11D2_9F0B_008048898454__INCLUDED_)
