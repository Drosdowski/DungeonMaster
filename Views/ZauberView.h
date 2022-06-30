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
	int getRuneTableId() { return m_iRuneTable; }
	void resetRuneTable();
	void storeRune(int index);
	int* getSpell() { return m_spell; }

// Implementierung
public:
	void Zeichnen(CPictures* pPictures, CDC* pDC, int iActiveWizard);

private:
	int* m_spell = NULL;
	int m_iRuneTable;
	void nextRuneTable();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_ZAUBERVIEW_H__1ECC0BA4_ADBD_11D4_B076_0000E857EB66__INCLUDED_
