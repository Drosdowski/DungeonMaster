#include "stdafx.h"
#include "ItemInfos.h"

CItemInfos::CItemInfos() {
	LoadItemInfos();
}

CItemInfos::~CItemInfos() {

}

void CItemInfos::LoadItemInfos() {

}

void CItemInfos::ParseItems(TiXmlElement* rootNode) {}
void CItemInfos::ParseWeaponItems(TiXmlElement* rootNode) {}
void CItemInfos::ParseClothItems(TiXmlElement* rootNode) {}
void CItemInfos::ParseMiscellaneousItems(TiXmlElement* rootNode) {}
