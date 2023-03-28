#pragma once
#include "Item.h"
#include <Attributes/ScrollAttributes.h>

class CScroll : public CItem
{
public:
	CScroll(int index, CScrollAttributes* attribute);
	~CScroll();

	const char* GetText();

	int GetSheetForGroup();
	int GetOffsetForGroup();
	ItemGroup GetGroup();
	bool IsOpen() { return m_attribute->open; }
	void SetOpen(bool value);
	double GetWeight() { return 0.1; }

private:
	CScrollAttributes* m_attribute;
};

