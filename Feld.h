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
#include <SpecialTile/CPressurePad.h>
// Feld.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CField view

class CGrpMonster;
class CMiscellaneous;
class CActuator;
class CFieldDecoration;
class CField
{
protected:
	CField();           // protected constructor used by dynamic creation
public:

	CField(VEKTOR koord, FeldTyp fieldType, CDoor::DoorType doorType, bool doorFrameEastAndWest, CFieldDecoration* pDeco[4]);
	CField(VEKTOR koord, FeldTyp fieldType, CStairs::StairType stairType, bool eastWest, CFieldDecoration* pDeco[4]);
	CField(VEKTOR koord, FeldTyp fieldType, CFieldDecoration* pDeco[4]);           // protected constructor used by dynamic creation


// Operations
public:
	void InitMonsterGruppe(CMonster::MonsterTyp iTyp, int iAnz, int richt);
	CGrpMonster* GetMonsterGroup();
	void RemoveMonsterGroup();
	void SetMonsterGroup(CGrpMonster* pGrpMonster);
	FeldTyp HoleTyp()	{ return m_iTyp;};
	bool Blocked();
	CFieldDecoration* HoleDeko(int side) { return m_pWallDecoration[side]; }
	CDoor* HoleDoor() { return m_pDoor;  }
	CStairs* HoleStairs() { return m_pStairs;  }
	void SetTypeDoor(FeldTyp iTyp, CDoor::DoorType doorType, bool doorDirectionEastWest);
	void SetTypeStair(FeldTyp fieldType, CStairs::StairType stairsType, bool eastWest);
	void SetType(FeldTyp iTyp);

	void PutMisc(CMiscellaneous* misc, SUBPOS_ABSOLUTE index);
	void ThrowMisc(CMiscellaneous* misc, SUBPOS_ABSOLUTE index, VEKTOR force);
	//void PutMisc(CMiscellaneous* misc, SUBPOS subPos);
	CMiscellaneous* TakeMisc(SUBPOS_ABSOLUTE subPos);
	std::stack<CMiscellaneous*> GetMisc(SUBPOS_ABSOLUTE index) { return m_pMiscellaneous[index]; }
	std::stack<CActuator*> GetActuator(SUBPOS_ABSOLUTE index) { return m_pActuator[index]; }

	void PutActuator(CActuator* actuator);

// Overrides

// Implementation
	virtual ~CField();

	// Generated message map functions
protected:
	VEKTOR m_posKoord;

	CGrpMonster* m_pGrpMonster;
	FeldTyp m_iTyp;
	CFieldDecoration* m_pWallDecoration[4];
	std::stack<CMiscellaneous*> m_pMiscellaneous[4];

	std::stack <CActuator*> m_pActuator;

	CDoor* m_pDoor = NULL;
	CStairs* m_pStairs = NULL;
	CPressurePad* m_pPressurePad = NULL;

	void InitDeco(CFieldDecoration* pDeco[4]);

	//{{AFX_MSG(CField)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FELD_H__9F453601_8A22_11D2_9F0B_008048898454__INCLUDED_)
