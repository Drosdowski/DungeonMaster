// DMDoc.h : interface of the CDMDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DMDOC_H__0852F62B_89E0_11D2_9F0B_008048898454__INCLUDED_)
#define AFX_DMDOC_H__0852F62B_89E0_11D2_9F0B_008048898454__INCLUDED_

#include "StdAfx.h"	// Added by ClassView
#include <string>
#include <Mmsystem.h> // included in the <Windows.h> header
#include <mciapi.h>  // included in the <Windows.h> header
#pragma comment(lib, "Winmm.lib")

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CDMDoc : public CDocument
{
protected: // create from serialization only
	CDMDoc();
	DECLARE_DYNCREATE(CDMDoc)

	// Attributes
	// Operations

public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	void PlayDMSound(std::string file);
	
	virtual ~CDMDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CDMDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DMDOC_H__0852F62B_89E0_11D2_9F0B_008048898454__INCLUDED_)
