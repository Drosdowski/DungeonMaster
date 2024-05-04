#include "stdafx.h"
#include "Champion.h"

CChampion::CChampion(CString text, int heroId) {
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
	m_heroId = heroId;
	ParseOtherFromText(saItems.GetAt(3 - sub));
	ParseVitalsFromText(saItems.GetAt(4 - sub));
	ParseLevelsFromText(saItems.GetAt(5 - sub));
	
}

CChampion::CChampion(const char* name, const char* subname, bool isMale, int heroId, VITALS vitals, int hp, int st, int ma) {
	m_name = name;
	m_subname = subname;
	m_vitals = vitals;
	m_gender = (isMale ? male : female);
	m_hp = hp;
	m_st = st;
	m_ma = ma;
}

void CChampion::ParseOtherFromText(CString block1) {
	int hp = TupelToNumber(block1.Mid(2, 2));
	int st = TupelToNumber(block1.Mid(4, 2)) * 256 + TupelToNumber(block1.Mid(6, 2)); // Faktor 10
	int ma = TupelToNumber(block1.Mid(10, 2));
	m_hp = hp;
	m_st = st;
	m_ma = ma;
}


void CChampion::ParseVitalsFromText(CString block2) {
	// AA = 00 ... AP = 15
	// BA = 16 ... BP = 31
	// CA = 32 ... CP = 47
	// DA = 48 ... DP = 63  
	// EA = 64 ... EP = 79
	// FA = 80
	// GA = 96
	// HA =112
	// IA =128
	// JA =144 ... JP =159
	int luk = TupelToNumber(block2.Mid(0, 2));
	m_vitals.luk.Aktuell = luk;
	m_vitals.luk.Max = luk;
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
	//																				  HPSTST  MA    xxxxxxxxxxxxxx  FFFFNNNNPPPPWWWW           
	// AC = 02; JO = 158       2*256 + 158 = 670
	// Elija: Novice Fighter / Apprentice Priest 42/40/42/36/53/40					AADMACEEAABG	DCCKCICKCEDFCI	BBCAAAAACBECAAAA
	// Hawk: Novice Fighter / Apprentice Priest	 45/35/38/55/35/35					AAEGADFCAAAK	CICNCDCGDHCDCD	CAACAAAAADADAAAA
	// Chani: Novice Fighter / Apprentice WIzard 37/47/57/37/47/37  => 47/67/17		AACPACJOAABB	DJCFCPDJCFCPCF	BDACAAAAAAAADCDB
	// Hissa: Apprentice Fighter / Novice Ninja  58/48/35/35/43/55  => 80/61/5		AAFAACGCAAAF	CIDKDACDCDCLDH	EDAAADBAAAAAAAAA
	// Linflas: Appr. Fighter / Novice Wizard    45/47/47/35/50/35  => 65/50/12		AAEBABPEAAAM	CNCNCNCPCDDCCD	ABCEAABAABAAABCC
	// Halk: Journeyman Figher					 55/43/30/46/38/48  => 90/75/0		AAFKACOOAAAA	CIDHCLBOCOCGDA	EAEAAAAAAAAAAAAA

	// Alex: Apprentice Ninja / Novice Wizard										AADCACDKAAAN	CPCMDHCNCICDCI	AAAADCDCAAAACCBC	
	// Gando: Apprentice Ninja / Novice Wizard   39/45/47/33/48/43  => 39/63/26		AACHACHGAABK	DCCHCNCPCBDACL	AAAADACDAAAABCBC
	// Syra: Novice Priest / Apprentice WIzard   38/35/43/45/42/40	=> 53/72/15		AADFACNAAAAP	DHCGCDCLCNCKCI	AAAAAAAAADBBACDD
	// Nabi: Apprentice Priest / Novice Wizard   41/36/45/45/55/55  => 55/65/13		AADHACIKAAAN	CICJCECNCNDHDH	AAAAAAAABBECBBBB	
	// Gothmog: Journeymay Wizard													AADMACCGAABC	BOCICDDACCDCDL	AAAAAAAAAAAAEDCC

	// http://dmweb.free.fr/?q=node/691  - skills / hp gain
}

void CChampion::ParseLevelsFromText(CString block3) {
	// http://dmweb.free.fr/?q=node/199
	// AAAA => 0000; DDDD => 3333
	m_fightLevel.Club = LetterToValue(block3, 0); // todo auf EXP mappen
	m_fightLevel.Parry= LetterToValue(block3, 1);
	m_fightLevel.Swing= LetterToValue(block3, 2);
	m_fightLevel.Thrust= LetterToValue(block3, 3);

	m_ninjaLevel.Fight = LetterToValue(block3, 4); 
	m_ninjaLevel.Shoot= LetterToValue(block3, 5); 
	m_ninjaLevel.Steal= LetterToValue(block3, 6);
	m_ninjaLevel.Throw = LetterToValue(block3, 7); 

	m_priestLevel.Defend= LetterToValue(block3, 8);
	m_priestLevel.Heal = LetterToValue(block3, 9);
	m_priestLevel.Identify= LetterToValue(block3, 10);
	m_priestLevel.Influence= LetterToValue(block3, 11);

	m_wizardLevel.Air = LetterToValue(block3, 12);
	m_wizardLevel.Earth = LetterToValue(block3, 13);
	m_wizardLevel.Fire= LetterToValue(block3, 14);
	m_wizardLevel.Water = LetterToValue(block3, 15);
}


int CChampion::TupelToNumber(CString str) {
	char firstLetter = str.GetAt(0);
	char secondLetter = str.GetAt(1);
	
	return (firstLetter - 65) * 16 + (secondLetter - 65);
}

int CChampion::LetterToValue(CString word, int letter) {
	return (int)(word.GetAt(letter) - 'A');
}