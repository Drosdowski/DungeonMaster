#ifndef AFX_CHARACTER_H__15FAEB00_991E_11D2_A630_008048898454__INCLUDED_
#define AFX_CHARACTER_H__15FAEB00_991E_11D2_A630_008048898454__INCLUDED_

// Character.h : Header-Datei
//
/////////////////////////////////////////////////////////////////////////////
// Ansicht CCharacter 

class CPictures;
class CGrpChar;
class CCharacter : public CView
{
protected:
	CCharacter();           // Dynamische Erstellung verwendet geschützten Konstruktor
	DECLARE_DYNCREATE(CCharacter)

// Attribute
public:

// Operationen
public:
	virtual int Hp()				 { return m_HP.Aktuell;};
	virtual int St()				 { return m_ST.Aktuell;};
	virtual int Ma()				 { return m_MA.Aktuell;};
	virtual bool IstBereit()		 { return m_iReady == 0;};

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CCharacter)
	protected:
	virtual void OnDraw(CDC* pDC);      // Überschrieben zum Zeichnen dieser Ansicht
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual bool Altern();
	virtual void SetzeSubPosition(SUBPOS pos) {m_subPosition = pos;};
	virtual SUBPOS HoleSubPosition() { return m_subPosition;};
	virtual bool Kollision(int richt, CGrpChar* pGrpChar);
	virtual void WerteTemporaerAendern(int hp, int st, int ma);
	virtual void WertePermanentAendern(int hp, int st, int ma);
	virtual int CalcDmg(int ID, CGrpChar* pOpponents);
	virtual ~CCharacter();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	bool isAttacking() { return m_attacking; }
	void ActionDone() { m_iReady = m_SpeedDelay; } // wartezeit triggern, abhängig von Speed
	void AttackModeWithDmg(int damage);
	void EndAttack();

	// TODO möglichst viel nach PROTECTED

	CPictures* m_pPictures;
	int m_SpeedDelay; // 0 = Schnellstes (Zyklen bis zur Aktion)
	
	int m_ApproxDmg; // AKTIV - Durchschnittlicher Schaden plus minus random
	int m_dealingDmg; // AKTIV - tatsächlicher aktueller Schaden, zur Anzeige.
	int m_iReceivedDmg; // PASSIV- Erhaltener Schaden, zur Anzeige.

	int m_chrDirection;	// initial und bei Grp.-Bewegung gleich der Gruppenvariable; ändert sich nur bei angriffen

	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	bool m_attacking = false;
	CDC* m_pDC;

	WERTE m_MA;	// Mana
	WERTE m_ST;	// Stamina
	WERTE m_HP;	// Hitpoints	

	SUBPOS m_subPosition;
	int m_iReady;

	//{{AFX_MSG(CCharacter)
		// HINWEIS - Der Klassen-Assistent fügt hier Member-Funktionen ein und entfernt diese.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_CHARACTER_H__15FAEB00_991E_11D2_A630_008048898454__INCLUDED_
