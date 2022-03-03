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

#define TRANS_ORA RGB(208, 144, 112)
#define TRANS_BLU RGB(0, 208, 208)
#define TRANS_VIO RGB(255, 0, 255)

#define MOD_LAUFEN 1
#define MOD_RUCKSACK 2
#define MOD_PAUSE 3

#define MOD_EXT_NORMAL 0
#define MOD_EXT_AUGE 1

/// <summary>
/// Relative Position aus Sicht des Feldes
/// </summary>
enum SUBPOS
{
	LINKSVORNE	 = 0x1100,	// LVRH -> Kollisionsbits
	LINKSHINTEN  = 0x1001,
	RECHTSVORNE  = 0x0110,
	RECHTSHINTEN = 0x0011,
	NONE		 = 0x0000

};

/// <summary>
/// Absolute Position auf der Karte
/// </summary>
enum SUBPOS_ABSOLUTE
{
	NORTHWEST = 0,
	NORTHEAST = 1,
	SOUTHWEST = 2,
	SOUTHEAST = 3,
	MIDDLE = 4
};

struct VEKTOR
{
	int x,y,z;
};

struct WERTE
{
	int Aktuell, Max;
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

enum DecorationType 
{
	None,
	Switch,
	Fountain
};

enum FeldTyp {
	WALL = 0,
	EMPTY = 1,
	PIT = 2,
	STAIRS = 3,
	DOOR = 4
};



bool InRect(CPoint p, int x1, int y1, int x2, int y2);

#define MainAreaWidth 448
#define MainAreaHeight 205

#define sign(a) ( ( (a) < 0 )  ?  -1   : ( (a) > 0 ) ? 1 : 0 )


//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__0852F627_89E0_11D2_9F0B_008048898454__INCLUDED_)
