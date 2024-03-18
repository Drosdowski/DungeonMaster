// DMDoc.cpp : implementation of the CDMDoc class
//

#include "stdafx.h"
#include "DM.h"

#include "Views\Raumview.h"
#include "DMDoc.h"
#include "Mobs\MobGroups\GrpHeld.h"
#include "CalculationHelper\CHelpfulValues.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDMDoc

IMPLEMENT_DYNCREATE(CDMDoc, CDocument)

BEGIN_MESSAGE_MAP(CDMDoc, CDocument)
	//{{AFX_MSG_MAP(CDMDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDMDoc construction/destruction


CDMDoc::CDMDoc()
{
	((CDMApp*)AfxGetApp())->SetDoc(this);
	
}

CDMDoc::~CDMDoc()
{
	((CDMApp*)AfxGetApp())->SetDoc(NULL);
}

BOOL CDMDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CDMDoc serialization

void CDMDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDMDoc diagnostics

#ifdef _DEBUG
void CDMDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDMDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDMDoc commands


	
void CDMDoc::PlayDMSound(std::string file) {
	// std::string file = "C:\\Source\\C++\\DM\\sound\\DMCSB-SoundEffect-Attack(Skeleton-AnimatedArmour-PartySlash).mp3";
	std::string cmd = "open \"" + file + "\" type mpegvideo alias mp3";
	mciSendString("close mp3", NULL, 0, NULL);
	mciSendString(cmd.c_str(), NULL, 0, NULL);
	mciSendString("play mp3", NULL, 0, NULL);

}
