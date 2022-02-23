// Character.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include <typeinfo>
#include "DMDoc.h"
#include "Character.h"
#include "..\CHelpfulValues.h"
#include "MobGroups/GrpChar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCharacter

CCharacter::CCharacter()
{
	m_chrDirection = 0;
	m_iReady = 0;
}

CCharacter::~CCharacter()
{
}


/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CCharacter 

void CCharacter::WerteTemporaerAendern(int hp, int st, int ma)
{	
	m_HP.Aktuell = min(max(hp+m_HP.Aktuell,0),m_HP.Max);
	m_ST.Aktuell = min(max(st+m_ST.Aktuell,0),m_ST.Max);
	m_MA.Aktuell = min(max(ma+m_MA.Aktuell,0),m_MA.Max);
}

void CCharacter::WertePermanentAendern(int hp, int st, int ma)
{
	m_HP.Max += hp;
	m_ST.Max += st;
	m_MA.Max += ma;
}

int CCharacter::CalcDmg(int ID, CGrpChar* pOpponents) {
	return 1;
}

bool CCharacter::Kollision(int richt, CGrpChar* pGrpChar)
{
	switch(richt)
	{
	case VORWAERTS:
		return (((m_subPosition & 0x0100) > 0) || (pGrpChar->InReihe(0x0100) == 0));
		break;
	case RUECKWAERTS:
		return (((m_subPosition & 0x0001) > 0) || (pGrpChar->InReihe(0x0001) == 0));
		break;
	case LINKS_STRAFE:
		return (((m_subPosition & 0x1000) > 0) || (pGrpChar->InReihe(0x1000) == 0));
		break;
	case RECHTS_STRAFE:
		return (((m_subPosition & 0x0010) > 0) || (pGrpChar->InReihe(0x0010) == 0));
		break;
	default:	// links & rechts drehen
		return false;
	}
}

void CCharacter::AttackModeWithDmg(int damage) {
	m_attacking = true; 
	m_dealingDmg = damage;
}

void CCharacter::EndAttack() {
	m_attacking = false;
	m_dealingDmg = 0;
}

bool CCharacter::Altern() {
	if (m_iReady > 0) { 
		m_iReady--; 
	}
	if (m_HP.Aktuell > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CCharacter::InFrontOfOpponent(VEKTOR myPos, VEKTOR hisPos) {
	if (myPos.z != hisPos.z) return false;

	SUBPOS_ABSOLUTE feldPos = CHelpfulValues::GetAbsPosBySubpos(m_subPosition);

	bool xEqual = (myPos.x == hisPos.x);
	bool yEqual = (myPos.x == myPos.y);
	bool meEastFromHim = ((myPos.x - hisPos.x) == 1);
	bool meSouthFromHim = ((myPos.y - hisPos.y) == 1);
	bool meWestFromHim = ((hisPos.x - myPos.x) == 1);
	bool meNorthFromHim = ((hisPos.x - myPos.x) == 1);

	switch (feldPos) {
	case NORTHWEST: // nw nach n oder w könnte "front" sein.
		if (xEqual && meSouthFromHim) return true;
		if (yEqual && meEastFromHim) return true;
		break;
	case NORTHEAST:
		if (xEqual && meSouthFromHim) return true;
		if (yEqual && meWestFromHim) return true;
		break;
	case SOUTHWEST:
		if (xEqual && meNorthFromHim) return true;
		if (yEqual && meEastFromHim) return true;
		break;
	case SOUTHEAST:
		if (xEqual && meNorthFromHim) return true;
		if (yEqual && meWestFromHim) return true;
	}

}
