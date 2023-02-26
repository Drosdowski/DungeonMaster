#pragma once
#include "MovingObject.h"
class CItem : public CMovingObject
{
public:
	enum ItemType {
		WeaponItem,
		MiscItem,
		ClothItem,
		PotionItem,
		ScrollItem
	};
	enum ItemGroup {
		Key = 1,
		Consumable = 2,
		Helmet = 3,
		Amulet = 4,
		Torso = 5,
		Legs = 6,
		Shoes = 7,
		Weapon = 8,
		Shield = 9,
		Container = 10,
		Quiver = 11,
		Throwable = 12,
		Flask = 13,
		Scroll = 14,

		Other = 99
	};

	virtual ItemGroup GetGroup() { return Other; };

	CItem(int index, ItemType m_itemType);
	
	bool CheckGroup(int slotId, ItemGroup group);
	ItemType getItemType() { return m_itemType; }
	int GetIndex() { return m_index; }

	virtual int GetType() { return -1; }
	virtual int GetSheetForGroup() { return -1; }
	virtual int GetOffsetForGroup() { return -1; }
	virtual double GetWeight() { return -1; }
	virtual int GetArmourClass() { return 0; }

private:
	int m_index;
	ItemType m_itemType;
};

