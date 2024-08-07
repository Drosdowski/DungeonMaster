#if !defined(AFX_FELD_H__9F453601_8A22_11D2_9F0B_008048898454__INCLUDED_)
#define AFX_FELD_H__9F453601_8A22_11D2_9F0B_008048898454__INCLUDED_

#include "StdAfx.h"	// Hinzugefügt von ClassView
#include "Mobs\Monster.h"
#include <deque>

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#include <SpecialTile\CDoor.h>
#include <SpecialTile\CStairs.h>
#include <SpecialTile/CPit.h>
// Feld.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CField view

class CGrpMonster;
class CItem;
class CMiscellaneous;
class CCloth;
class CWeapon;
class CPotion;
class CScroll;
class CContainer;
class CActuator;
class CFloorDecoration;
class CWallDecoration;
class CText;
class CDoor;
class CPit;
class CStairs;
class CTeleporter;
class CTrickWall;
class CMagicMissile;
class CField
{
protected:
	CField();           // protected constructor used by dynamic creation
public:

	CField(VEKTOR koord, CDoor* pDoor);
	CField(VEKTOR koord, CStairs* pStair);
	CField(VEKTOR koord, CPit* pPit);
	CField(VEKTOR koord, CTeleporter* teleItem);
	CField(VEKTOR koord, CTrickWall* trickwall);
	CField(VEKTOR koord, FeldTyp fieldType);           // protected constructor used by dynamic creation


// Operations
public:
	CGrpMonster* GetMonsterGroup();
	void RemoveMonsterGroup();
	void SetMonsterGroup(CGrpMonster* pGrpMonster);
	FeldTyp HoleTyp()	{ return m_iTyp;};
	bool BlockedToWalk();
	bool BlockedToPut();
	
	CFloorDecoration* GetFloorDeco() {	return  m_floorOrnateType; }
	CWallDecoration* GetWallDeco(COMPASS_DIRECTION position) { return  m_wallOrnateType[position]; }
	void PutFloorDeco(CFloorDecoration* deco);
	void PutWallDeco(CWallDecoration* deco, int position);
	void PutWallText(CText* text, int position);

	CDoor* HoleDoor() { return m_pDoor;  }
	CStairs* HoleStairs() { return m_pStairs;  }
	CPit* HolePit() { return m_pPit; }
	CTeleporter* HoleTeleporter() { return m_pTeleporter; }
	CTrickWall* HoleTrickWall() { return m_pTrickwall; }

	void SetType(FeldTyp iTyp);

	void PutItem(CItem* item, SUBPOS_ABSOLUTE index);
	void PutMisc(CMiscellaneous* item, SUBPOS_ABSOLUTE index);
	void PutWeapon(CWeapon* item, SUBPOS_ABSOLUTE index);
	void PutCloth(CCloth* item, SUBPOS_ABSOLUTE index);
	void PutPotion(CPotion* item, SUBPOS_ABSOLUTE index);
	void PutScroll(CScroll* item, SUBPOS_ABSOLUTE index);
	void PutContainer(CContainer* item, SUBPOS_ABSOLUTE index);
	void ThrowItem(CItem* item, SUBPOS_ABSOLUTE index, VEKTOR force);
	void CastMissile(CMagicMissile* missile, SUBPOS_ABSOLUTE index);
	//void PutItem(CItem* item, SUBPOS subPos);
	CItem* TakeItem(SUBPOS_ABSOLUTE subPos);
	CMagicMissile* TakeMissile(SUBPOS_ABSOLUTE subPos, CMagicMissile* pMissile);
	std::deque<CItem*> GetItem(SUBPOS_ABSOLUTE index) { return m_pItem[index]; }
	std::deque<CActuator*> GetActuator(COMPASS_DIRECTION index) { return m_pActuator[index]; }
	std::deque<CMagicMissile*> GetMagicMissile(SUBPOS_ABSOLUTE index) { return m_pMagicMissiles[index]; }
	CText* GetFirstText(int position);

	void PutActuator(CActuator* actuator, COMPASS_DIRECTION index);
	VEKTOR HolePos() { return m_posKoord; }
	void StoreCurrentWeight(VEKTOR heroPos);
	bool CriticalWeightBreached(VEKTOR heroPos, double criticalWeight);
	bool CriticalWeightGone(VEKTOR heroPos, double criticalWeight);

	void RotateActuators(COMPASS_DIRECTION position);

private:
	void SetTypeDoor(CDoor* pDoor);
	void SetTypeStair(CStairs* pStair);
	void SetTypePit(CPit* pPit);
	void SetTypeTeleporter(CTeleporter* teleItem);
	void SetTypeTrickwall(CTrickWall* trickwall);

// Overrides

// Implementation
public:
	~CField();

	// Generated message map functions
protected:
	void InitVars();
	VEKTOR m_posKoord;

	CGrpMonster* m_pGrpMonster;
	FeldTyp m_iTyp;
	//int m_pWallDecoration[4];
	CFloorDecoration* m_floorOrnateType;
	CWallDecoration* m_wallOrnateType[4];
	std::deque<CText*> m_wallText[4];
	std::deque<CItem*> m_pItem[4];
	std::deque<CMagicMissile*> m_pMagicMissiles[4];
	std::deque <CActuator*> m_pActuator[4];

	CDoor* m_pDoor = NULL;
	CStairs* m_pStairs = NULL;
	CPit* m_pPit = NULL;
	CTeleporter* m_pTeleporter = NULL;
	CTrickWall* m_pTrickwall = NULL;

	double GetWeight(VEKTOR heroPos);

	double m_lastWeight;

	//{{AFX_MSG(CField)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FELD_H__9F453601_8A22_11D2_9F0B_008048898454__INCLUDED_)
