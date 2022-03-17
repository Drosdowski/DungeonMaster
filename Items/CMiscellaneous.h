#pragma once
class CMiscellaneous
{
public:
	CMiscellaneous(int index, int type, int subtype);
	~CMiscellaneous();

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
		Food = 2,
		Other = 3
	};

	ItemType GetType() {
		return (ItemType)m_type;
	}

	ItemGroup GetGroup() {
		if (m_type >= 9 && m_type <= 24) return ItemGroup::Key;
		if (m_type >= 29 && m_type <= 31) return ItemGroup::Food;
		return ItemGroup::Other;
	}

	bool IsFlying();
	bool HasMovedThisTick();
	void ResethasMoved();
	void ReduceSpeed();

	
	VEKTOR m_flyForce;

private:
	int m_index;
	int m_type;
	int m_subtype;
	bool m_done;
};

