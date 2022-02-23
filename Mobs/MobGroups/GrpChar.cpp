// GrpChar.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "DMDoc.h"
#include "..\Character.h"
#include "GrpChar.h"
#include "CHelpfulValues.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGrpChar


CGrpChar::CGrpChar() 
{
	m_grpDirection = 0;
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
			bLaufbereit &= (m_pMember[i]->St() > 0);
		}
	
	return bLaufbereit;
}

int CGrpChar::InReihe(int byte)
{	
	int iAnz = 0; 
	for (int i=1; i<5;i++)
	{
		if ((m_pMember[i]!=NULL) && (m_pMember[i]->HoleSubPosition() & byte) > 0)
			if (m_pMember[i]->Hp()>0)
				iAnz++;
	}
	return iAnz;
}

void CGrpChar::Kollision() {
	for (int i = 1; i <= 4; i++)
		if ((m_pMember[i]) && (m_pMember[i]->Hp() > 0))
			if (m_pMember[i]->Kollision(m_grpDirection, (CGrpChar*)this))
				m_pMember[i]->WerteTemporaerAendern(-2, 0, 0);
}

void CGrpChar::DoDamage(int dmg, SUBPOS fromPos, bool areaDmg) {
	CCharacter* victim = NULL;
	if (areaDmg) {
		for (int dmgTgt = 1; dmgTgt <= 4; dmgTgt++) {
			victim = m_pMember[dmgTgt];
			if (victim && (victim->Hp() > 0)) {
				victim->m_iReceivedDmg += dmg; // Schaden aufsummieren, Abrechnung folgt im Altern.
			}
		}
	}
	else {
		victim = NearestTarget(fromPos);
		if (victim && (victim->Hp() > 0)) {
			victim->m_iReceivedDmg += dmg; 
		}
	}

}

CCharacter* CGrpChar::NearestTarget(SUBPOS from) {
	// todo unfug code
	if (from == NORTHWEST || from == SOUTHWEST) {
		return m_pMember[3];
	} 
	return m_pMember[1];
}

void CGrpChar::DamageFrom(CCharacter* pEnemy, bool areaDmg) {
	if (pEnemy && pEnemy->isAttacking()) {
		int dmg = pEnemy->m_dealingDmg;
		DoDamage(dmg, pEnemy->HoleSubPosition(), areaDmg);
		return;
	}
}

void CGrpChar::Laufen(VEKTOR WunschPos) {
	for (int i = 1; i <= 4; i++)
		if ((m_pMember[i]) && (m_pMember[i]->Hp() > 0))
		{
			//m_pMember[i]->posi
			m_pMember[i]->WerteTemporaerAendern(0, -1, 0);
			m_pMember[i]->ActionDone();
		}
	m_posPosition = WunschPos;	
}

VEKTOR CGrpChar::HoleZielFeld(int iRichtung)
{
	CPictures* x = NULL;

	int sx = m_values->m_stx[m_grpDirection];
	int sy = m_values->m_sty[m_grpDirection];

	VEKTOR WunschPos;
	WunschPos.z = m_posPosition.z;

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


void CGrpChar::Drehen(int iRichtung)
{
	switch (iRichtung)
	{
	case LINKS:
		m_grpDirection = (m_grpDirection + 3) %4;		
		break;
	case RECHTS:
		m_grpDirection = (m_grpDirection + 1) %4;
		break;
	}

	for (int i = 1; i < 5; i++)
	{
		if (m_pMember[i] != NULL) {
			m_pMember[i]->m_chrDirection = m_grpDirection;
			m_pMember[i]->ActionDone();
		}
	}

}


