#pragma once
#include "Item.h"
#include <Attributes/ContainerAttributes.h>

class CContainer : public CItem
{
public:
	CContainer(int index, CContainerAttributes attribute);
	~CContainer();

	int GetSheetForGroup();
	int GetOffsetForGroup();
	ItemGroup GetGroup();
	bool IsOpen() { return m_attribute.open; }
	void SetOpen(bool value);
	double GetWeight() { return 0.1; }

private:
	CContainerAttributes m_attribute;
};

