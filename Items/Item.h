#pragma once
class CItem
{
public:
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

	ItemGroup GetGroup(int type);

	CItem(int index);

	bool IsFlying();
	bool HasMovedThisTick();
	void ResethasMoved();
	void ReduceSpeed();
	bool CheckGroup(int slotId, int type);

	VEKTOR m_flyForce;

private:
	int m_index;
	bool m_done;

};

