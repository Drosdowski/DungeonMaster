// GrpChar.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "GrpChar.h"
#include "..\Character.h"
#include "..\..\CalculationHelper\CHelpfulValues.h"
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGrpChar


CGrpChar::CGrpChar() 
{
	m_grpDirection = COMPASS_DIRECTION::NORTH;
	m_values = new CHelpfulValues();
}


CGrpChar::~CGrpChar()
{
	for (int i=1; i<5; i++)
		if (m_pMember[i] != NULL)
		{
			delete m_pMember[i];
			m_pMember[i] = NULL;
		}
	delete m_values;
}


/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CGrpChar 


int CGrpChar::InReihe(int byte)
{	
	int iAnz = 0; 
	for (int i=1; i<5;i++)
	{
		if ((m_pMember[i]!=NULL) && (m_pMember[i]->HoleSubPosition() & byte) > 0)
			if (m_pMember[i]->Hp().Aktuell >0)
				iAnz++;
	}
	return iAnz;
}

void CGrpChar::Kollision() {
	for (int i = 1; i <= 4; i++)
		if ((m_pMember[i]) && (m_pMember[i]->Hp().Aktuell > 0))
		{
			if (CharCollision(i)) 
				m_pMember[i]->AddDmg(2);
		}
}

bool CGrpChar::CharCollision(int index) {
	SUBPOS_ABSOLUTE pos = m_pMember[index]->HoleSubPosition();
	switch (m_grpDirection)
	{
	case VORWAERTS:
		return (((pos & 0x0100) > 0) || (InReihe(0x0100) == 0));
		break;
	case RUECKWAERTS:
		return (((pos & 0x0001) > 0) || (InReihe(0x0001) == 0));
		break;
	case LINKS_STRAFE:
		return (((pos & 0x1000) > 0) || (InReihe(0x1000) == 0));
		break;
	case RECHTS_STRAFE:
		return (((pos & 0x0010) > 0) || (InReihe(0x0010) == 0));
		break;
	default:	// links & rechts drehen
		return false;
	}
}


void CGrpChar::FallingDamage() {
	for (int i = 1; i <= 4; i++)
		if ((m_pMember[i]) && (m_pMember[i]->Hp().Aktuell > 0))
			m_pMember[i]->AddDmg(25);
}

void CGrpChar::DoDamage(int dmg, VEKTOR hisPos, bool areaDmg) {
	CCharacter* victim = NULL;
	if (areaDmg) {
		for (int dmgTgt = 1; dmgTgt <= 4; dmgTgt++) {
			victim = m_pMember[dmgTgt];
			if (victim && (victim->Hp().Aktuell > 0)) {
				victim->AddDmg(dmg); // Schaden aufsummieren, Abrechnung folgt im Altern.
			}
		}
	}
	else {
		victim = NearestTarget(hisPos);
		if (victim && (victim->Hp().Aktuell > 0)) {
			victim->AddDmg(dmg);
		}
	}

}

CCharacter* CGrpChar::NearestTarget(VEKTOR hisPos) {
	// Prüfen: Monster ist in vorderster (nicht zwingend 1.) Reihe, Held ebenso!
	// Ferner: Monster steht nicht zwingend in Blickrichtung vor dem Held!
	CCharacter* nearestTarget  = NULL;
	for (int i = 1; i < 5; i++) {
		CCharacter* pChar = m_pMember[i];		
		if (pChar && pChar->Hp().Aktuell > 0) {
			if (pChar->InFrontOfOpponent(GetPos(), hisPos, emptyNorthRow(), emptyEastRow(), emptySouthRow(), emptyWestRow()))
				return pChar;
		}
	}
	return nearestTarget; // Kein Nahkampf von Hinten
}

void CGrpChar::DamageFrom(CCharacter* pEnemy, VEKTOR hisPos, bool areaDmg) {
	if (pEnemy && pEnemy->isAttacking()) {
		int dmg = pEnemy->GetDealingDamage();
		DoDamage(dmg, hisPos, areaDmg);
		return;
	}
}


VEKTOR CGrpChar::HoleZielFeld(int iRichtung)
{
	int sx = m_values->m_stx[m_grpDirection];
	int sy = m_values->m_sty[m_grpDirection];

	VEKTOR WunschPos = {0,0,m_posPosition.z };

	switch (iRichtung)
	{
	case LINKS_STRAFE:
		WunschPos.x = m_posPosition.x - sx;
		WunschPos.y = m_posPosition.y - sy;
		break;
	case RUECKWAERTS:
		WunschPos.x = m_posPosition.x - sy;
		WunschPos.y = m_posPosition.y + sx;
		break;
	case RECHTS_STRAFE:
		WunschPos.x = m_posPosition.x + sx;
		WunschPos.y = m_posPosition.y + sy;
		break;
	case VORWAERTS:
		WunschPos.x = m_posPosition.x + sy;
		WunschPos.y = m_posPosition.y - sx;
		break;
	default:
		break;
	}
	return WunschPos;
}

void CGrpChar::DrehenAbsolut(COMPASS_DIRECTION iRichtung) {
	int oldDir = m_grpDirection;
	m_grpDirection = iRichtung;
	
	for (int i = 1; i < 5; i++)
	{
		if (m_pMember[i] != NULL) {
			m_pMember[i]->SetDirection(m_grpDirection);
			SUBPOS_ABSOLUTE pos = m_pMember[i]->HoleSubPosition();

			if (((iRichtung + 4 - oldDir) % 4) == 3) // nö - geht nur bei relativ
			{
				pos = CHelpfulValues::RightFrom(pos);
			}
			else if (((iRichtung + 4 - oldDir) % 4) == 1) {
				pos = CHelpfulValues::LeftFrom(pos);
			}
			else if (((iRichtung + 4 - oldDir) % 4) == 2) {
				pos = CHelpfulValues::LeftFrom(CHelpfulValues::LeftFrom(pos));
			}

			m_pMember[i]->SetzeSubPosition(pos);
			m_pMember[i]->ActionDone();
		}
	}
}

void CGrpChar::DrehenRelativ(int iRelRichtung)
{
	switch (iRelRichtung)
	{
	case LINKS:
		DrehenAbsolut((COMPASS_DIRECTION)((m_grpDirection + 3) %4));
		break;
	case RECHTS:
		DrehenAbsolut((COMPASS_DIRECTION)((m_grpDirection + 1) %4)); // todo auslagern
		break;
	}

}

void CGrpChar::SetNewCharOnNextFreePos(int nr) {

	bool lv, rv, lh, rh;
	lv = rv = lh = rh = false;
	SUBPOS pos = NONE;	// Freien Platz suchen
	for (int i = 1; i < 5; i++)
		if ((i != nr) && (m_pMember[i] != NULL))
		{
			pos = CHelpfulValues::GetRelativeSubPosActive(m_pMember[i]->HoleSubPosition(), m_grpDirection);
			if (pos == LINKSVORNE) lv = true;
			else if (pos == RECHTSVORNE) rv = true;
			else if (pos == LINKSHINTEN) lh = true;
			else if (pos == RECHTSHINTEN) rh = true;
		}
	if (!lv)
		pos = LINKSVORNE;
	else if (!rv)
		pos = RECHTSVORNE;
	else if (!lh)
		pos = LINKSHINTEN;
	else if (!rh)
		pos = RECHTSHINTEN;

	m_pMember[nr]->SetzeSubPosition(CHelpfulValues::GetRelativeSubPosPassive(pos, m_grpDirection));
}

bool CGrpChar::emptyNorthRow() {
	for (int i = 1; i < 5; i++) {
		if (m_pMember[i] && m_pMember[i]->Hp().Aktuell > 0) {
			SUBPOS_ABSOLUTE pos = m_pMember[i]->HoleSubPosition();
			if (pos == NORTHEAST || pos == NORTHWEST) return false;
		}
	}
	return true;
}
bool CGrpChar::emptySouthRow() {
	for (int i = 1; i < 5; i++) {
		if (m_pMember[i] && m_pMember[i]->Hp().Aktuell > 0) {
			SUBPOS_ABSOLUTE pos = m_pMember[i]->HoleSubPosition();
			if (pos == SOUTHEAST || pos == SOUTHWEST) return false;
		}
	}
	return true;
}
bool CGrpChar::emptyEastRow() {
	for (int i = 1; i < 5; i++) {
		if (m_pMember[i] && m_pMember[i]->Hp().Aktuell > 0) {
			SUBPOS_ABSOLUTE pos = m_pMember[i]->HoleSubPosition();
			if (pos == SOUTHEAST || pos == NORTHEAST) return false;
		}
	}
	return true;
}
bool CGrpChar::emptyWestRow() {
	for (int i = 1; i < 5; i++) {
		if (m_pMember[i] && m_pMember[i]->Hp().Aktuell > 0) {
			SUBPOS_ABSOLUTE pos = m_pMember[i]->HoleSubPosition();
			if (pos == NORTHWEST || pos == SOUTHWEST) return false;
		}
	}
	return true;
}

