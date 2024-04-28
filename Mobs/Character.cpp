// Character.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include <typeinfo>
#include "Character.h"
#include "..\CalculationHelper\CHelpfulValues.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCharacter

CCharacter::CCharacter(bool isHero)
{
	m_chrDirection = COMPASS_DIRECTION::NORTH;
	m_iReceivedDmg = 0;
	m_iReceivedPoison = 0;
	m_dealingDmg = 0;
	m_dealingDmgToDraw = 0;
	m_dealingPoison = 0;
	m_attacking = false;
	m_isHero = isHero;
	m_subPosition = SUBPOS_ABSOLUTE::MIDDLE;
	m_HP.Aktuell = 1;
	m_HP.Max = 1;
}

CCharacter::~CCharacter()
{
}


/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CCharacter 


void CCharacter::AttackModeWithDmg(int damage, int poison) {
	m_attacking = true; 
	m_dealingDmg = damage;
	m_dealingDmgToDraw = damage;
	m_dealingPoison = poison;
}

void CCharacter::EndAttack() {
	m_attacking = false;
	m_dealingDmg = 0;
}

void CCharacter::AddDmg(int value) {
	m_iReceivedDmg += value;
}

void CCharacter::AddPoison(int value) {
	m_iReceivedPoison = min(240, m_iReceivedPoison + value);
}

bool CCharacter::InFrontOfOpponent(VEKTOR myPos, VEKTOR hisPos, bool emptyNorthRow, bool emptyEastRow, bool emptySouthRow, bool emptyWestRow) {
	if (myPos.z != hisPos.z) return false;
		
	switch (m_subPosition) {
	case SOUTHEAST: // nw nach n oder w könnte "front" sein.
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
		break;
	case MIDDLE:
		return true;
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

bool CCharacter::ReceiveDamage(int dmg) {
	if (m_HP.Aktuell > 0) {
		m_HP.Aktuell -= dmg;
		if (!isAlive()) {
			return false;
		}
		return true;
	}
	return false;
}