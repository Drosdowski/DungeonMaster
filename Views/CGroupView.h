#pragma once
class CPictures;
class CGrpHeld;
class CHeld;
class CGroupView
{
public:

	CGroupView(CPictures* pPictures);
	virtual ~CGroupView();

	void GroupZeichnen(CDC* pDC, DMMode iModus, CGrpHeld* pGrpHeld);
private:
	void KnochenZeichnen(int index);
	void WerteZeichnen(CHeld* pHeld);
	void NameZeichnen(bool aktiv, int index, CString strName);
	void HaendeZeichnen(CHeld* pHeld);
	void BildZeichnen(bool aktiv, int index);
	void SchadenZeichnen(int index, bool bigDmg, int dmg);

	CDC* m_pDC;
	CPictures* m_pPictures;

	char* m_textBuffer;
};

