#include "stdafx.h"
#include "CLockPic.h"

CLockPic::CLockPic(CDC* pDC) : CBasePictures(pDC)
{
	InitPics();
}

CLockPic:: ~CLockPic() {
}

CBitmap* CLockPic::GetLockFront(int index) {
	return NULL;
}

CBitmap* CLockPic::GetLockSide(int index, bool left) {
	return NULL;
}


void CLockPic::InitPics() {

}