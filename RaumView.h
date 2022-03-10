#if !defined(AFX_RAUMVIEW_H__E9C070C1_89FD_11D2_9F0B_008048898454__INCLUDED_)
#define AFX_RAUMVIEW_H__E9C070C1_89FD_11D2_9F0B_008048898454__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RaumView.h : header file
//
#include "Feld.h"
#include "CDungeonMap.h"

/////////////////////////////////////////////////////////////////////////////
// CRaumView view


class CMonster;
class CDMDoc;
class CPictures;
class CDoorPic;
class CStairsPic;
class CWallPic;
class CLeverPic;
class CPressurePadPic;
class CPitPic;
class CFloorOrnatePic;
class CFountainPic;
class CItem3DPic;
class CMonsterPic;
class CHelpfulValues;
class CDecorationType;
class CMiscellaneous;
class CGrpHeld;
class CRaumView
{
public:
	CRaumView();
protected:

// Attributes
public:
	CDMDoc* m_pDoc;

// Operations

// Implementation
public:
	void OnTrigger();
	void MoveAnythingNearby();
	void TriggerActuatorsNearby();

	void InitDungeon(CDMDoc* pDoc, CDC* pDC, CPictures* pPictures); // TODO: pDOC & pDC private merken
	VEKTOR Betrete(VEKTOR from, VEKTOR to);
	CGrpMonster* GetMonsterGroup(VEKTOR pos);
	CDungeonMap* GetMap() { return m_pMap; }
	CGrpHeld* GetHeroes() { return m_pMap->GetHeroes(); }
	void TriggerMoveAnimation();
	void Zeichnen(CDC* pDC);
	bool OnStairs();

	CItem3DPic* Get3DPics() { return m_pItem3DPic; }

	virtual ~CRaumView();

protected:
	bool m_bMirror;
	CPictures* m_pPictures;
	CDoorPic* m_pDoorPic;	
	CWallPic* m_pWallPic;
	CLeverPic* m_pLeverPic;
	CStairsPic* m_pStairsPic;
	CPressurePadPic* m_pPressurePadPic;
	CPitPic* m_pPitPic;
	CFloorOrnatePic* m_pOrnatePic;
	CFountainPic* m_pFountainPic;
	CMonsterPic* m_pMonsterPic;
	CItem3DPic* m_pItem3DPic;

	VEKTOR MonsterMoveOrAttack(CGrpMonster* pGrpMon);
	void DrawPile(CDC* pDC, CDC* cdc, int xx, int ebene, SUBPOS_ABSOLUTE SubPos, int heroDir, std::stack<CMiscellaneous*> pile);
	void DrawWall(CDC* pDC, CDC* cdc, int xxx, int ebene, int richt, CField* pField);
	void DrawDoor(CDC* pDC, CDC* cdc, int xxx, int ebene, int richt, CDoor* pDoor);
	void DrawStairsFront(CDC* pDC, CDC* cdc, int xxx, int ebene, CStairs* pStairs);
	void DrawStairsSide(CDC* pDC, CDC* cdc, int xxx, int ebene, CStairs* pStairs);
	void DrawFloorPit(CDC* pDC, CDC* cdc, int xxx, int ebene, CPit* pit);
	void DrawCeilingPit(CDC* pDC, CDC* cdc, int xxx, int ebene, CPit* pit);
	void DrawSquarePressurePad(CDC* pDC, CDC* cdc, int xxx, int ebene, CActuator* pActuator);
	void DrawOnFloor(CDC* pDC, CDC* cdc, int xxx, int ebene, CField* pField);
	void DrawFrame(CDC* pDC, CDC* cdc, int xxx, int ebene, bool left);
	void DrawMonsterGroup(CDC* pDC, CDC* cdc, int xxx, int ebene, int richt, CField* pField);
	void DrawMonster(CDC* pDC, CDC* cdc, int xx, int ebene, int richt, CMonster* pMonster);
	void DrawInArea(int x, int y, int w, int h, double faktor, CDC* pDC, CDC* cdc, COLORREF col);
	// VEKTOR NextFieldWithoutTurn(CGrpMonster* pGrpMon, VEKTOR heroPos);

	CDungeonMap* m_pMap;
private:
	int wallXFactor[5];
	CHelpfulValues* m_values;
	void MoveMonsters(VEKTOR heroPos);
	void MoveDoors(VEKTOR heroPos);
	void PrepareMoveItems(VEKTOR heroPos);
	void MoveItems(VEKTOR heroPos);

	void TriggerActuators(VEKTOR fieldPos, VEKTOR heroPos );
	void TriggerActuator(VEKTOR heroPos, CField* field, CActuator* actuator, SUBPOS_ABSOLUTE pos);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RAUMVIEW_H__E9C070C1_89FD_11D2_9F0B_008048898454__INCLUDED_)
