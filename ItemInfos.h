#pragma once
#include "Consts/WeaponConst.h";
#include "Consts/ClothConst.h";

class TiXmlElement;
class CItemInfos
{
	CItemInfos();
	~CItemInfos();


private:
	void LoadItemInfos();
	
	void ParseItems(TiXmlElement* rootNode);
	void ParseWeaponItems(TiXmlElement* rootNode);
	void ParseClothItems(TiXmlElement* rootNode);
	void ParseMiscellaneousItems(TiXmlElement* rootNode);

	CWeaponConst weaponInfos[46];
	CClothConst clothInfos[58];
};

