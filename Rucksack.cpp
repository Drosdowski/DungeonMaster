// Rucksack.cpp : implementation file
//

#include "stdafx.h"
#include "Rucksack.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRucksack

CRucksack::CRucksack()
{
	m_iModusExtend = MOD_EXT_NORMAL;

}

CRucksack::~CRucksack()
{
}


/////////////////////////////////////////////////////////////////////////////
// CRucksack message handlers


void CRucksack::SetzeModusExtend(int iModusExtend)
{
	m_iModusExtend = iModusExtend;
}
