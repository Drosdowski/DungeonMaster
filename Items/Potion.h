#pragma once
#include "Item.h"
#include <Attributes/PotionAttributes.h>
class CPotion : public CItem
{
public:
	CPotion(int index, CPotionAttributes attribute);
	~CPotion();

	int GetType() { return m_attribute.type; }

	double GetWeight() { return 0.1; }

	int GetSheetForGroup();
	int GetOffsetForGroup();
	ItemGroup GetGroup();

private:
	CPotionAttributes m_attribute;
};

