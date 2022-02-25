// Held.cpp : implementation file
//

#include "stdafx.h"
#include "Rucksack.h"
#include "Pictures\CPictures.h"
#include "..\CHelpfulValues.h"
#include "Monster.h"
#include "Held.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHeld

CHeld::CHeld(CPictures* pPictures, int iIndex, CString strName): CCharacter()
{
	m_HP.Max = 100;
	m_MA.Max = 100;
	m_ST.Max = 100;
	
	m_HP.Aktuell = m_HP.Max;
	m_ST.Aktuell = m_MA.Max;
	m_MA.Aktuell = m_ST.Max;
	m_bAktiv = true;
	m_attacking = false;
	m_strName = strName;
	m_iIndex = iIndex;
	m_iReceivedDmg = 0;
	m_iFood = maxFood;
	m_iWater = maxWater;
	for (int i = 1; i<5; i++)
		m_sExp[i] = 200;
	switch (iIndex)
	{
	case 1:
		m_Farbe[1] = HELLGRUEN; break;
	case 2:
		m_Farbe[2] = GELB; break;
	case 3:
		m_Farbe[3] = ROT; break;
	case 4:
		m_Farbe[4] = BLAU; break;
	}

	m_pRucksack = new CRucksack(pPictures);
}

CHeld::CHeld()
{
}

CHeld::~CHeld()
{
	delete m_pRucksack;
}


/////////////////////////////////////////////////////////////////////////////
// CHeld message handlers

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////// Zeichenroutinen /////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void CHeld::BildZeichnen(CDC* pDC)
{

}

void CHeld::WerteZeichnen(CDC* pDC)
{
	// Hp, St, Ma - Balken
	int x = (m_iIndex-1)*138+94;
	pDC->FillSolidRect(CRect(x, 4, x+35, 52), GANZDUNKELGRAU);
	pDC->FillSolidRect(CRect(x, 52-(48*m_HP.Aktuell/m_HP.Max), x+7, 52), m_Farbe[m_iIndex]);
	pDC->FillSolidRect(CRect(x+14, 52-(48*m_ST.Aktuell/m_ST.Max), x+21, 52), m_Farbe[m_iIndex]);
	pDC->FillSolidRect(CRect(x+28, 52-(48*m_MA.Aktuell/m_MA.Max), x+35, 52), m_Farbe[m_iIndex]);
}

void CHeld::WaffeZeichnen(CDC* pDC)
{
	// ggf. die Hand (zweimal!)
}

void CHeld::SymbolZeichnen(CDC* pDC, CPictures* pPictures, int heroGrpDir)
{
	// kleines Symbol oben rechts; zeigt Richtung / Subpos der einzelnen Helden an
	SUBPOS relPos = CHelpfulValues::GetRelativeSubPosActive(m_subPosition, heroGrpDir);
	CDC tmpdc;
	tmpdc.CreateCompatibleDC(pDC);
	
	tmpdc.SelectObject(pPictures->GetRucksack());
	int sx = 560 +(((m_iIndex==1) || (m_iIndex ==4)) ? 0 : 40);
	int sy =	   (m_iIndex > 2) ? 28 : 0;
	
	int dx = 560 +((relPos & 0x1000) ? 0 : 40);
	int dy =	   (relPos & 0x0100) ? 0 : 28;
	pDC->BitBlt(dx,dy,40,28,&tmpdc,sx,sy,SRCCOPY);
	tmpdc.DeleteDC();
}

void CHeld::HaendeZeichnen(CDC* pDC, CPictures* pPictures)
{
	// wird ggf. mit Waffezeichnen verschmelzen
	CDC tmpdc;
	tmpdc.CreateCompatibleDC(pDC);
	
	tmpdc.SelectObject(pPictures->GetRucksack());
	pDC->BitBlt((m_iIndex-1)*138, 0, 138, 64, &tmpdc, 0, 0, SRCCOPY);

	tmpdc.DeleteDC();
}

void CHeld::KnochenZeichnen(CDC* pDC, CPictures* pPictures)
{
	CDC tmpdc;
	tmpdc.CreateCompatibleDC(pDC);
	
	tmpdc.SelectObject(pPictures->GetKram());
	pDC->BitBlt((m_iIndex-1)*138, 0, 138, 56, &tmpdc, 276, 320, SRCCOPY);

	tmpdc.DeleteDC();
}

void CHeld::RucksackZeichnen(CDC* pDC)
{
	m_pRucksack->Zeichnen(pDC);
	if (m_pRucksack->HoleModusExtend() == MOD_EXT_NORMAL)
		m_pRucksack->ZeichneHungerDurst(pDC, m_iFood, m_iWater);
	else if (m_pRucksack->HoleModusExtend() == MOD_EXT_AUGE)
		m_pRucksack->ZeichneSkills(pDC, m_sExp, m_sVitals);
	m_pRucksack->ZeichneHpStMa(pDC, m_HP, m_ST, m_MA);
}

void CHeld::NameZeichnen(CDC* pDC)
{
	if (m_bAktiv)
		pDC->SetTextColor(GELB);
	else
		pDC->SetTextColor(HELLBRAUN);
	pDC->SetBkColor(DUNKELGRAU);
	int x = (m_iIndex-1)*138;
	pDC->ExtTextOut(x+4,-3,ETO_CLIPPED | ETO_OPAQUE, CRect(x,0,x+86,10), m_strName, NULL);
}

void CHeld::SchadenZeichnen(CDC* pDC, CPictures* pPictures)
{
	if (m_iReceivedDmg>0) 
	{
		CDC tmpdc;
		tmpdc.CreateCompatibleDC(pDC);
		
		tmpdc.SelectObject(pPictures->GetKram());
		pDC->BitBlt((m_iIndex-1)*138, 0, 84, 14, &tmpdc, 192, 92, SRCCOPY);

		tmpdc.DeleteDC();
		m_iReceivedDmg = 0;
		DeleteDC(tmpdc);
	}
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////// Hilfsfunktionen /////////////////////////////
/////////////////////////////////////////////////////////////////////////////

bool CHeld::Altern()
{
	bool alive = CCharacter::Altern();
	if (m_dealingDmg > 0)
	{
		m_dealingDmg = 0;
		// phase
	}

	// erstmal konstant, später hp & st abhängig 
	// von VIT, ma von WIS sowie von FOOD & WATER
	if (alive)
	{
		WerteTemporaerAendern(1, 1, 1);
		//m_iFood--;
		//m_iWater--;
		if (m_iFood < 50)
			WerteTemporaerAendern(0, -1, 0);
		if (m_iWater < 50)
			WerteTemporaerAendern(0, -1, 0);
		if (m_iFood < 15)
			WerteTemporaerAendern(0, -2, 0);
		if (m_iWater < 15)
			WerteTemporaerAendern(0, -2, 0);
		if (m_ST.Aktuell <= 0)
		{
			m_HP.Aktuell = 0;	// zu Tode erschöpft
			return false;
		}
	}
	return alive;
}

int CHeld::CalcDmg(int ID, CGrpChar* pOpponents) {
	// CHeld* hero = pHeroes->ClosestHeroTo(pMonster); // Todo berechnen, welcher Held am nahesten steht!
	// TODO temporär; Waffe 1 = 1 Schaden, ...
	return ID;
}

void CHeld::Essen(int amount) {
	m_iFood = min(maxFood, m_iFood + amount);
}

void CHeld::Trinken(int amount) {
	m_iWater = min(maxWater, m_iWater + amount);
}