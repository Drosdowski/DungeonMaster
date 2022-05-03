#pragma once
#include "Consts/WeaponConst.h";
#include "Consts/ClothConst.h";
#include "Consts/MiscConst.h";

class TiXmlElement;
class CItemInfos
{
public:
	CItemInfos();
	~CItemInfos();

	CWeaponConst GetWeaponInfo(int index) { return weaponInfos[index]; }
	CClothConst GetClothInfo(int index) { return clothInfos[index]; }
	CMiscConst GetMiscInfo(int index) { return miscInfos[index]; }

private:
	void LoadItemInfos();
	
	void ParseItems(TiXmlElement* rootNode);
	void ParseWeaponItems(TiXmlElement* rootNode);
	void ParseClothItems(TiXmlElement* rootNode);
	void ParseMiscellaneousItems(TiXmlElement* rootNode);

	CWeaponConst weaponInfos[46];
	CClothConst clothInfos[58];
	CMiscConst miscInfos[56];
};

