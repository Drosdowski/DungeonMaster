#ifndef AFX_ZAUBERVIEW_H__1ECC0BA4_ADBD_11D4_B076_0000E857EB66__INCLUDED_
#define AFX_ZAUBERVIEW_H__1ECC0BA4_ADBD_11D4_B076_0000E857EB66__INCLUDED_

// ZauberView.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Ansicht CZauberView 

class CPictures;
class CZauberView
{
public:
	CZauberView();           // Dynamische Erstellung verwendet geschützten Konstruktor
	virtual ~CZauberView();

	
// Attribute
public:
// Operationen
	//int getRuneTableId(int heroId) { return m_iRuneTable[heroId]; }
	//int GetPower(int heroId);
	//void resetRuneTable(int heroId);
	//void storeRune(int index, int heroId);
	//int* getSpell(int heroId) { return m_spell[heroId]; }

// Implementierung
public:
	void Zeichnen(CPictures* pPictures, CDC* pDC, int iActiveWizard, int runeTableId, int* runeIds);

//private:
//	int* m_spell[5];
//	int m_iRuneTable[5];
//	void nextRuneTable(int heroId);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_ZAUBERVIEW_H__1ECC0BA4_ADBD_11D4_B076_0000E857EB66__INCLUDED_
