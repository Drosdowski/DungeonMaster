#ifndef AFX_GRPHELD_H__7404A901_99F7_11D2_A630_008048898454__INCLUDED_
#define AFX_GRPHELD_H__7404A901_99F7_11D2_A630_008048898454__INCLUDED_

// GrpHeld.h : Header-Datei
//
#include "GrpChar.h"
#include "..\Held.h"
/////////////////////////////////////////////////////////////////////////////
// Ansicht CGrpChar 

class CItem;
class CAttackInfos;
class CChampion;
class CGrpHeld: public CGrpChar
{
public:
	CGrpHeld(VEKTOR pos, COMPASS_DIRECTION richt);
	

// Implementierung
public:
	void InitHeld(int nr);
	void InitHeld(CChampion* champion, const int nr, int hp_akt, int st_akt, int ma_akt);
	void RessurectHero(CString text, int heroId);
	
	CHeld* GetHero(int iID) { return (CHeld*)m_pMember[iID]; }
	CHeld* GetHeroBySubPos(SUBPOS_ABSOLUTE pos);
	CHeld* GetActiveHero() { return (CHeld*)m_pMember[m_iAktiverHeld]; }
	CHeld* GetAttackingHero();

	int GetActiveWizard() { return m_iAktiverZauberer; }
	int GetNumberOfHeroes() { return m_iAnzHelden;  }
	Phase GetActionPhase() { return m_iPhase; }
	
	CItem* GetItemInHand() { return m_pItemInHand; }
	void TakeItemInHand(CItem* item);
	void EmptyHand();

	virtual bool Laufbereit();
	bool isAlive();
	void Laufen(VEKTOR WunschPos, bool teleport);

	void PutGetItem(int handOfHeroId, int heroId);

	void Aktiviere(int n);
	void setPhase(Phase p) { m_iPhase = p; }
	void setPhaseDelay(int n) { m_iPhaseDelay = n; }
	void PassAction();
	void ChooseHeroForAction(int ID);
	bool SetActiveCaster(int ID);
	
	bool Altern();

	CHeld* GetHeroForAction() { return GetHero(m_iHeroForAction); }
// überschriebene Methoden
	
	GroupMode GetModus() { return m_Modus; }
	bool AsleepAndAttacked();
	void SetzeModus(GroupMode modus);
	void ChangeCompass();

	virtual ~CGrpHeld();

private:
	void NewHero(CChampion* champ, int nr, int hp_akt, int st_akt, int ma_akt);

	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	Phase m_iPhase = CHOOSE_HERO;
	int m_iPhaseDelay = 0;
	int m_iHeroForAction = 1;
	int m_iAktiverZauberer = 0;
	int m_iAktiverHeld = 1;
	int m_iAnzHelden = 0;
	CItem* m_pItemInHand = NULL;
	GroupMode m_Modus;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_GRPHELD_H__7404A901_99F7_11D2_A630_008048898454__INCLUDED_
