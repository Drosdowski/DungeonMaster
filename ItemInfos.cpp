#include "stdafx.h"
#include "ItemInfos.h"
#include "Consts/ClothConst.h"
#include "Consts/WeaponConst.h"
#include <TinyXML/tinyxml.h>
#include <string>

CItemInfos::CItemInfos() {
	LoadItemInfos();
}

CItemInfos::~CItemInfos() {

}

void CItemInfos::LoadItemInfos() {
	TiXmlDocument doc("Maps\\items.xml");
	bool loadOkay = doc.LoadFile();

	if (!loadOkay)
	{
		printf("Could not load test file 'items.xml'. Error='%s'. Exiting.\n", doc.ErrorDesc());
		exit(1);
	}
	TiXmlElement* rootElement = doc.FirstChildElement();
	const char* docname = rootElement->Value();
	if (strcmp(docname, "items") == 0) {

		ParseItems(rootElement);
	}

}

void CItemInfos::ParseItems(TiXmlElement* rootNode) {
	TiXmlElement* parentElement = rootNode->FirstChildElement();
	while (parentElement)
	{
		const char* parent = parentElement->Value();
		if (strcmp(parent, "weapons") == 0)
		{
			ParseWeaponItems(parentElement);
		}
		else if (strcmp(parent, "clothes") == 0)
		{
			ParseClothItems(parentElement);
		}
		else if (strcmp(parent, "miscellaneous") == 0)
		{
			ParseMiscellaneousItems(parentElement);
		}

		parentElement = parentElement->NextSiblingElement();
	}
}

void CItemInfos::ParseWeaponItems(TiXmlElement* rootNode) {
	TiXmlElement* parentElement = rootNode->FirstChildElement();
	while (parentElement)
	{
		const char* parent = parentElement->Value();
		if (strcmp(parent, "items") == 0) // several existing
		{
			int index;
			CWeaponConst attribute;
			parentElement->QueryIntAttribute("index", &index);
			parentElement->QueryDoubleAttribute("weight", &attribute.weight);
			parentElement->QueryIntAttribute("damage", &attribute.damage);
			parentElement->QueryIntAttribute("distance", &attribute.distance);
			parentElement->QueryIntAttribute("shootDamage", &attribute.shootDamage);

			std::string attack = parentElement->Attribute("attack1");
			std::string attackType = attack.substr(0, attack.find('('));

			weaponInfos[index] = attribute;
		}
		parentElement = parentElement->NextSiblingElement();
	}
}

void CItemInfos::ParseClothItems(TiXmlElement* rootNode) {
	TiXmlElement* parentElement = rootNode->FirstChildElement();
	while (parentElement)
	{
		const char* parent = parentElement->Value();
		if (strcmp(parent, "items") == 0) // several existing
		{
			int index;
			CClothConst attribute;
			parentElement->QueryIntAttribute("index", &index);
			parentElement->QueryDoubleAttribute("weight", &attribute.weight);
			parentElement->QueryIntAttribute("armor", &attribute.armor);
			parentElement->QueryIntAttribute("res", &attribute.res);

			clothInfos[index] = attribute;
		}
		parentElement = parentElement->NextSiblingElement();
	}
}

void CItemInfos::ParseMiscellaneousItems(TiXmlElement* rootNode) {}
