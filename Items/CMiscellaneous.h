#pragma once
class CItem3DPic;
class CMiscellaneous
{
public:
	enum ItemType {
		IronKey = 9, 
		KeyOfB = 10, 
		SolidKey = 11, 
		SquareKey = 12,
		TurquoiseKey = 13,
		CrossKey = 14, 
		SkeletonKey = 16,
		GoldKey = 17, 
		WingedKey = 18,
		TopazKey = 19, 
		EmeraldKey = 21,
		RubyKey = 22, 
		RaKey = 23,
		MasterKey = 24,
		Apple = 29,
		Bread = 31
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

	int GetSheetForGroup();
	int GetOffsetForGroup();

	CMiscellaneous(int index, ItemType type, int subtype);
	~CMiscellaneous();

	ItemType GetType() {
		return m_type;
	}

	int GetSubtype() {
		return m_subtype;
	}

	ItemGroup GetGroup() {
		if (m_type >= 9 && m_type <= 24) return ItemGroup::Key;
		if (m_type >= 29 && m_type <= 31) return ItemGroup::Consumable;
		return ItemGroup::Other;
	}

	bool IsFlying();
	bool HasMovedThisTick();
	void ResethasMoved();
	void ReduceSpeed();
	bool CheckGroup(int slotId);

	CBitmap* GetPicByType(CItem3DPic* p3DPics);
		
	VEKTOR m_flyForce;

private:
	int m_index;
	ItemType m_type;
	int m_subtype;
	bool m_done;
};

