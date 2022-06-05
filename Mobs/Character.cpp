// Character.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include <typeinfo>
#include "Character.h"
#include "..\CalculationHelper\CHelpfulValues.h"
#include "MobGroups/GrpChar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCharacter

CCharacter::CCharacter(bool isHero)
{
	m_chrDirection = 0;
	m_iReady = 0;
	m_iReceivedDmg = 0;
	m_attacking = false;
	m_isHero = isHero;
}

CCharacter::~CCharacter()
{
}


/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen f�r Nachrichten CCharacter 

int CCharacter::CalcDmg(int ID, CGrpChar* pOpponents) {
	return 1;
}

void CCharacter::AttackModeWithDmg(int damage) {
	m_attacking = true; 
	m_dealingDmg = damage;
	m_dealingDmgToDraw = damage;
}

void CCharacter::EndAttack() {
	m_attacking = false;
	m_dealingDmg = 0;
}

void CCharacter::AddDmg(int value) {
	m_HP.Aktuell = max(0, m_HP.Aktuell - value);
	m_iReceivedDmg += value;
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

bool CCharacter::InFrontOfOpponent(VEKTOR myPos, VEKTOR hisPos, bool emptyNorthRow, bool emptyEastRow, bool emptySouthRow, bool emptyWestRow) {
	if (myPos.z != hisPos.z) return false;
		
	switch (m_subPosition) {
	case SOUTHEAST: // nw nach n oder w k�nnte "front" sein.
		if (southOf(myPos, hisPos)) return true;
		if (eastOf(myPos, hisPos)) return true;
		if (westOf(myPos, hisPos) && emptyEastRow) return true;
		if (northOf(myPos, hisPos) && emptySouthRow) return true;
		break;
	case SOUTHWEST:
		if (southOf(myPos, hisPos)) return true;
		if (westOf(myPos, hisPos)) return true;
		if (eastOf(myPos, hisPos) && emptyWestRow) return true;
		if (northOf(myPos, hisPos) && emptySouthRow) return true;
		break;
	case NORTHEAST:
		if (northOf(myPos, hisPos)) return true;
		if (eastOf(myPos, hisPos)) return true;
		if (westOf(myPos, hisPos) && emptyEastRow) return true;
		if (southOf(myPos, hisPos) && emptyNorthRow) return true;
		break;
	case NORTHWEST:
		if (northOf(myPos, hisPos)) return true;
		if (westOf(myPos, hisPos)) return true;
		if (eastOf(myPos, hisPos) && emptyWestRow) return true;
		if (southOf(myPos, hisPos) && emptyNorthRow) return true;
	}
	return false;
}

bool CCharacter::westOf(VEKTOR myPos, VEKTOR hisPos) {
	return (myPos.y == myPos.y) && ((myPos.x - hisPos.x) == 1);
}

bool CCharacter::eastOf(VEKTOR myPos, VEKTOR hisPos) {
	return (myPos.y == myPos.y) && ((hisPos.x - myPos.x) == 1);
}

bool CCharacter::northOf(VEKTOR myPos, VEKTOR hisPos) {
	return (myPos.x == hisPos.x) && ((myPos.y - hisPos.y) == 1);
}

bool CCharacter::southOf(VEKTOR myPos, VEKTOR hisPos) {
	return (myPos.x == hisPos.x) && ((hisPos.y - myPos.y) == 1);
}