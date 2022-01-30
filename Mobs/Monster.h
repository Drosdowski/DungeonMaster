#ifndef AFX_MONSTER_H__15FAEB01_991E_11D2_A630_008048898454__INCLUDED_
#define AFX_MONSTER_H__15FAEB01_991E_11D2_A630_008048898454__INCLUDED_

// Monster.h : Header-Datei
//
#include "Character.h"
/////////////////////////////////////////////////////////////////////////////
// Ansicht CMonster 

class CPictures;
class CMonster : public CCharacter
{
public:
	enum MonsterTyp {
		MUMIE = 1,
		STEINE = 2,
		SKELETT = 3
	};

	explicit CMonster(CPictures* pPictures, CDC* pDC);

// Attribute
public:

// Operationen
public:

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CMonster)
	protected:
	virtual void OnDraw(CDC* pDC);      // Überschrieben zum Zeichnen dieser Ansicht
	//}}AFX_VIRTUAL

// Implementierung
public:
	void Zeichnen(CDC* pDC, int iEntfernung, int iRichtung, int xrel);
	virtual bool Altern();
	virtual int GetIDB(int index);
	int getDealingDmg() { return m_dealingDmg; }
	bool TurnTo(int iDirection);
	int CalcDmg(int ID, CGrpChar* pOpponents);

protected:
	virtual ~CMonster();
	void ZeichneMonster(CDC* pDC, int bmpTAG, int iEntfernung, int xrel, bool invers);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	int m_iTyp;
	CDC pCdc;
	int transCol;

	//{{AFX_MSG(CMonster)
		// HINWEIS - Der Klassen-Assistent fügt hier Member-Funktionen ein und entfernt diese.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_MONSTER_H__15FAEB01_991E_11D2_A630_008048898454__INCLUDED_
