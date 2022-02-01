// GrpMonster.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CHelpfulValues.h"
#include "GrpMonster.h"
#include "..\Skelett.h"
#include "..\Mumie.h"
#include "..\MobGroups\GrpHeld.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGrpMonster

IMPLEMENT_DYNCREATE(CGrpMonster, CView)

CGrpMonster::CGrpMonster()
{
}

CGrpMonster::CGrpMonster(VEKTOR pos)
{
	for (int i=1; i<=4; i++)
		m_pMember[i] = NULL;
	m_posPosition=pos;
	m_grpDirection = 0;
}

CGrpMonster::~CGrpMonster()
{
}


BEGIN_MESSAGE_MAP(CGrpMonster, CView)
	//{{AFX_MSG_MAP(CGrpMonster)
		// HINWEIS - Der Klassen-Assistent fügt hier Zuordnungsmakros ein und entfernt diese.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Zeichnung CGrpMonster 

void CGrpMonster::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// ZU ERLEDIGEN: Code zum Zeichnen hier einfügen
}

/////////////////////////////////////////////////////////////////////////////
// Diagnose CGrpMonster

#ifdef _DEBUG
void CGrpMonster::AssertValid() const
{
	CView::AssertValid();
}

void CGrpMonster::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CGrpMonster 

void CGrpMonster::InitMonster(int nr, CMonster::MonsterTyp iTyp)
{
	if (m_pMember[nr] == NULL)
	{
		switch (iTyp)
		{
		case CMonster::MonsterTyp::SKELETT:
			m_pMember[nr] = new CSkelett();
			break;
		default:
			ASSERT(false); // unexpected monster type
		} 
		
		bool vl,vr,hl,hr;
		vl=vr=hl=hr=false;
		SUBPOS pos;	// Freien Platz suchen
		for (int i=1; i<5; i++)
			if ((i!=nr) && (m_pMember[i]!=NULL))
			{
				pos = m_pMember[i]->HoleSubPosition();
				if (pos == RECHTSVORNE) vr = true;
				else if (pos == LINKSVORNE) vl = true;
				else if (pos == LINKSHINTEN) hl = true;
				else if (pos == RECHTSHINTEN) hr = true;
			}
		if (!vl)
			pos = LINKSVORNE;
		else if (!vr)
			pos = RECHTSVORNE;
		else if (!hl)
			pos = LINKSHINTEN;
		else if (!hr)
			pos = RECHTSHINTEN;
		
		m_pMember[nr]->SetzeSubPosition(pos);
		m_grpDirection = 0;
		m_pMember[nr]->m_chrDirection= m_grpDirection;
	}
}

bool CGrpMonster::SetzeModus(int iModus)
{
	// Modus könnte sein: angst/fliehen, frozen, taub/ruhend, angreifend
	return true;
}

bool CGrpMonster::Altern()
{
	bool anyoneAlive = false;
	for (int i=1; i<5; i++)
	{
		CMonster* pMonster= (CMonster*) m_pMember[i];
		if (pMonster) {
			bool monsterAlive = pMonster->Altern();
			if (!monsterAlive)
			{
				delete m_pMember[i]; // auslöschen! todo: staubwolke malen!
				m_pMember[i] = NULL;
			}
			else {
				anyoneAlive = true;
			}
		}
	}
	return anyoneAlive;
}


void CGrpMonster::EndAttack() {
	for (int i = 1; i < 5; i++)
	{
		CMonster* pMonster = (CMonster*)m_pMember[i];
		if (pMonster) {
			pMonster->EndAttack();
		}
	}
}

void CGrpMonster::AttackHero(CGrpHeld* pHeroes) {
	for (int i = 1; i < 5; i++)
	{
		CMonster* pMonster = (CMonster*)m_pMember[i];
		if (pMonster) {					
			int dmg = pMonster->CalcDmg(1, pHeroes); // todo monster attacke random
			pMonster->AttackModeWithDmg(dmg);
		}
	}
}

bool CGrpMonster::IstBereit() {
	for (int i = 1; i < 5; i++)
	{
		CMonster* pMonster = (CMonster*)m_pMember[i];
		if (pMonster) {
			if (!pMonster->IstBereit())
				return false;
		}
	}
	return true;
}

void CGrpMonster::ActionDone() {
	// todo : attacke ist nur für 1 Monster action!
	for (int i = 1; i < 5; i++)
	{
		CMonster* pMonster = (CMonster*)m_pMember[i];
		if (pMonster) {
			pMonster->ActionDone();
		}
	}
}

CMonster* CGrpMonster::GetMonster(int ID) {
	return (CMonster*)m_pMember[ID];
}

//   0
//   |
// 1- -3
//   |
//   2
void CGrpMonster::TurnToHero(VEKTOR heroPos) {
	VEKTOR monPos = HolePosition();
	int monDir = m_grpDirection;

	int newDirection;
	if (heroPos.x < monPos.x) {
		newDirection = 3;
	}
	else if (heroPos.x > monPos.x) {
		newDirection = 1;
	}
	else if (heroPos.y < monPos.y) {
		newDirection = 0;
	}
	else {
		newDirection = 2;
	}

	for (int i = 1; i < 5; i++)
	{
		CMonster* pMonster = (CMonster*)m_pMember[i];
		if (pMonster) {
			if (pMonster->TurnTo(newDirection))
				m_grpDirection = newDirection;
			pMonster->EndAttack();
		}
	}
	
}
