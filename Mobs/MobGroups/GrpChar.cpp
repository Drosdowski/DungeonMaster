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

IMPLEMENT_DYNCREATE(CGrpChar, CView)


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


BEGIN_MESSAGE_MAP(CGrpChar, CView)
	//{{AFX_MSG_MAP(CGrpChar)
		// HINWEIS - Der Klassen-Assistent fügt hier Zuordnungsmakros ein und entfernt diese.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Zeichnung CGrpChar 

void CGrpChar::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// ZU ERLEDIGEN: Code zum Zeichnen hier einfügen
}

/////////////////////////////////////////////////////////////////////////////
// Diagnose CGrpChar

#ifdef _DEBUG
void CGrpChar::AssertValid() const
{
	CView::AssertValid();
}

void CGrpChar::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

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

void CGrpChar::DoDamage(int dmg, bool areaDmg) {

		for (int dmgTgt = 1; dmgTgt <= 4; dmgTgt++) {

			CCharacter* victim = m_pMember[dmgTgt];
			if (victim && (victim->Hp() > 0)) {
				victim->m_iReceivedDmg += dmg; // Schaden aufsummieren, Abrechnung folgt im Altern.
				if (!areaDmg) dmgTgt = 4;
			}
		}

}

void CGrpChar::DamageFrom(CGrpChar* pGrpMon, bool areaDmg) {
	for (int dmgSrc = 1; dmgSrc <= 4; dmgSrc++)
	{
		if ((pGrpMon->m_pMember[dmgSrc]) && (pGrpMon->m_pMember[dmgSrc]->isAttacking())) {
			int dmg = pGrpMon->m_pMember[dmgSrc]->m_dealingDmg;
			DoDamage(dmg, areaDmg);
			return;
		}
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


