#ifndef AFX_GRPCHAR_H__7B688A40_9939_11D2_A630_008048898454__INCLUDED_
#define AFX_GRPCHAR_H__7B688A40_9939_11D2_A630_008048898454__INCLUDED_

// GrpChar.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Ansicht CGrpChar 

class CHelpfulValues;
class CCharacter;
class CGrpChar : public CView
{
#define LINKS 1
#define RECHTS 2
#define LAUFEN 0
#define RUCKSACK 3

public:
	CGrpChar();
protected:
	DECLARE_DYNCREATE(CGrpChar)

// Attribute
protected:
	CDC* m_pDC;
	CCharacter* m_pMember[5];

// Operationen
public:
	int HoleRichtung() {return m_grpDirection;};
	VEKTOR HolePosition() {return m_posPosition;};

// �berschreibungen
protected:
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CGrpChar)
	virtual void OnDraw(CDC* pDC);      // �berschrieben zum Zeichnen dieser Ansicht
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual bool Altern() { return true; };
	virtual void Zeichnen(CDC* pDC, int iModus) {};
	virtual bool SetzeModus(CDC* pDC, int iModus) {return false;};
	virtual bool Laufbereit();
	virtual int InReihe(int byte);
	VEKTOR GetPos() { return m_posPosition;  }
	CCharacter* GetChar(int ID) { return m_pMember[ID]; }
	
	VEKTOR HoleZielFeld(int iRichtung); // VORWAERTS, etc
	void Kollision();
	void Laufen(VEKTOR WunschPos);
	void DamageFrom(CGrpChar* pGrpMon, bool DamageFrom);
	void DoDamage(int dmg, bool DamageFrom);

	void Drehen(int iRichtung);
	virtual ~CGrpChar();
protected:
	int m_grpDirection;
	VEKTOR m_posPosition;
	CHelpfulValues* m_values;

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generierte Nachrichtenzuordnungsfunktionen
protected:
public:
	//{{AFX_MSG(CGrpChar)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio f�gt zus�tzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_GRPCHAR_H__7B688A40_9939_11D2_A630_008048898454__INCLUDED_
