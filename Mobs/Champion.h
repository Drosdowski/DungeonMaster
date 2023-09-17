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

	void ParseVitalsFromText(CString block2);
	void ParseLevelsFromText(CString block3);
	int TupelToNumber(CString str);
};
