#pragma once
#include "Item.h"

class CItem3DPic;
class CMiscellaneous : public CItem
{
public:
	enum MiscItemType {
		Water = 1,
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

	enum WeaponType {
		Torch = 2,
		BoltBlade = 5,
		Falchion = 9,
		Sword = 10,
		Rapier = 11,
		Sabre = 12,
		SamuraiSword = 13,
		Delta = 14,
		DiamondEdge = 15,
		Inquisitor = 17,
		Hardcleave = 19,
		Club = 23
	};

	

	int GetSheetForGroup();
	int GetOffsetForGroup();

	CMiscellaneous(int index, MiscItemType type, int subtype);
	~CMiscellaneous();

	MiscItemType GetType() {
		return m_type;
	}

	int GetSubtype() {
		return m_subtype;
	}

	void SetSubtype(int value) {
		m_subtype = value;
	}

private:
	MiscItemType m_type;
	int m_subtype;
};

