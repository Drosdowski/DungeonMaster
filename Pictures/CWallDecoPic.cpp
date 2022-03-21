#include "stdafx.h"
#include "..\resource.h"
#include "CWallDecoPic.h"
#include <set>

CWallDecoPic::CWallDecoPic(CDC* pDC) : CBasePictures(pDC)
{
	InitPics();
}

CWallDecoPic:: ~CWallDecoPic() {
	for (int gullideckel = 0; gullideckel < maxAnz; gullideckel++) {
		if (m_pDecoFront[gullideckel]) {
			delete m_pDecoFront[gullideckel];
			delete m_pDecoLeft[gullideckel];
			delete m_pDecoRight[gullideckel];
		}
	}
}

CBitmap* CWallDecoPic::GetPicFront(WallDecorationType index) {
	return m_pDecoFront[index];
}

CBitmap* CWallDecoPic::GetPicSide(WallDecorationType  index, bool left) {
	if (left)
		return m_pDecoLeft[index];
	else
		return m_pDecoRight[index];
}


void CWallDecoPic::InitPics() {
	std::set<int> listOfPics {5, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 35, 36, 44, 45};
	for (int index = 0; index < maxAnz; index++) {
		
		if (listOfPics.find(index) != listOfPics.end()) {
			LoadPic(m_pDecoFront[index], 2000 + index);
			LoadPic(m_pDecoLeft[index], 2100 + index);
			LoadPicAndFlip(m_pDecoRight[index], 2100 + index);
		}
		else {
			m_pDecoFront[index] = NULL;
			m_pDecoLeft[index] = NULL;
			m_pDecoRight[index] = NULL;
		}
	}

}