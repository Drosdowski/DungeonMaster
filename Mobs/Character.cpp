// Character.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include <typeinfo>
#include "DMDoc.h"
#include "Character.h"
#include "MobGroups/GrpChar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCharacter

IMPLEMENT_DYNCREATE(CCharacter, CView)

CCharacter::CCharacter()
{
	m_chrDirection = 0;
	m_iReady = 0;
}

CCharacter::~CCharacter()
{
}


BEGIN_MESSAGE_MAP(CCharacter, CView)
	//{{AFX_MSG_MAP(CCharacter)
		// HINWEIS - Der Klassen-Assistent fügt hier Zuordnungsmakros ein und entfernt diese.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Zeichnung CCharacter 

void CCharacter::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// ZU ERLEDIGEN: Code zum Zeichnen hier einfügen
}

/////////////////////////////////////////////////////////////////////////////
// Diagnose CCharacter

#ifdef _DEBUG
void CCharacter::AssertValid() const
{
	CView::AssertValid();
}

void CCharacter::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

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
