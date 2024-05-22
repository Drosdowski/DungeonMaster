#ifndef AFX_GRPMONSTER_H__17528B60_9B45_11D2_A630_008048898454__INCLUDED_
#define AFX_GRPMONSTER_H__17528B60_9B45_11D2_A630_008048898454__INCLUDED_

// GrpMonster.h : Header-Datei
//
#include <deque>
#include "GrpChar.h"
#include "..\Monster.h"
#include "..\..\Attributes\CreatureAttributes.h"


/////////////////////////////////////////////////////////////////////////////
// Ansicht CGrpMonster 
class CGrpHeld;
class CItem;
class CField;
class CGrpMonster : public CGrpChar
{
public:
	
	CGrpMonster(VEKTOR pos, CCreatureAttributes attributes, int index);
protected:
	CGrpMonster();           // Dynamische Erstellung verwendet geschützten Konstruktor

// Attribute
public:

// Operationen
public:
	bool Altern(CField* field);
	CMonster* GetMonster(int ID);
	void MoveDone();
	void ScaredAction(VEKTOR nextPos, boolean collision);
	bool IsScared() { return m_iScaredCounter > 0;}
	int MonsterIndexReadyToAttack();
	bool AnyoneReadyToMove();
	bool EveryoneReadyToAttack();
	bool EveryoneReadyToMove();
	bool isAlive();
	CMonster* GetMonsterByRelSubPos(SUBPOS posIndex, COMPASS_DIRECTION richt);
	CMonster* GetMonsterByAbsSubPos(SUBPOS_ABSOLUTE pos);
	MonsterTyp GetType();

// Implementierung
public:
	bool SetzeModus(int iModus);	
	CMonster* AttackHero(int monIndex, VEKTOR myPos, VEKTOR hisPos);
	void TurnToHero(VEKTOR heroPos);
	void Scare();
	void Laufen(VEKTOR WunschPos, boolean teleport);
	void CarryItem(CItem* item);
	std::deque<CItem*> DropInventory();
	SUBPOS_ABSOLUTE GetLastPos() { return m_lastPosition; }
	int GetIndex() { return m_index; }
	virtual ~CGrpMonster();
	void TryToAdvanceToFirstRow(VEKTOR heroPos);
	void TryToAdvanceToFirstRow(int index, VEKTOR monPos, VEKTOR heroPos);
private:
	bool TrySetToSubPos(CMonster* monster, SUBPOS_ABSOLUTE subPos);

	void InitMonster(int nr, CCreatureAttributes attributes);
	bool isSubPosAbsoluteFree(SUBPOS_ABSOLUTE pos);
	void RandomMove(VEKTOR nextPos, boolean collision);
	int Count();

	std::deque<CItem*> carriedItems;
	SUBPOS_ABSOLUTE m_lastPosition;
	int m_iScaredCounter;
	int m_index;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_GRPMONSTER_H__17528B60_9B45_11D2_A630_008048898454__INCLUDED_
