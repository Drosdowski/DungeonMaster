#pragma once
class CBasePictures
{
public:

	CBasePictures(CDC* pDC);
	~CBasePictures() {};

	CDC* GetMyDC() { return m_pDC; }

	void LoadPic(CBitmap*& mPic, int ID);
	void LoadPicAndFlip(CDC* pDC, CBitmap*& mPic, int ID);


private:
	CDC* m_pDC;

};

