#pragma once
class CChampion
{
public:
	enum GenderType { // no more than these!
		male,
		female
	};

	CChampion(CString text);
	~CChampion() {};

	CString GetName() { return m_name; }
	VITALS GetVitals() { return m_vitals; }

private:

	CString m_name;
	CString m_subname;
	int m_pictureId;
	GenderType m_gender;
	VITALS m_vitals;

};

// Syra: Novice Priest / Apprentice WIzard   38/35/43/45/42/40	=> 53/72/15		AADFACNAAAAP	DHCGCDCLCNCKCI	AAAAAAAAADBBACDD
// Gando: Apprentice Ninja / Novica Wizard   39/45/47/33/48/43  => 39/63/26		AACHACHGAABK	DCCHCNCPCBDACL	AAAADACDAAAABCBC
// Elija: Novice Fighter / Apprentice Priest 42/40/42/36/53/40					AADMACEEAABG	DCCKCICKCEDFCI	BBCAAAAACBECAAAA
// Hissa: Apprentice Fighter / Novice Ninja  58/48/35/35/43/55  => 80/61/5		AAFAACGCAAAF	CIDKDACDCDCLDH	EDAAADBAAAAAAAAA
// Halk: Journeyman Figher					 55/43/30/46/38/48  => 90/75/0		AAFKACOOAAAA	CIDHCLBOCOCGDA	EAEAAAAAAAAAAAAA
