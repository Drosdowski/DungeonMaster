#if !defined(AFX_HELD_H__E9C070C2_89FD_11D2_9F0B_008048898454__INCLUDED_)
#define AFX_HELD_H__E9C070C2_89FD_11D2_9F0B_008048898454__INCLUDED_

#include "..\StdAfx.h"	// Added by ClassView
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Held.h : header file
//
#include "Character.h"
#include "..\Consts\AttackConst.h"
#include "..\Consts\MonsterConst.h"
/////////////////////////////////////////////////////////////////////////////
// CHeld view

class CRucksack;
class CItem;
class CWeapon;
class CGrpMonster;
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
	void WerteTemporaerAendern(double hp, double st, double ma);
	//virtual void WertePermanentAendern(int hp, int st, int ma);
	void ChangeCompass();

	int CalcDmg(CWeapon* weapon, CAttackConst ac, CMonsterConst mc, CGrpMonster* pOpponents, int levelDif);
	double LifePart() { return (double)m_HP.Aktuell / (double)m_HP.Max; }
	double StaminaPart() { return (double)m_ST.Aktuell / (double)m_ST.Max; }
	double ManaPart() { return (double)m_MA.Aktuell / (double)m_MA.Max; }
	COLORREF Farbe() { return m_Farbe[m_iIndex]; }
	double MaxLoad();
	double CurLoad();
	int Armour();


	CRucksack* GetRucksack() { return m_pRucksack; }

	void setActive() { m_bAktiv = true; }
	void setInactive() { m_bAktiv = false; }

	CItem* GetItemCarrying(int index) { return m_itemCarrying[index]; }
	void RemoveItemCarrying(int index) { m_itemCarrying[index] = NULL; }
	CItem* SwitchItemAt(int index, CItem* item);

// Implementation
public:
	virtual bool Altern(CField* field);
	virtual ~CHeld();
	virtual WERTE St() { return m_ST; };
	virtual WERTE Ma() { return m_MA; };
	bool UseMana(int mana);

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
	int m_iCurrentLuck;
	WERTE m_MA;	// Mana
	WERTE m_ST;	// Stamina

	CString m_strName;
	CItem* m_itemCarrying[30];

	double round1(double value);
	bool hitSucessful(CAttackConst ac, int levelDif);
	void DelItem(CItem* pItem);
	int ACC_Coeff(int levelDif, int armor);
	void ReduceWhenOverload(int d6_weapon_weight, int d5_load_coefficient, int &dmg);

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HELD_H__E9C070C2_89FD_11D2_9F0B_008048898454__INCLUDED_)
