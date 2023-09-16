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
	int TupelToNumber(CString str);
};
