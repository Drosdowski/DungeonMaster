#ifndef AFX_GRPHELD_H__7404A901_99F7_11D2_A630_008048898454__INCLUDED_
#define AFX_GRPHELD_H__7404A901_99F7_11D2_A630_008048898454__INCLUDED_

// GrpHeld.h : Header-Datei
//
#include "GrpChar.h"
#include "..\Held.h"
/////////////////////////////////////////////////////////////////////////////
// Ansicht CGrpChar 

class CMonster;
class CItem;
class CAttackInfos;
class CMonsterInfos;
class CGrpHeld: public CGrpChar
{
public:
	CGrpHeld(VEKTOR pos, COMPASS_DIRECTION richt);
	

// Implementierung
public:
	CHeld* InitHeld(int nr);
	
	CHeld* GetHero(int iID) { return (CHeld*)m_pMember[iID]; }
	CHeld* GetActiveHero() { return (CHeld*)m_pMember[m_iAktiverHeld]; }
	CHeld* GetAttackingHero();

	int GetActiveWizard() { return m_iAktiverZauberer; }
	int GetNumberOfHeroes() { return m_iAnzHelden;  }
	int GetActionPhase() { return m_iPhase; }
	
	CItem* GetItemInHand();
	void TakeItemInHand(CItem* item) { return GetActiveHero()->TakeItemInHand(item); }
	void EmptyHand() { return GetActiveHero()->EmptyHand(); }
	virtual bool Laufbereit();
	void Laufen(VEKTOR WunschPos);

	void PutGetItem(int handOfHeroId, int heroId);

	void Aktiviere(int n);
	void PassAction();
	void ChooseHeroForAction(int ID);
	void DoActionForChosenHero(int ID, CGrpChar* pVictims, CAttackInfos* attackInfos, CMonsterInfos* monsterInfos, int diff);
	bool SetActiveCaster(int ID);
	
	bool Altern();

	CHeld* GetHeroForAction() { return GetHero(m_iHeroForAction); }
	CHeld* ClosestHeroTo(CMonster* monster);
// überschriebene Methoden
	
	bool SetzeModus(CDC* pDC, int iModus);	

	virtual ~CGrpHeld();

	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	int m_iPhase = 1;
	int m_iPhaseDelay = 0;
	int m_iHeroForAction = 1;
	int m_iAktiverZauberer = 0;
	int m_iAktiverHeld = 1;
	int m_iAnzHelden = 0;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_GRPHELD_H__7404A901_99F7_11D2_A630_008048898454__INCLUDED_
