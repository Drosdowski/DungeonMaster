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
class CMiscellaneous;
class CHeld : public CCharacter
{
public:
	CHeld(int iIndex, CString strName);
protected:
	CHeld();           // protected constructor used by dynamic creation

// Attributes
public:
	int getIndex() { return m_iIndex; }
	bool isActive() { return m_bAktiv; }
	int getFood() { return m_iFood; }
	int getWater() { return m_iWater; }
	long* getExp() { return m_sExp; }
	VITALS getVitals() { return m_sVitals;  }
	CString getName() { return m_strName; }

// Operations
public:
	void Trinken(int amount);
	void Essen(int amount);

	int CalcDmg(int ID, CGrpChar* pOpponents);
	double LifePart() { return (double)m_HP.Aktuell / (double)m_HP.Max; }
	double StaminaPart() { return (double)m_ST.Aktuell / (double)m_ST.Max; }
	double ManaPart() { return (double)m_MA.Aktuell / (double)m_MA.Max; }
	COLORREF Farbe() { return m_Farbe[m_iIndex]; }

	CRucksack* GetRucksack() { return m_pRucksack; }

	CMiscellaneous* GetItemInHand() { return m_pItemInHand; }
	void setActive() { m_bAktiv = true; }
	void setInactive() { m_bAktiv = false; }
	void TakeItemInHand(CMiscellaneous* item);
	void EmptyHand();

	CMiscellaneous* GetItemCarrying(int index) { return m_itemCarrying[index]; }
	CMiscellaneous* SwitchItemAt(int index, CMiscellaneous* item);

// Implementation
public:
	virtual bool Altern();
	virtual ~CHeld();


private:
	CRucksack* m_pRucksack;
	COLORREF m_Farbe[5];
	long m_sExp[5];
	VITALS m_sVitals;
	int maxFood = 200;
	int maxWater = 200;
	int m_iFood;
	int m_iWater;
	int m_iIndex;
	bool m_bAktiv;
	CString m_strName;
	CMiscellaneous* m_itemCarrying[30];

	CMiscellaneous* m_pItemInHand = NULL;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HELD_H__E9C070C2_89FD_11D2_9F0B_008048898454__INCLUDED_)
