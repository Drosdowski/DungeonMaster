#include "stdafx.h"
#include "MonsterInfos.h"
#include "Consts/MonsterConst.h"
#include <TinyXML/tinyxml.h>

CMonsterInfos::CMonsterInfos() {
	LoadMonsterInfos();
}

CMonsterInfos::~CMonsterInfos() {}

void CMonsterInfos::LoadMonsterInfos() {
	TiXmlDocument doc("Maps\\monster.xml");
	bool loadOkay = doc.LoadFile();

	if (!loadOkay)
	{
		printf("Could not load test file 'monster.xml'. Error='%s'. Exiting.\n", doc.ErrorDesc());
		exit(1);
	}
	TiXmlElement* rootElement = doc.FirstChildElement();
	const char* docname = rootElement->Value();
	if (strcmp(docname, "monsters") == 0) {

		ParseMonsterInfos(rootElement);
	}
}

void CMonsterInfos::ParseMonsterInfos(TiXmlElement* rootNode) {
	TiXmlElement* parentElement = rootNode->FirstChildElement();
	while (parentElement)
	{
		const char* parent = parentElement->Value();
		if (strcmp(parent, "monster") == 0)
		{
			ParseMonster(parentElement);
		}

		parentElement = parentElement->NextSiblingElement();
	}
}

void CMonsterInfos::ParseMonster(TiXmlElement* element) {
	int type, help;
	CMonsterConst attribute;
	element->QueryIntAttribute("type", &type);
	element->QueryIntAttribute("size", &attribute.size);
	element->QueryIntAttribute("side_attack", &help);
	attribute.side_attack = (help == 1);
	element->QueryIntAttribute("attack_anyone", &help);
	attribute.attack_anyone = (help == 1);
	element->QueryIntAttribute("levitate", &help);
	attribute.levitate = (help == 1);
	element->QueryIntAttribute("non_material", &help);
	attribute.non_material = (help == 1);
	element->QueryIntAttribute("height", &attribute.height);
	element->QueryIntAttribute("mirror_front", &help);
	attribute.mirror_front = (help == 1);
	element->QueryIntAttribute("mirror_front_dist", &attribute.mirror_front_dist);
	element->QueryIntAttribute("move_dur", &attribute.move_dur);
	element->QueryIntAttribute("attack_dur", &attribute.attack_dur);
	element->QueryIntAttribute("armor", &attribute.armor);
	element->QueryIntAttribute("attack_power", &attribute.attack_power);
	element->QueryIntAttribute("poison", &attribute.poison);
	element->QueryIntAttribute("defense", &attribute.defense);
	element->QueryIntAttribute("spell_casting_range", &attribute.spell_casting_range);
	element->QueryIntAttribute("fire_res", &attribute.fire_res);
	element->QueryIntAttribute("poison_res", &attribute.poison_res);
	m_pMonsterInfos[type] = attribute;

}
