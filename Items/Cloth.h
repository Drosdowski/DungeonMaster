#pragma once
#include "Item.h"
#include <Attributes/ClothAttributes.h>

class CCloth : public CItem
{
public:
	CCloth(int index, CClothAttributes attribute);
	~CCloth();

private:
	CClothAttributes m_attribute;
};

