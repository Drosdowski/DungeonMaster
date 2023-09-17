#include "stdafx.h"
#include "Champion.h"

CChampion::CChampion(CString text) {
	int newlinePos = text.Find(_T("\n"));
	m_name = text.Left(newlinePos);
	m_vitals.str.Max = 60; m_vitals.str.Aktuell = 60;
	m_vitals.dex.Max = 50; m_vitals.dex.Aktuell = 50;
	m_vitals.vit.Max = 40; m_vitals.vit.Aktuell = 40;
	m_vitals.wis.Max = 30; m_vitals.wis.Aktuell = 30;
}