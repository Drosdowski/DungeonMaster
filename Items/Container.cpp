#include "stdafx.h"
#include "Container.h"

CContainer::CContainer(int index, CContainerAttributes attributes) : CItem(index, ContainerItem) {
	m_attribute = attributes;
}

CContainer::~CContainer() {

}

void CContainer::SetOpen(bool value) {
	m_attribute.open = value;
}

int CContainer::GetOffsetForGroup() {
	if (m_attribute.open) {
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