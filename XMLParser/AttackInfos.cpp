#include "stdafx.h"
#include "AttackInfos.h"
#include "Consts/AttackConst.h"
#include <TinyXML/tinyxml.h>


CAttackInfos::CAttackInfos() {
	LoadAttackInfos();
}
CAttackInfos::~CAttackInfos() {}


void CAttackInfos::LoadAttackInfos() {
	TiXmlDocument doc("Maps\\attack.xml");
	bool loadOkay = doc.LoadFile();

	if (!loadOkay)
	{
		printf("Could not load test file 'attack.xml'. Error='%s'. Exiting.\n", doc.ErrorDesc());
		exit(1);
	}
	TiXmlElement* rootElement = doc.FirstChildElement();
	const char* docname = rootElement->Value();
	if (strcmp(docname, "attackinfos") == 0) {

		ParseAttackInfos(rootElement);
	}
}

void CAttackInfos::ParseAttackInfos(TiXmlElement* rootNode) {
	TiXmlElement* parentElement = rootNode->FirstChildElement();
	while (parentElement)
	{
		const char* parent = parentElement->Value();
		if (strcmp(parent, "attack") == 0)
		{
			ParseAttack(parentElement);
		}

		parentElement = parentElement->NextSiblingElement();
	}
}

void CAttackInfos::ParseAttack(TiXmlElement* node) {
	TiXmlElement* parentElement = node->FirstChildElement();
	while (parentElement)
	{
		const char* parent = parentElement->Value();
		if (strcmp(parent, "attack") == 0) 
		{
			int index;
			CAttackConst attribute;
			parentElement->QueryIntAttribute("index", &index);
			CString attack = parentElement->Attribute("name");
			parentElement->QueryIntAttribute("improved", &attribute.improved);
			parentElement->QueryIntAttribute("experience", &attribute.experience);
			parentElement->QueryIntAttribute("def", &attribute.def);
			parentElement->QueryIntAttribute("stamina", &attribute.stamina);
			parentElement->QueryIntAttribute("hit", &attribute.to_hit);
			parentElement->QueryIntAttribute("damage", &attribute.damage);
			parentElement->QueryIntAttribute("fatigue", &attribute.fatigue);
			attackInfos[index] = attribute;
		}
		parentElement = parentElement->NextSiblingElement();
	}
}