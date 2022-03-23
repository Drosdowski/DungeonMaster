// GrpChar.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "..\Character.h"
#include "GrpChar.h"
#include "CHelpfulValues.h"
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

bool CGrpChar::Laufbereit()
{
	bool bLaufbereit = true;
	for (int i=1; i<5; i++)
		if (m_pMember[i])
		{
			bLaufbereit &= (m_pMember[i]->St().Aktuell > 0);
		}
	
	return bLaufbereit;
}

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
			if (m_pMember[i]->Kollision(m_grpDirection, (CGrpChar*)this))
				m_pMember[i]->WerteTemporaerAendern(-2, 0, 0);
}

void CGrpChar::FallingDamage() {
	for (int i = 1; i <= 4; i++)
		if ((m_pMember[i]) && (m_pMember[i]->Hp().Aktuell > 0))
			m_pMember[i]->WerteTemporaerAendern(-25, 0, 0);
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
	for (int i = 1; i < 5; i++) {
		CCharacter* pChar = m_pMember[i];
		if (pChar && pChar->Hp().Aktuell > 0) {
			if (pChar->InFrontOfOpponent(GetPos(), hisPos))
				return pChar;
		}
	}
	return NULL; // Kein Nahkampf von Hinten
}

void CGrpChar::DamageFrom(CCharacter* pEnemy, VEKTOR hisPos, bool areaDmg) {
	if (pEnemy && pEnemy->isAttacking()) {
		int dmg = pEnemy->GetDealingDamage();
		DoDamage(dmg, hisPos, areaDmg);
		return;
	}
}

void CGrpChar::Laufen(VEKTOR WunschPos) {
	for (int i = 1; i <= 4; i++)
		if ((m_pMember[i]) && (m_pMember[i]->Hp().Aktuell > 0))
		{
			//m_pMember[i]->posi
			m_pMember[i]->WerteTemporaerAendern(0, -1, 0);
			m_pMember[i]->ActionDone();
		}
	m_posPosition = WunschPos;	
	std::cout << "New Position: " << m_posPosition.x << " - " << m_posPosition.y << std::endl;

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

