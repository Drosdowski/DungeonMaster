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
		ScrollItem,
		ContainerItem
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
		Climb = 15,

		Other = 99
	};

	virtual ItemGroup GetGroup() { return Other; };

	CItem(int index, ItemType m_itemType);
	
	bool CheckGroup(int slotId, ItemGroup group);
	ItemType getItemType() { return m_itemType; }
	char* getItemTypeString();
	int GetIndex() { return m_index; }

	virtual int GetSheetForGroup() { return -1; }
	virtual int GetOffsetForGroup(bool active) { return -1; }
	virtual double GetWeight() { return -1; }
	virtual CString GetName() { return ""; }
	virtual int GetArmourClass() { return 0; }

	void ClearSubitems(int index) { m_subItems[index] = NULL; }

protected:
	CItem* m_subItems[8];

private:
	int m_index;
	ItemType m_itemType;



};

