#ifndef AFX_CHARACTER_H__15FAEB00_991E_11D2_A630_008048898454__INCLUDED_
#define AFX_CHARACTER_H__15FAEB00_991E_11D2_A630_008048898454__INCLUDED_

// Character.h : Header-Datei
//
/////////////////////////////////////////////////////////////////////////////
// Ansicht CCharacter 

class CCharacter
{
protected:
	CCharacter(bool isHero);           // Dynamische Erstellung verwendet geschützten Konstruktor

// Attribute
public:
	virtual WERTE Hp() { return m_HP; }
	
	int ReceivedDmg() { return m_iReceivedDmg;}
	int ReceivedPoison() { return m_iReceivedPoison; }
	COMPASS_DIRECTION GetDirection() { return m_chrDirection; }
	bool isAttacking() { return m_attacking; }
	bool IsHero() {	return m_isHero; }
	bool isAlive() { return m_HP.Aktuell > 0; }

// Operationen
public:
	void SetzeSubPosition(SUBPOS_ABSOLUTE pos) { m_subPosition = pos; }
	void SetDirection(COMPASS_DIRECTION direction) { m_chrDirection = direction; }
	void AddDmg(int value);
	void AddPoison(int value);
	void ResetDmg() { m_iReceivedDmg = 0; m_iReceivedPoison = 0; }
	

// Implementierung
public:
	virtual bool Altern() { return isAlive(); }
	virtual SUBPOS_ABSOLUTE HoleSubPosition() { return m_subPosition;}
	virtual void MoveDone() {};
	bool InFrontOfOpponent(VEKTOR myPos, VEKTOR hisPos, bool emptyNorthRow, bool emptyEastRow, bool emptySouthRow, bool emptyWestRow);
	virtual ~CCharacter();

	void AttackModeWithDmg(int damage, int poison);
	void EndAttack();

	int GetDealingDamage() { return m_dealingDmgToDraw; }
	int GetDealingPoison() { return m_dealingPoison; }

	bool ReceiveDamage(int dmg);

	// Generierte Nachrichtenzuordnungsfunktionen

protected:
	int m_iReceivedDmg; // PASSIV- Erhaltener Schaden, zur Anzeige.
	int m_iReceivedPoison;
	COMPASS_DIRECTION m_chrDirection;	// initial und bei Grp.-Bewegung gleich der Gruppenvariable; ändert sich nur bei angriffen
// TODO	int m_ApproxDmg; // AKTIV - Durchschnittlicher Schaden plus minus random
// TODO	int m_SpeedDelay; // 0 = Schnellstes (Zyklen bis zur Aktion)
	int m_dealingDmg; // AKTIV - tatsächlicher aktueller Schaden, zur Anzeige.
	int m_dealingDmgToDraw;
	int m_dealingPoison;
	bool m_attacking = false;

	WERTE m_HP;	// Hitpoints	

	SUBPOS_ABSOLUTE m_subPosition;
	bool m_isHero;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_CHARACTER_H__15FAEB00_991E_11D2_A630_008048898454__INCLUDED_
