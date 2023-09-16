#include "stdafx.h"
#include "Champion.h"


void CChampion::ParseVitalsFromText() {
	// AA = 00 ... AP = 15
	// BA = 16 ... BP = 31
	// CA = 32 ... CP = 47
	// DA = 48 ... DP = 63  
	// 
	CString block2 = "DHCGCDCLCNCKCI";
	int str = TupelToNumber(block2.Mid(2, 2));
	vitals.str.Aktuell = str;
	vitals.str.Max = str;
	int dex = TupelToNumber(block2.Mid(4, 2));
	vitals.dex.Aktuell = dex;
	vitals.dex.Max = dex;
	int vit = TupelToNumber(block2.Mid(6, 2));
	vitals.vit.Aktuell = vit;
	vitals.vit.Max = vit;
	int wis = TupelToNumber(block2.Mid(8, 2));
	vitals.wis.Aktuell = wis;
	vitals.wis.Max = wis;
	int af = TupelToNumber(block2.Mid(10, 2));
	vitals.af.Aktuell = af;
	vitals.af.Max = af;
	int am = TupelToNumber(block2.Mid(12, 2));
	vitals.am.Aktuell = am;
	vitals.am.Max = am;


	//																								  xxxxxxxxxxxx                           
	// Syra: Novice Priest / Apprentice WIzard   38/35/43/45/42/40	=> 53/72/15		AADFACNAAAAP	DHCGCDCLCNCKCI	AAAAAAAAADBBACDD
	// Chani: Novice Fighter / Apprentice WIzard 37/47/57/37/47/37  => 47/67/17		AACPACJOAABB	DJCFCPDJCFCPCF	BDACAAAAAAAADCDB
	// Elija: Novice Fighter / Apprentice Priest 42/40/42/36/53/40					AADMACEEAABG	DCCKCICKCEDFCI	BBCAAAAACBECAAAA
	// Gando: Apprentice Ninja / Novice Wizard   39/45/47/33/48/43  => 39/63/26		AACHACHGAABK	DCCHCNCPCBDACL	AAAADACDAAAABCBC
	// Hissa: Apprentice Fighter / Novice Ninja  58/48/35/35/43/55  => 80/61/5		AAFAACGCAAAF	CIDKDACDCDCLDH	EDAAADBAAAAAAAAA
	// Halk: Journeyman Figher					 55/43/30/46/38/48  => 90/75/0		AAFKACOOAAAA	CIDHCLBOCOCGDA	EAEAAAAAAAAAAAAA
}

int CChampion::TupelToNumber(CString str) {
	char firstLetter = str.GetAt(0);
	char secondLetter = str.GetAt(1);
	
	return (firstLetter - 65) * 16 + (secondLetter - 65);
}
