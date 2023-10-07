#include "stdafx.h"
#include "Champion.h"

CChampion::CChampion(CString text) {
	int i = 0;
	CStringArray saItems;
	for (CString sItem = text.Tokenize("\n", i); i >= 0; sItem = text.Tokenize("\n", i))
	{
		saItems.Add(sItem);
	}
	int sub = 0;
	m_name = saItems.GetAt(0);
	if (saItems.GetSize() == 6)
	{
		m_subname = saItems.GetAt(1);
	}
	else {
		sub = 1;
	}
	CString gender = saItems.GetAt(2-sub);
	m_gender = (gender == "F" ? female : male);

	CString block1 = saItems.GetAt(3 - sub);
	ParseVitalsFromText(saItems.GetAt(4 - sub));
	ParseLevelsFromText(saItems.GetAt(5 - sub));
}

CChampion::CChampion(const char* name, const char* subname, bool isMale, VITALS vitals) {
	m_name = name;
	m_subname = subname;
	m_vitals = vitals;
	m_gender = (isMale ? male : female);
}


void CChampion::ParseVitalsFromText(CString block2) {
	// AA = 00 ... AP = 15
	// BA = 16 ... BP = 31
	// CA = 32 ... CP = 47
	// DA = 48 ... DP = 63  
	// 
	int str = TupelToNumber(block2.Mid(2, 2));
	m_vitals.str.Aktuell = str;
	m_vitals.str.Max = str;
	int dex = TupelToNumber(block2.Mid(4, 2));
	m_vitals.dex.Aktuell = dex;
	m_vitals.dex.Max = dex;
	int vit = TupelToNumber(block2.Mid(6, 2));
	m_vitals.vit.Aktuell = vit;
	m_vitals.vit.Max = vit;
	int wis = TupelToNumber(block2.Mid(8, 2));
	m_vitals.wis.Aktuell = wis;
	m_vitals.wis.Max = wis;
	int af = TupelToNumber(block2.Mid(10, 2));
	m_vitals.af.Aktuell = af;
	m_vitals.af.Max = af;
	int am = TupelToNumber(block2.Mid(12, 2));
	m_vitals.am.Aktuell = am;
	m_vitals.am.Max = am;
	//																								  xxxxxxxxxxxx                           
	// Syra: Novice Priest / Apprentice WIzard   38/35/43/45/42/40	=> 53/72/15		AADFACNAAAAP	DHCGCDCLCNCKCI	AAAAAAAAADBBACDD
	// Chani: Novice Fighter / Apprentice WIzard 37/47/57/37/47/37  => 47/67/17		AACPACJOAABB	DJCFCPDJCFCPCF	BDACAAAAAAAADCDB
	// Elija: Novice Fighter / Apprentice Priest 42/40/42/36/53/40					AADMACEEAABG	DCCKCICKCEDFCI	BBCAAAAACBECAAAA
	//																												FIFININIPRPRWIWI  
	// Gando: Apprentice Ninja / Novice Wizard   39/45/47/33/48/43  => 39/63/26		AACHACHGAABK	DCCHCNCPCBDACL	AAAADACDAAAABCBC
	// Alex: Apprentice Ninja / Novice Wizard										AADCACDKAAAN	CPCMDHCNCICDCI	AAAADCDCAAAACCBC
	// Linflas: Appr. Fighter / Novice Wizard    45/47/47/35/50/35  => 65/50/12		AAEBABPEAAAM	CNCNCNCPCDDCCD	ABCEAABAABAAABCC
	// Nabi: Apprentice Priest / Novice Wizard   41/36/45/45/55/55  => 55/65/13		AADHACIKAAAN	CICJCECNCNDHDH	AAAAAAAABBECBBBB

	// Hissa: Apprentice Fighter / Novice Ninja  58/48/35/35/43/55  => 80/61/5		AAFAACGCAAAF	CIDKDACDCDCLDH	EDAAADBAAAAAAAAA
	// Halk: Journeyman Figher					 55/43/30/46/38/48  => 90/75/0		AAFKACOOAAAA	CIDHCLBOCOCGDA	EAEAAAAAAAAAAAAA
	// Gothmog: Journeymay Wizard													AADMACCGAABC	BOCICDDACCDCDL	AAAAAAAAAAAAEDCC
}

void CChampion::ParseLevelsFromText(CString block3) {

}


int CChampion::TupelToNumber(CString str) {
	char firstLetter = str.GetAt(0);
	char secondLetter = str.GetAt(1);
	
	return (firstLetter - 65) * 16 + (secondLetter - 65);
}
