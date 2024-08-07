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

class CItem;
class CWeapon;
class CChampion;
class CHeld : public CCharacter
{
public:
	CHeld(int iIndex, CChampion* champ, int hp_akt, int st_akt, int ma_akt);
protected:
	CHeld();           // protected constructor used by dynamic creation

// Attributes
public:
	int getIndex() { return m_iIndex; }
	int getHeroId() { return m_heroId; }
	bool isActive() { return m_bAktiv; }
	int getFood() { return m_iFood; }
	int getWater() { return m_iWater; }
	VITALS getVitals() { return m_sVitals;  }
	CString getName() { return m_strName; }
	CString getSubname() { return m_strSubname; }
	bool isMale() { return m_male; }

// Operations
public:
	void Trinken(int amount);
	void Essen(int amount);
	void WerteTemporaerAendern(double hp, double st, double ma);
	void WerteSetzen(double hp, double st, double ma);
	void ReduceStamina(int st) { m_ST.Aktuell = max(0, m_ST.Aktuell - 10 * (st + (rand() % 1))); }
	//virtual void WertePermanentAendern(int hp, int st, int ma);
	void ChangeCompass();

	int CalcDmg(CWeapon* weapon, CAttackConst ac, CMonsterConst mc, int levelDif);
	double LifePart() { return (double)floor(m_HP.Aktuell) / HPMax(); }
	double StaminaPart() { return (double)floor(m_ST.Aktuell) / STMax(); }
	double ManaPart() { return (double)(floor(m_MA.Aktuell)) / MAMax(); }
	COLORREF Farbe() { return m_Farbe; }
	double MaxLoad();
	double CurLoad();
	int Armour();
	int fightLevel() ;
	int ninjaLevel() ;
	int priestLevel();
	int wizardLevel();

	void SetBackpackLooking(bool value) { m_bBackpackLooking = value; }
	bool GetBackpackLooking() { return m_bBackpackLooking; }
	bool GetMouthEating() { return m_iEating % 2 == 1; }

	void setActive() { m_bAktiv = true; }
	void setInactive() { m_bAktiv = false; }
	void setDelay(int delay) { m_delay += delay; }
	bool isReady() { return m_delay <= 0; }

	CItem* GetItemCarrying(int index) { return m_itemCarrying[index]; }
	void RemoveItemCarrying(int index);
	CItem* SwitchItemAt(int index, CItem* item);
	CString GetSkillsForSaveGame();
	CString GetSpellForSaveGame();
	void SetSkillsFromSaveGame(CString skills);
	void SetSpellFromSaveGame(CString spell);

	// Get Attributes with item boni
	double HPMax() { return (double) m_HP.Max; }
	double STMax() { return (double) m_ST.Max;  }
	double MAMax();

// Implementation
public:
	virtual bool Altern();
	virtual ~CHeld();
	virtual WERTE St() { return m_ST; };
	virtual WERTE Ma() { return m_MA; };
	bool UseMana(int mana);

	int getRuneTableId() { return m_iRuneTable; }
	int GetPower();
	void resetRuneTable();
	void undoRune();
	void storeRune(int index);
	int* getSpell() { return m_spell; }

private:
	bool m_bBackpackLooking;
	int m_iEating;
	COLORREF m_Farbe;
	FIGHT_SKILLS m_fightLevel;
	NINJA_SKILLS m_ninjaLevel;
	PRIEST_SKILLS m_priestLevel;
	WIZARD_SKILLS m_wizardLevel;
	VITALS m_sVitals;
	int maxFood = 200;
	int maxWater = 200;
	int m_iFood;
	int m_iWater;
	int m_iIndex;
	int m_heroId;
	int m_iPoison;
	int m_iPoisonDelay;
	int m_delay; // for action
	bool m_bAktiv;
	WERTE m_MA;	// Mana
	WERTE m_ST;	// Stamina

	CString m_strName;
	CString m_strSubname;
	bool m_male;
	CItem* m_itemCarrying[31]; // Letztes Item sind die Knochen, sieht man nat�rlich nicht im Backpack.
	bool hitSucessful(CAttackConst ac, CMonsterConst mc, int levelDif);
	void DelItem(CItem* pItem);
	int ACC_Coeff(int levelDif, int armor);
	void ReduceWhenOverload(double d6_weapon_weight, double d5_load_coefficient, double &dmg);

	int* m_spell;
	int m_iRuneTable;
	void nextRuneTable();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HELD_H__E9C070C2_89FD_11D2_9F0B_008048898454__INCLUDED_)
