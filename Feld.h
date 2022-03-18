#if !defined(AFX_FELD_H__9F453601_8A22_11D2_9F0B_008048898454__INCLUDED_)
#define AFX_FELD_H__9F453601_8A22_11D2_9F0B_008048898454__INCLUDED_

#include "StdAfx.h"	// Hinzugefügt von ClassView
#include "Mobs\Monster.h"
#include <stack>

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
class CMiscellaneous;
class CActuator;
class CFieldDecoration;
class CDoor;
class CPit;
class CStairs;
class CTeleporter;
class CField
{
protected:
	CField();           // protected constructor used by dynamic creation
public:

	CField(VEKTOR koord, CDoor* pDoor);
	CField(VEKTOR koord, CStairs* pStair);
	CField(VEKTOR koord, CPit* pPit);
	CField(VEKTOR koord, CTeleporter* teleItem);
	CField(VEKTOR koord, FeldTyp fieldType);           // protected constructor used by dynamic creation


// Operations
public:
	void InitMonsterGruppe(CMonster::MonsterTyp iTyp, int iAnz, int richt);
	CGrpMonster* GetMonsterGroup();
	void RemoveMonsterGroup();
	void SetMonsterGroup(CGrpMonster* pGrpMonster);
	FeldTyp HoleTyp()	{ return m_iTyp;};
	bool Blocked();
	
	CFieldDecoration* GetFloorDeco() {	return  m_floorOrnateType; }
	void PutFloorDeco(CFieldDecoration* deco);

	int GetWallDeco(int position) { return m_pWallDecoration[position]; }
	void PutWallDeco(int position, int type) { m_pWallDecoration[position] = type; };

	CDoor* HoleDoor() { return m_pDoor;  }
	CStairs* HoleStairs() { return m_pStairs;  }
	void SetTypeDoor(CDoor* pDoor); 
	void SetTypeStair(CStairs* pStair); 
	void SetTypePit(CPit* pPit); 
	void SetTypeTeleporter(CTeleporter* teleItem);
	void SetType(FeldTyp iTyp);

	void PutMisc(CMiscellaneous* misc, SUBPOS_ABSOLUTE index);
	void ThrowMisc(CMiscellaneous* misc, SUBPOS_ABSOLUTE index, VEKTOR force);
	//void PutMisc(CMiscellaneous* misc, SUBPOS subPos);
	CMiscellaneous* TakeMisc(SUBPOS_ABSOLUTE subPos);
	std::stack<CMiscellaneous*> GetMisc(SUBPOS_ABSOLUTE index) { return m_pMiscellaneous[index]; }
	std::stack<CActuator*> GetActuator(SUBPOS_ABSOLUTE index) { return m_pActuator[index]; }

	CPit* HolePit() { return m_pPit;  }
	CTeleporter* HoleTeleporter() { return m_pTeleporter; }

	void PutActuator(CActuator* actuator, SUBPOS_ABSOLUTE index);
	VEKTOR HolePos() { return m_posKoord; }
	bool CriticalWeightChange(VEKTOR heroPos, int criticalWeight);

// Overrides

// Implementation
	virtual ~CField();

	// Generated message map functions
protected:
	VEKTOR m_posKoord;

	CGrpMonster* m_pGrpMonster;
	FeldTyp m_iTyp;
	int m_pWallDecoration[4];
	CFieldDecoration* m_floorOrnateType;
	std::stack<CMiscellaneous*> m_pMiscellaneous[4];

	std::stack <CActuator*> m_pActuator[4];

	CDoor* m_pDoor = NULL;
	CStairs* m_pStairs = NULL;
	CPit* m_pPit = NULL;
	CTeleporter* m_pTeleporter = NULL;

	int GetWeight(VEKTOR heroPos);

	int m_lastWeight;

	//{{AFX_MSG(CField)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FELD_H__9F453601_8A22_11D2_9F0B_008048898454__INCLUDED_)
