#pragma once
#include "Item.h"
#include <Attributes/ClothAttributes.h>

class CCloth : public CItem
{
public:

	CCloth(int index, CClothAttributes attribute);
	~CCloth();

	int GetType() { return m_attribute.type; }

	int GetSheetForGroup();
	int GetOffsetForGroup();
	ItemGroup GetGroup();


private:
	CClothAttributes m_attribute;
};

