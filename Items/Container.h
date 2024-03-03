#pragma once
#include "Item.h"
#include <Attributes/ContainerAttributes.h>

class CContainer : public CItem
{
public:
	CContainer(int index, CContainerAttributes attribute);
	~CContainer();

	int GetSheetForGroup();
	int GetOffsetForGroup(bool active);
	ItemGroup GetGroup();
	bool IsOpen() { return m_attribute.open; }
	void SetOpen(bool value);
	double GetWeight();
	CString GetName();

	void SetSubitems(CItem* items, int index) { m_subItems[index] = items; }
	CItem* GetSubItem(int index) { return m_subItems[index]; }

	CItem* GetItemCarrying(int index) { return m_subItems[index]; }
	void RemoveItemCarrying(int index) { m_subItems[index] = NULL; }
	CItem* SwitchItemAt(int index, CItem* item);

private:
	CContainerAttributes m_attribute;
};

