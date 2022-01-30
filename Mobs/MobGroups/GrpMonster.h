#ifndef AFX_GRPMONSTER_H__17528B60_9B45_11D2_A630_008048898454__INCLUDED_
#define AFX_GRPMONSTER_H__17528B60_9B45_11D2_A630_008048898454__INCLUDED_

// GrpMonster.h : Header-Datei
//
#include "GrpChar.h"
#include "..\Monster.h"


/////////////////////////////////////////////////////////////////////////////
// Ansicht CGrpMonster 
class CMonster;
class CGrpHeld;
class CGrpMonster : public CGrpChar
{
public:
	
	CGrpMonster(VEKTOR pos);
protected:
	CGrpMonster();           // Dynamische Erstellung verwendet gesch�tzten Konstruktor
	DECLARE_DYNCREATE(CGrpMonster)

// Attribute
public:

// Operationen
public:
	bool Altern();
	void MoveOrAttack(VEKTOR heroPos, int heroDirection);
	void ActionDone();
	bool IstBereit();

// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CGrpMonster)
	protected:
	virtual void OnDraw(CDC* pDC);      // �berschrieben zum Zeichnen dieser Ansicht
	//}}AFX_VIRTUAL

// Implementierung
public:
	void InitMonster(CPictures* pPicture, CDC* pDC, int nr, CMonster::MonsterTyp iTyp);
	bool SetzeModus(int iModus);	
	void AttackHero(CGrpHeld* hero);
	void TurnToHero(VEKTOR heroPos);
	void EndAttack();
	virtual void Zeichnen(CDC* pDC, int iDistanz, int iRichtung, int xrel);
	virtual ~CGrpMonster();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	//{{AFX_MSG(CGrpMonster)
		// HINWEIS - Der Klassen-Assistent f�gt hier Member-Funktionen ein und entfernt diese.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio f�gt zus�tzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_GRPMONSTER_H__17528B60_9B45_11D2_A630_008048898454__INCLUDED_
