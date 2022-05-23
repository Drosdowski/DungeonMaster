#include "stdafx.h"
#include "ItemInfos.h"
#include "Consts/ClothConst.h"
#include "Consts/WeaponConst.h"
#include <TinyXML/tinyxml.h>
#include <string>
#include <iostream>


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
		if (strcmp(parent, "item") == 0) // several existing
		{
			int index;
			CWeaponConst attribute;
			parentElement->QueryIntAttribute("index", &index);
			parentElement->QueryDoubleAttribute("weight", &attribute.weight[0]);
			parentElement->QueryIntAttribute("damage", &attribute.damage);
			parentElement->QueryIntAttribute("distance", &attribute.distance);
			parentElement->QueryIntAttribute("shootDamage", &attribute.shootDamage);

			attribute.style[0] = ParseStyle(parentElement, "attack1");
			attribute.style[1] = ParseStyle(parentElement, "attack2");
			attribute.style[2] = ParseStyle(parentElement, "attack3");

			weaponInfos[index] = attribute;
		}
		parentElement = parentElement->NextSiblingElement();
	}
}

CWeaponConst::AttackStyle CItemInfos::ParseStyle(TiXmlElement* parentElement, const char* atk) {
	std::string attack = parentElement->Attribute(atk);
	std::string attackType = attack.substr(0, attack.find('('));
	std::string attackValues = attack.substr(attack.find('(') + 1);

	CWeaponConst::AttackStyle style;
	if (attackValues != "") {
		style.dmg = std::stoi(attackValues.substr(0, 2)); // string to int!
		style.difficult = std::stoi(attackValues.substr(3, 2));
		style.useCharge = (attackValues.substr(6, 2) == "UC");
		style.type = attackType.c_str();
	}
	return style;
}


void CItemInfos::ParseClothItems(TiXmlElement* rootNode) {
	TiXmlElement* parentElement = rootNode->FirstChildElement();
	while (parentElement)
	{
		const char* parent = parentElement->Value();
		if (strcmp(parent, "item") == 0) // several existing
		{
			int index;
			CClothConst attribute;
			parentElement->QueryIntAttribute("index", &index);
			parentElement->QueryDoubleAttribute("weight", &attribute.weight[0]);
			parentElement->QueryIntAttribute("armor", &attribute.armor);
			parentElement->QueryIntAttribute("res", &attribute.res);
			// todo mehr Attribute lesen

			clothInfos[index] = attribute;
		}
		parentElement = parentElement->NextSiblingElement();
	}
}

void CItemInfos::ParseMiscellaneousItems(TiXmlElement* rootNode) {
	TiXmlElement* parentElement = rootNode->FirstChildElement();
	while (parentElement)
	{
		const char* parent = parentElement->Value();
		if (strcmp(parent, "item") == 0) // several existing
		{
			int index;
			CMiscConst attribute;			
			parentElement->QueryIntAttribute("index", &index);
			parentElement->QueryDoubleAttribute("weight", &attribute.weight[0]);
			parentElement->QueryDoubleAttribute("weight2", &attribute.weight[1]);
			parentElement->QueryDoubleAttribute("weight3", &attribute.weight[2]);
			parentElement->QueryIntAttribute("food", &attribute.food);
			parentElement->QueryIntAttribute("water", &attribute.water);
			// todo mehr Attribute lesen

			miscInfos[index] = attribute;
		}
		parentElement = parentElement->NextSiblingElement();
	}
}

