#pragma once
class CPictures;
class CGrpHeld;
class CBackpackView
{
public:
	CBackpackView();
	virtual ~CBackpackView();

	void UpdateRucksack(CDC* pDC, CPictures* pPictures, CGrpHeld* grpHero);
};

