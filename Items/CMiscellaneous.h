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

	CMiscellaneousAttributes::MiscItemType GetType() { return m_attribute.type; };
	double GetWeight();
	CString GetName();

	int GetSubtype() {
		return m_attribute.subtype;
	}

	void SetSubtype(int value) {
		m_attribute.subtype = value;
	}

private:
	CMiscellaneousAttributes m_attribute;
};

