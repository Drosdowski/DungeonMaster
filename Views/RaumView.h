#if !defined(AFX_RAUMVIEW_H__E9C070C1_89FD_11D2_9F0B_008048898454__INCLUDED_)
#define AFX_RAUMVIEW_H__E9C070C1_89FD_11D2_9F0B_008048898454__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RaumView.h : header file
//
#include "Feld.h"
#include "..\XMLParser\CDungeonMap.h"
#include "..\XMLParser\ItemInfos.h"
#include "..\XMLParser\AttackInfos.h"
#include "..\XMLParser\MonsterInfos.h"
#include <Items/MagicMissile.h>

/////////////////////////////////////////////////////////////////////////////
// CRaumView view


class CMonster;
class CDMDoc;
class CPictures;
class CDoorPic;
class CStairsPic;
class CWallPic;
class CPressurePadPic;
class CPitPic;
class CFloorOrnatePic;
class CWallDecoPic;
class CTeleportPic;
class CItem3DPic;
class CMonsterPic;
class CMagicMissilePic;
class CHelpfulValues;
class CDecorationType;
class CItem;
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
	CItemInfos* GetItemInfos() { return m_pItemInfos; }
	CAttackInfos* GetAttackInfos() { return m_pAttackInfos; }
	CMonsterInfos* GetMonsterInfos() { return m_pMonsterInfos; }
	void TriggerMoveAnimation();
	void RaumZeichnen(CDC* pDC);
	void DrawActionAreaChoice(CDC* pDC, int weaponIndex);
	void DrawActionAreaDamage(CDC* pDC, int dmg);

	bool OnStairs();
	CSize GetSizeOfFrontDeco(CField* pfield, COMPASS_DIRECTION dir);

	virtual ~CRaumView();

	CField* ChangeFieldWithTeleporter(CField* pField, SUBPOS_ABSOLUTE &subPos);
	CField* ChangeFieldWithStairs(CField* pField, CMovingObject* pItem, SUBPOS_ABSOLUTE& subPos);

protected:
	bool m_bMirror;
	CPictures* m_pPictures;
	CDoorPic* m_pDoorPic;	
	CWallPic* m_pWallPic;
	CStairsPic* m_pStairsPic;
	CPressurePadPic* m_pPressurePadPic;
	CPitPic* m_pPitPic;
	CTeleportPic* m_pTeleportPic;
	CFloorOrnatePic* m_pOrnatePic;
	CWallDecoPic* m_pWallDecoPic;
	CMonsterPic* m_pMonsterPic;
	CItem3DPic* m_pItem3DPic;
	CMagicMissilePic* m_pMagicMissilePic;

	VEKTOR MonsterMoveOrAttack(CGrpMonster* pGrpMon);
	void DrawPile(CDC* pDC, CDC* cdc, int xx, int ebene, SUBPOS_ABSOLUTE SubPos, COMPASS_DIRECTION heroDir, std::deque<CItem*> pile);
	void DrawMagicMissile(CDC* pDC, CDC* cdc, int xx, int ebene, SUBPOS_ABSOLUTE SubPos, COMPASS_DIRECTION heroDir, std::deque<CMagicMissile*> magicMissile);
	void DrawWall(CDC* pDC, CDC* cdc, int xxx, int ebene, COMPASS_DIRECTION richt, CField* pField);
	void DrawDoor(CDC* pDC, CDC* cdc, int xxx, int ebene, COMPASS_DIRECTION richt, CDoor* pDoor);
	void DrawStairsFront(CDC* pDC, CDC* cdc, int xxx, int ebene, CStairs* pStairs);
	void DrawStairsSide(CDC* pDC, CDC* cdc, int xxx, int ebene, CStairs* pStairs);
	void DrawFloorPit(CDC* pDC, CDC* cdc, int xxx, int ebene, CPit* pit);
	void DrawCeilingPit(CDC* pDC, CDC* cdc, int xxx, int ebene, CPit* pit);
	void DrawTeleporter(CDC* pDC, CDC* cdc, int xxx, int ebene, CTeleporter* tele);
	void DrawSquarePressurePad(CDC* pDC, CDC* cdc, int xxx, int ebene, CActuator* pActuator);
	void DrawOnFloor(CDC* pDC, CDC* cdc, int xxx, int ebene, CField* pField);
	void DrawFrame(CDC* pDC, CDC* cdc, int xxx, int ebene, bool left);
	void DrawMonsterGroup(CDC* pDC, CDC* cdc, int xxx, int ebene, COMPASS_DIRECTION richt, CField* pField);
	void DrawMonster(CDC* pDC, CDC* cdc, int xx, int ebene, COMPASS_DIRECTION richt, CMonster* pMonster);
	void DrawInArea(int x, int y, int w, int h, double faktor, CDC* pDC, CDC* cdc, COLORREF col);
	// VEKTOR NextFieldWithoutTurn(CGrpMonster* pGrpMon, VEKTOR heroPos);

	CDungeonMap* m_pMap;
	CItemInfos* m_pItemInfos;
	CAttackInfos* m_pAttackInfos;
	CMonsterInfos* m_pMonsterInfos;

private:
	int wallXFactor[5];
	CHelpfulValues* m_values;
	void MoveMonsters(VEKTOR heroPos);
	void MoveDoors(VEKTOR heroPos);
	void PrepareMoveObjects(VEKTOR heroPos);
	void MoveItems(VEKTOR heroPos);
	void MoveMagicMissiles(VEKTOR heroPos);
	CBitmap* GetMiscBitmap(CMiscellaneous* misc);
	CBitmap* GetWeaponBitmap(CWeapon* weapon, bool inAir);
	CBitmap* GetClothBitmap(CCloth* cloth, bool inAir);
	CBitmap* GetMagicMissileBitmap(CMagicMissile::MagicMissileType type, bool exploding);

	void TriggerPassiveActuators(VEKTOR fieldPos, VEKTOR heroPos );
	void TriggerPassiveActuator(VEKTOR heroPos, CField* field, CActuator* actuator);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RAUMVIEW_H__E9C070C1_89FD_11D2_9F0B_008048898454__INCLUDED_)
