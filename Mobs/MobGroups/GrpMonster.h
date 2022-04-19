#ifndef AFX_GRPMONSTER_H__17528B60_9B45_11D2_A630_008048898454__INCLUDED_
#define AFX_GRPMONSTER_H__17528B60_9B45_11D2_A630_008048898454__INCLUDED_

// GrpMonster.h : Header-Datei
//
#include "GrpChar.h"
#include "..\Monster.h"
#include "..\..\SpecialTile\CCreatureAttributes.h"


/////////////////////////////////////////////////////////////////////////////
// Ansicht CGrpMonster 
class CMonster;
class CGrpHeld;
class CMiscellaneous;
class CGrpMonster : public CGrpChar
{
public:
	
	CGrpMonster(VEKTOR pos, COMPASS_DIRECTION richt); // todo eliminieren.
	CGrpMonster(VEKTOR pos, CCreatureAttributes attributes);
protected:
	CGrpMonster();           // Dynamische Erstellung verwendet geschützten Konstruktor

// Attribute
public:

// Operationen
public:
	bool Altern();
	CMonster* GetMonster(int ID);
	// TODO bool ExistsAndDies();
	void ActionDone();
	bool AnyoneReady();
	bool EveryoneReady();
	CMonster* GetMonsterByRelSubPos(SUBPOS posIndex, COMPASS_DIRECTION richt);


// Implementierung
public:
	bool SetzeModus(int iModus);	
	CMonster* AttackHero(VEKTOR myPos, VEKTOR hisPos);
	void TurnToHero(VEKTOR heroPos);
	void Laufen(VEKTOR WunschPos);
	void EndAttack();
	void CarryItem(CMiscellaneous* item, SUBPOS_ABSOLUTE pos);
	virtual ~CGrpMonster();
private:
	void InitMonster(int nr, CCreatureAttributes attributes);
	void TryToAdavanceToFirstRow(int index, VEKTOR monPos, VEKTOR heroPos);
	bool isSubPosAbsoluteFree(SUBPOS_ABSOLUTE pos);

	CMonster* GetBySubpos(SUBPOS pos);
	CMiscellaneous* carriedItem;
	SUBPOS_ABSOLUTE carriedItemPos;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_GRPMONSTER_H__17528B60_9B45_11D2_A630_008048898454__INCLUDED_
