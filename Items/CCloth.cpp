#include "stdafx.h"
#include "Cloth.h"

CCloth::CCloth(int index, CClothAttributes attribute) : CItem(index, ClothItem) {
	m_attribute = attribute;
}

CCloth::~CCloth() {

}