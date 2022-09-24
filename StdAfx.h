// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__0852F627_89E0_11D2_9F0B_008048898454__INCLUDED_)
#define AFX_STDAFX_H__0852F627_89E0_11D2_9F0B_008048898454__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC OLE automation classes
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#define monsterAktiv false
#define cheatAktiv true
#define footWaterAktiv false

// todo in enum packen
#define VORWAERTS 1
#define RUECKWAERTS 2
#define LINKS_STRAFE 3
#define RECHTS_STRAFE 4
#define LINKS_DREHEN 5
#define RECHTS_DREHEN 6

#define SCHWARZ RGB(0,0,0)
#define HELLBLAU RGB(0,224,224)
#define HELLGRAU RGB(160,160,160)
#define MITTELGRAU RGB(128,128,128)
#define DUNKELGRAU RGB(96,96,96)
#define GANZDUNKELGRAU RGB(64,64,64)
#define GELB RGB(224,224,96)
#define PURROT RGB(240, 0, 0)
#define PURGELB RGB(240, 240, 0)
#define HELLBRAUN RGB(192,128,64)
#define MITTELBRAUN RGB(160,96,0)
#define DUNKELBRAUN RGB(128,64,0)
#define GANZDUNKELBRAUN RGB(96,32,0)

#define HELLGRUEN RGB(0,224,0)
#define DUNKELGRUEN RGB(0,160,0)
#define BLAU RGB(0,0,224)
#define ROT RGB(224,0,0)
#define WEISS RGB(224,224,224)
#define ROSA RGB(224,0,224)
#define HELLBLAU RGB(0,224,224)

#define TRANS_ORA RGB(208, 144, 112)
#define TRANS_BLU RGB(0, 208, 208)
#define TRANS_VIO RGB(255, 0, 255)
#define TRANS_GRA RGB(80, 80, 80)

#define MOD_EXT_NORMAL 0
#define MOD_EXT_AUGE 1

/// <summary>
/// Relative Position aus Sicht des Feldes
/// </summary>
enum SUBPOS
{
	// FRONT = 1. REIHE = OBEN
	// BACK = 2. REIHE = UNTEN
	LINKSBACK = 0b1001,	// LVRH -> Kollisionsbits
	LINKSFRONT = 0b1100,
	RECHTSBACK = 0b0011,
	RECHTSFRONT = 0b0110,
	MITTE = 0b1111,
	NONE = 0b0000

};

/// <summary>
/// Absolute Position auf der Karte
/// </summary>
enum SUBPOS_ABSOLUTE
{
	NORTHWEST = 0,
	NORTHEAST = 1,
	SOUTHEAST = 2,
	SOUTHWEST = 3,
	MIDDLE = 4,
	OUTSIDE = 5
};

enum COMPASS_DIRECTION
{
	NORTH = 0,
	EAST = 1,
	SOUTH = 2,
	WEST = 3
};

enum DMMode {
	MOD_LAUFEN = 1,
	MOD_RUCKSACK = 2,
	MOD_PAUSE = 3
};


struct VEKTOR
{
	int x, y, z;
};

struct WERTE
{
	double Aktuell, Max;
};

struct VITALS
{
	WERTE str;
	WERTE dex;
	WERTE vit;
	WERTE wis;
	WERTE af;
	WERTE am;
};

enum WallDecorationType
{
	None = 0,
	SquareAlcove = 1,
	ViAltar = 2,
	ArchedAlcove = 3,
	Hook = 4,
	IronLock = 5,
	WoodRing = 6,
	SmallSwitch = 7,
	Dent1 = 8,
	IronRing = 10,
	Crack = 11,
	SlimeOutlet = 12,
	TinySwitch = 14,
	GreenSwitchOut = 15,
	BlueSwitchOut = 16,
	CoinSlot = 17,
	SquareLock = 19,
	WingedLock = 20,
	OnyxLock = 21,
	StoneLock = 22,
	CrossLock = 23,
	TopazLock = 24,
	SkeletonLock = 25,
	GoldLock = 26,
	TourquoiseLock = 27,
	EmeraldLock = 28,
	RubyLock = 29,
	RaLock = 30,
	MasterLock = 31,
	GemHole = 32,
	Slime = 33,
	Grate = 34,
	Fountain = 35,
	Manacles = 36,
	GhoulsHead = 37,
	EmptyTorchHolder = 38,
	Scratches = 39,
	PoisonHole = 40,
	FireballHoles = 41,
	DaggerHoles = 42,
	ChampionMirror = 43,
	LeverUp = 44,
	LeverDown = 45,
	FullTorchHolder = 46,
	RedSwitchOut = 47,
	EyeSwitch = 48,
	BigSwitchOut = 49,
	GreenSwitchIn = 51,
	BlueSwitchIn = 52,
	RedSwitchIn = 53,
	BigSwitchIn = 54,
	AmalgamEncasedGem = 56,
	AmalgamFreeGem = 57,
	AmalgamWithoutGem = 58,
	LordOrder = 59
};

enum FloorDecorationType
{
	FloorMoss = 0, // typ 2
	FloorPuddle = 1, // typ 8
	FloorCrack = 2 // typ 6
};

enum FeldTyp {
	WALL = 0,
	EMPTY = 1,
	PIT = 2,
	STAIRS = 3,
	DOOR = 4,
	TELEPORT = 5,
	TRICKWALL = 6
};

enum MonsterTyp {
	SCREAMER = 6,
	ROCKPILE = 7,
	MUMMY = 10,
	SKELETON = 12,
	MAGENTA_WORM = 15,
	TROLIN = 16
};


#define HANDINDEX 46


bool InRect(CPoint p, int x1, int y1, int x2, int y2);

#define MainAreaWidth 448
#define MainAreaHeight 272

#define sign(a) ( ( (a) < 0 )  ?  -1   : ( (a) > 0 ) ? 1 : 0 )


//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__0852F627_89E0_11D2_9F0B_008048898454__INCLUDED_)
