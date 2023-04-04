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
	double GetWeight();

	void SetSubitems(CItem* items, int index) { m_subItems[index] = items; }
	CItem* GetSubItem(int index) { return m_subItems[index]; }

private:
	CContainerAttributes m_attribute;
};

