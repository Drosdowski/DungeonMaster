// DM.h : main header file for the DM application
//

#if !defined(AFX_DM_H__0852F625_89E0_11D2_9F0B_008048898454__INCLUDED_)
#define AFX_DM_H__0852F625_89E0_11D2_9F0B_008048898454__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDMApp:
// See DM.cpp for the implementation of this class
//

class CDMView;
class CDMDoc;
class CDMApp : public CWinApp
{
public:
	CDMDoc* m_pDoc;
	CDMApp();
	CDMView* m_pView;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDMApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	void SetView(CDMView* pView);
	void SetDoc(CDMDoc* pDoc);
	//{{AFX_MSG(CDMApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	long m_lCount;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DM_H__0852F625_89E0_11D2_9F0B_008048898454__INCLUDED_)
