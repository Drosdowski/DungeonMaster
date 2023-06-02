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
class CMonster;
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
	// TODO bool ExistsAndDies();
	void MoveDone();
	bool AnyoneReady();
	bool EveryoneReady();
	CMonster* GetMonsterByRelSubPos(SUBPOS posIndex, COMPASS_DIRECTION richt);
	CMonster* GetMonsterByAbsSubPos(SUBPOS_ABSOLUTE pos);
	MonsterTyp GetType();

// Implementierung
public:
	bool SetzeModus(int iModus);	
	CMonster* AttackHero(VEKTOR myPos, VEKTOR hisPos);
	void TurnToHero(VEKTOR heroPos);
	void Laufen(VEKTOR WunschPos, boolean teleport);
	void EndAttack();
	void CarryItem(CItem* item);
	std::deque<CItem*> DropInventory();
	SUBPOS_ABSOLUTE GetLastPos() { return m_lastPosition; }
	int GetIndex() { return m_index; }
	virtual ~CGrpMonster();
private:
	void InitMonster(int nr, CCreatureAttributes attributes);
	void TryToAdavanceToFirstRow(int index, VEKTOR monPos, VEKTOR heroPos);
	bool isSubPosAbsoluteFree(SUBPOS_ABSOLUTE pos);

	CMonster* GetBySubpos(SUBPOS pos);
	std::deque<CItem*> carriedItems;
	SUBPOS_ABSOLUTE m_lastPosition;
	int m_index;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_GRPMONSTER_H__17528B60_9B45_11D2_A630_008048898454__INCLUDED_
