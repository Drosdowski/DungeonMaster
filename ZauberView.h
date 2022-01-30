#ifndef AFX_ZAUBERVIEW_H__1ECC0BA4_ADBD_11D4_B076_0000E857EB66__INCLUDED_
#define AFX_ZAUBERVIEW_H__1ECC0BA4_ADBD_11D4_B076_0000E857EB66__INCLUDED_

// ZauberView.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Ansicht CZauberView 

class CGrpHeld;
class CZauberView : public CView
{
public:
	CZauberView();           // Dynamische Erstellung verwendet geschützten Konstruktor
	DECLARE_DYNCREATE(CZauberView)

// Attribute
public:

// Operationen
public:
	bool setActiveCaster(int ID, CGrpHeld* pGrpHelden);

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CZauberView)
	protected:
	virtual void OnDraw(CDC* pDC);      // Überschrieben zum Zeichnen dieser Ansicht
	//}}AFX_VIRTUAL

// Implementierung
public:
	void Zeichnen(CPictures* pPictures, CDC* pDC);
	virtual ~CZauberView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	//{{AFX_MSG(CZauberView)
		// HINWEIS - Der Klassen-Assistent fügt hier Member-Funktionen ein und entfernt diese.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_ZAUBERVIEW_H__1ECC0BA4_ADBD_11D4_B076_0000E857EB66__INCLUDED_
