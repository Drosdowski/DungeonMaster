#pragma once
class CChampion
{
	enum GenderType { // no more than these!
		male,
		female
	};

	CString name;
	CString subname;
	int pictureId;
	GenderType gender;
	VITALS vitals;
private:
	void ParseVitalsFromText(CString block2);
	void ParseLevelsFromText(CString block3);
	int TupelToNumber(CString str);
};
