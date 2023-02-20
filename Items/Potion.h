#pragma once
#include "Item.h"
#include <Attributes/PotionAttributes.h>
class CPotion : public CItem
{
public:
	CPotion(int index, CPotionAttributes attribute);
	~CPotion();

	double GetWeight() { return 0.1; }

	int GetSheetForGroup();
	int GetOffsetForGroup();
	ItemGroup GetGroup();

private:
	CPotionAttributes m_attribute;
};

