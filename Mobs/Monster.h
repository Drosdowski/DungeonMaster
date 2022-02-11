#ifndef AFX_MONSTER_H__15FAEB01_991E_11D2_A630_008048898454__INCLUDED_
#define AFX_MONSTER_H__15FAEB01_991E_11D2_A630_008048898454__INCLUDED_

// Monster.h : Header-Datei
//
#include "Character.h"
/////////////////////////////////////////////////////////////////////////////
// Ansicht CMonster 

class CMonster : public CCharacter
{
public:
	enum MonsterTyp {
		MUMIE = 1,
		STEINE = 2,
		SKELETT = 3
	};

	explicit CMonster();

// Attribute
public:

// Operationen


// Implementierung
public:
	virtual bool Altern();
	virtual int GetIDB(int index);
	int getDealingDmg() { return m_dealingDmg; }
	int getType() { return m_iTyp; }
	bool TurnTo(int iDirection);
	int CalcDmg(int ID, CGrpChar* pOpponents);

	int transCol;

protected:
	virtual ~CMonster();

	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	int m_iTyp;
	CDC pCdc;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_MONSTER_H__15FAEB01_991E_11D2_A630_008048898454__INCLUDED_
