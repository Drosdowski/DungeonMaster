#pragma once
class CPictures;
class CGrpHeld;
class CGroupView
{
public:
	CGroupView();           
	virtual ~CGroupView();

	void Zeichnen(CDC* pDC, CPictures* pPictures, int iModus, CGrpHeld* pGrpHeld);

};

