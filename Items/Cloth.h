#pragma once
#include "Item.h"
#include <Attributes/ClothAttributes.h>

class CCloth : public CItem
{
public:

	CCloth(int index, CClothAttributes attribute);
	~CCloth();

	CClothAttributes::ClothType GetType() { return m_attribute.type; }

	int GetSheetForGroup();
	int GetOffsetForGroup();
	ItemGroup GetGroup();
	double GetWeight();
	int GetArmourClass();

private:
	CClothAttributes m_attribute;
};

