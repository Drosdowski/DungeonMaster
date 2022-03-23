#ifndef AFX_CHARACTER_H__15FAEB00_991E_11D2_A630_008048898454__INCLUDED_
#define AFX_CHARACTER_H__15FAEB00_991E_11D2_A630_008048898454__INCLUDED_

// Character.h : Header-Datei
//
/////////////////////////////////////////////////////////////////////////////
// Ansicht CCharacter 

class CGrpChar;
class CCharacter
{
protected:
	CCharacter();           // Dynamische Erstellung verwendet geschützten Konstruktor

// Attribute
public:
	virtual WERTE Hp() { return m_HP; };
	virtual WERTE St() { return m_ST; };
	virtual WERTE Ma() { return m_MA; };

	int ReceivedDmg() { return m_iReceivedDmg;}
	int GetDirection() { return m_chrDirection; }
	bool IstBereit() { return m_iReady == 0; };
	bool isAttacking() { return m_attacking; }

// Operationen
public:
	void SetzeSubPosition(SUBPOS_ABSOLUTE pos) { m_subPosition = pos; };
	void SetDirection(int direction) { m_chrDirection = direction; }
	void AddDmg(int value) { m_iReceivedDmg += value; }
	void ResetDmg() { m_iReceivedDmg = 0; }

	

// Implementierung
public:
	virtual bool Altern();
	virtual SUBPOS_ABSOLUTE HoleSubPosition() { return m_subPosition;};
	virtual bool Kollision(int richt, CGrpChar* pGrpChar);
	virtual void WerteTemporaerAendern(int hp, int st, int ma);
	virtual void WertePermanentAendern(int hp, int st, int ma);
	virtual int CalcDmg(int ID, CGrpChar* pOpponents);
	bool InFrontOfOpponent(VEKTOR myPos, VEKTOR hisPos);
	virtual ~CCharacter();

	void ActionDone() { m_iReady = m_SpeedDelay; } // wartezeit triggern, abhängig von Speed
	void AttackModeWithDmg(int damage);
	void EndAttack();

	int GetDealingDamage() { return m_dealingDmg; }

	bool westOf(VEKTOR myPos, VEKTOR hisPos);
	bool eastOf(VEKTOR myPos, VEKTOR hisPos);
	bool northOf(VEKTOR myPos, VEKTOR hisPos);
	bool southOf(VEKTOR myPos, VEKTOR hisPos);

	// Generierte Nachrichtenzuordnungsfunktionen

protected:
	int m_iReceivedDmg; // PASSIV- Erhaltener Schaden, zur Anzeige.
	int m_chrDirection;	// initial und bei Grp.-Bewegung gleich der Gruppenvariable; ändert sich nur bei angriffen
	int m_ApproxDmg; // AKTIV - Durchschnittlicher Schaden plus minus random
	int m_SpeedDelay; // 0 = Schnellstes (Zyklen bis zur Aktion)
	int m_dealingDmg; // AKTIV - tatsächlicher aktueller Schaden, zur Anzeige.
	bool m_attacking = false;
	CDC* m_pDC;

	WERTE m_MA;	// Mana
	WERTE m_ST;	// Stamina
	WERTE m_HP;	// Hitpoints	

	SUBPOS_ABSOLUTE m_subPosition;
	int m_iReady;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_CHARACTER_H__15FAEB00_991E_11D2_A630_008048898454__INCLUDED_
