#if !defined(AFX_FELD_H__9F453601_8A22_11D2_9F0B_008048898454__INCLUDED_)
#define AFX_FELD_H__9F453601_8A22_11D2_9F0B_008048898454__INCLUDED_

#include "StdAfx.h"	// Hinzugefügt von ClassView
#include "Mobs\Monster.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#include <SpecialTile\CDoor.h>
#include <SpecialTile\CStairs.h>
// Feld.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CField view

class CGrpMonster;
class CMiscellaneous;
class CFieldDecoration;
class CField
{
protected:
	CField();           // protected constructor used by dynamic creation
public:

	CField(VEKTOR koord, FeldTyp fieldType, CDoor::DoorType doorType, bool doorFrameEastAndWest, CFieldDecoration* pDeco[4]);
	CField(VEKTOR koord, FeldTyp fieldType, CStairs::StairType stairType, bool eastWest, CFieldDecoration* pDeco[4]);
	CField(VEKTOR koord, FeldTyp fieldType, CFieldDecoration* pDeco[4]);           // protected constructor used by dynamic creation

// Attributes
public:
protected:
	CGrpMonster* m_pGrpMonster; 
	FeldTyp m_iTyp;
	CFieldDecoration* m_pWallDecoration[4];
	CMiscellaneous* m_pMiscellaneous[4]; // todo stacks / listen davon , nicht einzeln!
	CDoor* m_pDoor = NULL;
	CStairs* m_pStairs = NULL;

// Operations
public:
	void InitMonsterGruppe(CMonster::MonsterTyp iTyp, int iAnz, int richt);
	CGrpMonster* GetMonsterGroup();
	void RemoveMonsterGroup();
	void SetMonsterGroup(CGrpMonster* pGrpMonster);
	FeldTyp HoleTyp()	{ return m_iTyp;};
	CFieldDecoration* HoleDeko(int side) { return m_pWallDecoration[side]; }
	CDoor* HoleDoor() { return m_pDoor;  }
	CStairs* HoleStairs() { return m_pStairs;  }
	void SetType(FeldTyp iTyp, CDoor::DoorType doorType, bool doorDirectionEastWest);
	void SetType(FeldTyp fieldType, CStairs::StairType stairsType, bool eastWest);
	void SetType(FeldTyp iTyp);

	void PutMisc(CMiscellaneous* misc, int subPos);

// Overrides

// Implementation
	virtual ~CField();

	// Generated message map functions
protected:
	VEKTOR m_posKoord;


	void InitDeco(CFieldDecoration* pDeco[4]);

	//{{AFX_MSG(CField)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FELD_H__9F453601_8A22_11D2_9F0B_008048898454__INCLUDED_)
