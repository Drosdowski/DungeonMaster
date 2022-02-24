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
	
	CGrpMonster(VEKTOR pos, int richt);
protected:
	CGrpMonster();           // Dynamische Erstellung verwendet geschützten Konstruktor

// Attribute
public:

// Operationen
public:
	bool Altern();
	CMonster* GetMonster(int ID);
	// TODO bool ExistsAndDies();
	void MoveOrAttack(VEKTOR heroPos, int heroDirection);
	void ActionDone();
	bool IstBereit();
	CMonster* GetMonsterByRelSubPos(SUBPOS posIndex, int richt);


// Implementierung
public:
	void InitMonster(int nr, CMonster::MonsterTyp iTyp);
	bool SetzeModus(int iModus);	
	CMonster* AttackHero(VEKTOR myPos, VEKTOR hisPos);
	void TurnToHero(VEKTOR heroPos);
	void EndAttack();
	virtual ~CGrpMonster();
private:
	void TryToAdavanceToFirstRow(int index, VEKTOR monPos, VEKTOR heroPos);
	bool isSubPosAbsoluteFree(SUBPOS_ABSOLUTE pos);

	CMonster* GetBySubpos(SUBPOS pos);

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_GRPMONSTER_H__17528B60_9B45_11D2_A630_008048898454__INCLUDED_
