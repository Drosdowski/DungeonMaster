#pragma once
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

};

