#ifndef AFX_GRPCHAR_H__7B688A40_9939_11D2_A630_008048898454__INCLUDED_
#define AFX_GRPCHAR_H__7B688A40_9939_11D2_A630_008048898454__INCLUDED_

// GrpChar.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Ansicht CGrpChar 

class CHelpfulValues;
class CCharacter;
class CGrpChar 
{
#define LINKS 1
#define RECHTS 2
#define LAUFEN 0
#define RUCKSACK 3

public:
	CGrpChar();

// Attribute
protected:
	CDC* m_pDC;
	CCharacter* m_pMember[5];

// Operationen
public:
	void SetNewCharOnNextFreePos(int nr);
	COMPASS_DIRECTION HoleRichtung() { return m_grpDirection; };
	void SetzeRichtung(COMPASS_DIRECTION richt) { m_grpDirection = richt; }
	VEKTOR HolePosition() {return m_posPosition;};


// Implementierung
public:
	virtual bool Altern() { return true; };
	virtual bool SetzeModus(CDC* pDC, int iModus) {return false;};
	virtual bool Laufbereit();
	virtual int InReihe(int byte);
	VEKTOR GetPos() { return m_posPosition;  }
	CCharacter* GetChar(int ID) { return m_pMember[ID]; }
	
	VEKTOR HoleZielFeld(int iRichtung); // VORWAERTS, etc
	void Kollision();
	void FallingDamage();
	void Laufen(VEKTOR WunschPos);
	void DamageFrom(CCharacter* pMon, VEKTOR hisPos, bool DamageFrom);
	void DoDamage(int dmg, VEKTOR hisPos, bool DamageFrom);

	void DrehenRelativ(int iRelRichtung);
	void DrehenAbsolut(COMPASS_DIRECTION iRichtung);
	virtual ~CGrpChar();
protected:
	COMPASS_DIRECTION m_grpDirection; 
	VEKTOR m_posPosition;
	CHelpfulValues* m_values;
	CCharacter* NearestTarget(VEKTOR hisPos);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_GRPCHAR_H__7B688A40_9939_11D2_A630_008048898454__INCLUDED_
