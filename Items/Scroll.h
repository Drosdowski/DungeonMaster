#pragma once
#include "Item.h"
#include <Attributes/ScrollAttributes.h>

class CScroll : public CItem
{
public:
	CScroll(int index, CScrollAttributes attribute);
	~CScroll();

	const char* GetText();

	int GetSheetForGroup();
	int GetOffsetForGroup(bool active);
	ItemGroup GetGroup();
	bool IsOpen() { return m_attribute.open; }
	void SetOpen(bool value);
	double GetWeight() { return 0.1; }
	CString GetName();

private:
	CScrollAttributes m_attribute;
};

