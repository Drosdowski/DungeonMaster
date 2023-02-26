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
	int GetOffsetForGroup();
	ItemGroup GetGroup();

private:
	CScrollAttributes m_attribute;
};

