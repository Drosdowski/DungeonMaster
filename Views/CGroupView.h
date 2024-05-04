#pragma once
class CPictures;
class CGrpHeld;
class CHeld;
class CGroupView
{
public:

	CGroupView(CPictures* pPictures);
	virtual ~CGroupView();

	void DrawGroup(CDC* pDC, DMMode iModus, CGrpHeld* pGrpHeld);
private:
	void DrawBones(int index);
	void DrawValues(CHeld* pHeld);
	void DrawName(bool aktiv, int index, CString strName);
	void DrawHands(CHeld* pHeld);
	void DrawPicture(bool aktiv, int index, int heroId);
	void DrawDamage(int index, bool bigDmg, int dmg);

	CDC* m_pDC;
	CPictures* m_pPictures;

	char* m_textBuffer;
};

