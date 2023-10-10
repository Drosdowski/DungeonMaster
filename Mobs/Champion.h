#pragma once
class CChampion
{
public:
	enum GenderType { // no more than these!
		male,
		female
	};

	CChampion(CString text);
	CChampion(const char* name, const char* subname, bool male, VITALS vitals, int hp, int st, int ma);
	~CChampion() {};

	CString GetName() { return m_name; }
	VITALS GetVitals() { return m_vitals; }
	bool IsMale() { return m_gender == GenderType::male; }
	int hp() { return m_hp; }
	int st() { return m_st; }
	int ma() { return m_ma; }
	FIGHT_SKILLS fightLevel() { return m_fightLevel; };
	NINJA_SKILLS ninjaLevel() { return m_ninjaLevel; };
	PRIEST_SKILLS priestLevel() { return m_priestLevel; };
	WIZARD_SKILLS wizardLevel() { return m_wizardLevel; };

private:

	CString m_name;
	CString m_subname;
	GenderType m_gender;
	VITALS m_vitals;
	int m_hp, m_st, m_ma;
	FIGHT_SKILLS m_fightLevel;
	NINJA_SKILLS m_ninjaLevel;
	PRIEST_SKILLS m_priestLevel;
	WIZARD_SKILLS m_wizardLevel;

	void ParseVitalsFromText(CString block2);
	void ParseLevelsFromText(CString block3);
	int TupelToNumber(CString str);
	int LetterToValue(CString word, int letter);
};
