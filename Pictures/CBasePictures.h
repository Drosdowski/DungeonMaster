#pragma once
class CBasePictures
{
public:

	CBasePictures(CDC* pDC);
	~CBasePictures() {};

	CDC* GetMyDC() { return m_pDC; }

	void LoadPic(CBitmap*& mPic, int ID);
	void LoadPicAndScale(CBitmap*& mPic, int ID, bool maximum);
	void LoadPicAndFlip(CBitmap*& mPic, int ID);


protected:
	CDC* m_pDC;

};

