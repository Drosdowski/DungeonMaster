#pragma once
class CMiscellaneous
{
public:
	CMiscellaneous(int index, int type, int subtype);
	~CMiscellaneous();

	enum ItemType {
		Apple = 29,
		Bread = 31
	};

	ItemType GetType() {
		return (ItemType)m_type;
	}
	

private:
	int m_index;
	int m_type;
	int m_subtype;
};

