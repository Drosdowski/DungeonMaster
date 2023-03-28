#include "stdafx.h"
#include "Container.h"

CContainer::CContainer(int index, CContainerAttributes* attributes) : CItem(index, ContainerItem) {
	m_attribute = attributes;
	for (int i = 0; i < 8; i++) {
		subItems[i] = NULL;
	}
}

CContainer::~CContainer() {
	delete m_attribute;
	for (int i = 0; i < 8; i++) {
		if (subItems[i])
			delete subItems[i];
	}
}

void CContainer::SetOpen(bool value) {
	m_attribute->open = value;
}

int CContainer::GetOffsetForGroup() {
	if (m_attribute->open) {
		return 17;
	}
	else {
		return 16;
	}
}

int CContainer::GetSheetForGroup() {
	return 4;

}

CItem::ItemGroup CContainer::GetGroup() {
	return Container;
}