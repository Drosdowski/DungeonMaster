#pragma once
class CItem
{
public:
	enum ItemType {
		WeaponItem,
		MiscItem,
		ClothItem
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
		
		Other = 99
	};

	virtual ItemGroup GetGroup() { return Other; };

	CItem(int index, ItemType m_itemType);

	bool IsFlying();
	bool HasMovedThisTick();
	void ResethasMoved();
	void ReduceSpeed();
	bool CheckGroup(int slotId, ItemGroup group);
	ItemType getItemType() { return m_itemType; }
	
	virtual int GetType() { return -1; };
	virtual int GetSheetForGroup() { return -1; };
	virtual int GetOffsetForGroup() { return -1; };;

	VEKTOR m_flyForce;

private:
	int m_index;
	bool m_done;
	ItemType m_itemType;
};

