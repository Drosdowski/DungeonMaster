#pragma once
class CChampion
{
public:
	enum GenderType { // no more than these!
		male,
		female
	};

	CChampion(CString text);
	CChampion(const char* name, const char* subname, bool male, VITALS vitals);
	~CChampion() {};

	CString GetName() { return m_name; }
	VITALS GetVitals() { return m_vitals; }
	bool IsMale() { return m_gender == GenderType::male; }

private:

	CString m_name;
	CString m_subname;
	GenderType m_gender;
	VITALS m_vitals;

	void ParseVitalsFromText(CString block2);
	void ParseLevelsFromText(CString block3);
	int TupelToNumber(CString str);
};
