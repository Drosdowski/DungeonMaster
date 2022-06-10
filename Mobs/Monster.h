#ifndef AFX_MONSTER_H__15FAEB01_991E_11D2_A630_008048898454__INCLUDED_
#define AFX_MONSTER_H__15FAEB01_991E_11D2_A630_008048898454__INCLUDED_

// Monster.h : Header-Datei
//
#include "Character.h"
#include "..\Attributes\CCreatureAttributes.h" 
/////////////////////////////////////////////////////////////////////////////
// Ansicht CMonster 

class CMonster : public CCharacter
{
public:

	CMonster(CCreatureAttributes attributes, int subId);

// Attribute
public:

// Operationen


// Implementierung
public:
	virtual bool Altern();
	virtual int GetIDB(int index);
	bool IstBereit() { return m_iReady == 0; };
	void AttackDone() { m_iReady = m_attributes.monsterInfo.attack_dur; } 
	void MoveDone() { m_iReady = m_attributes.monsterInfo.move_dur; } 
	void ReceiveDamage(int dmg) { m_HP.Aktuell -= dmg; }
	int getDealingDmg() { return m_dealingDmg; }
	MonsterTyp getType() { return m_iTyp; }
	void setType(MonsterTyp typ) { m_iTyp = typ; }
	bool TurnTo(COMPASS_DIRECTION iDirection);
	int CalcDmg(int ID);

	int transCol;

protected:
	virtual ~CMonster();

	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	MonsterTyp m_iTyp;
	CDC pCdc;
	int m_iReady;
	CCreatureAttributes m_attributes;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_MONSTER_H__15FAEB01_991E_11D2_A630_008048898454__INCLUDED_
