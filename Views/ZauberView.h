#ifndef AFX_ZAUBERVIEW_H__1ECC0BA4_ADBD_11D4_B076_0000E857EB66__INCLUDED_
#define AFX_ZAUBERVIEW_H__1ECC0BA4_ADBD_11D4_B076_0000E857EB66__INCLUDED_

// ZauberView.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Ansicht CZauberView 

class CGrpHeld;
class CZauberView
{
public:
	CZauberView();           // Dynamische Erstellung verwendet geschützten Konstruktor
	virtual ~CZauberView();

// Attribute
public:

// Operationen


// Implementierung
public:
	void Zeichnen(CPictures* pPictures, CDC* pDC, int iActiveWizard);

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_ZAUBERVIEW_H__1ECC0BA4_ADBD_11D4_B076_0000E857EB66__INCLUDED_
