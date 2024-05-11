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

// todo auslagern, hat keinen Bezug zur Klasse !!
bool CCharacter::InFrontOfOpponent(VEKTOR myPos, VEKTOR hisPos, bool emptyNorthRow, bool emptyEastRow, bool emptySouthRow, bool emptyWestRow) {
	if (myPos.z != hisPos.z) return false;
		
	switch (m_subPosition) {
	case SOUTHEAST: // nw nach n oder w könnte "front" sein.
		if (CHelpfulValues::southOf(myPos, hisPos)) return true;
		if (CHelpfulValues::eastOf(myPos, hisPos)) return true;
		if (CHelpfulValues::westOf(myPos, hisPos) && emptyEastRow) return true;
		if (CHelpfulValues::northOf(myPos, hisPos) && emptySouthRow) return true;
		break;
	case SOUTHWEST:
		if (CHelpfulValues::southOf(myPos, hisPos)) return true;
		if (CHelpfulValues::westOf(myPos, hisPos)) return true;
		if (CHelpfulValues::eastOf(myPos, hisPos) && emptyWestRow) return true;
		if (CHelpfulValues::northOf(myPos, hisPos) && emptySouthRow) return true;
		break;
	case NORTHEAST:
		if (CHelpfulValues::northOf(myPos, hisPos)) return true;
		if (CHelpfulValues::eastOf(myPos, hisPos)) return true;
		if (CHelpfulValues::westOf(myPos, hisPos) && emptyEastRow) return true;
		if (CHelpfulValues::southOf(myPos, hisPos) && emptyNorthRow) return true;
		break;
	case NORTHWEST:
		if (CHelpfulValues::northOf(myPos, hisPos)) return true;
		if (CHelpfulValues::westOf(myPos, hisPos)) return true;
		if (CHelpfulValues::eastOf(myPos, hisPos) && emptyWestRow) return true;
		if (CHelpfulValues::southOf(myPos, hisPos) && emptyNorthRow) return true;
		break;
	case MIDDLE:
		return true;
	}
	return false;
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