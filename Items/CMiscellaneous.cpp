#include "stdafx.h"
#include "CMiscellaneous.h"


CMiscellaneous::CMiscellaneous(int index, int type, int subtype) {
	m_index = index;
	m_type = type;
	m_subtype = subtype;
	inAir = false;
}

CMiscellaneous::~CMiscellaneous() {

}
