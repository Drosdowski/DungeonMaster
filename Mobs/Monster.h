#ifndef AFX_MONSTER_H__15FAEB01_991E_11D2_A630_008048898454__INCLUDED_
#define AFX_MONSTER_H__15FAEB01_991E_11D2_A630_008048898454__INCLUDED_

// Monster.h : Header-Datei
//
#include "Character.h"
#include "..\Attributes\CreatureAttributes.h" 
/////////////////////////////////////////////////////////////////////////////
// Ansicht CMonster 

class CMonster : public CCharacter
{
public:

	CMonster(CCreatureAttributes attributes, int subId);

// Attribute
public:
	int GetSize() { return m_attributes.monsterInfo.size; }
	bool IsReady() { return m_iReady == 0; };
	int transCol;
	int GetReady() { return m_iReady; }
	bool IsLeftForPlayer(VEKTOR monPos, VEKTOR heroPos);
	void RestoreFromSaveGame(SUBPOS_ABSOLUTE subPos, int hp, int ready);

// Operationen


// Implementierung
public:
	virtual bool Altern();
	virtual int GetIDB(int index);
	void AttackDone() { m_iReady = m_attributes.monsterInfo.attack_dur; } 
	void MoveDone() { m_iReady = m_attributes.monsterInfo.move_dur; } 
	int getDealingDmg() { return m_dealingDmg; }
	MonsterTyp getType() { return m_attributes.type; }
	CMonsterConst getInfo() { return m_attributes.monsterInfo;  }
	bool TurnTo(COMPASS_DIRECTION iDirection);
	int CalcDmg(int ID);


protected:
	virtual ~CMonster();

	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	CDC pCdc;
	int m_iReady;
	CCreatureAttributes m_attributes;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio f�gt zus�tzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_MONSTER_H__15FAEB01_991E_11D2_A630_008048898454__INCLUDED_
