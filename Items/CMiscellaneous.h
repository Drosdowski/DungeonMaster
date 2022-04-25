#pragma once
#include "Item.h"
#include <Attributes\MiscellaneousAttributes.h>

class CItem3DPic;
class CMiscellaneous : public CItem
{
public:

	int GetSheetForGroup();
	int GetOffsetForGroup();
	ItemGroup GetGroup();

	CMiscellaneous(int index, CMiscellaneousAttributes att);
	~CMiscellaneous();

	int GetType() { return m_attributes.type; };

	int GetSubtype() {
		return m_attributes.subtype;
	}

	void SetSubtype(int value) {
		m_attributes.subtype = value;
	}

private:
	CMiscellaneousAttributes m_attributes;
};

