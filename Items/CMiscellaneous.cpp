#include "stdafx.h"
#include "CMiscellaneous.h"
#include "..\Pictures\Items3D\CItem3DPic.h"
#include <cassert>

CMiscellaneous::CMiscellaneous(int index, ItemType type, int subtype) {
	m_index = index;
	m_type = type;
	m_subtype = subtype;
	m_flyForce = VEKTOR{ 0,0,0 };
	m_done = false;
}

CMiscellaneous::~CMiscellaneous() {

}

bool CMiscellaneous::IsFlying()
{
	return (m_flyForce.x != 0 || m_flyForce.y != 0);
}

void CMiscellaneous::ReduceSpeed() {
	if (m_flyForce.x > 0) m_flyForce.x--;
	if (m_flyForce.y > 0) m_flyForce.y--;
	if (m_flyForce.x < 0) m_flyForce.x++;
	if (m_flyForce.y < 0) m_flyForce.y++;
	m_done = true;
}

bool CMiscellaneous::HasMovedThisTick() {
	return m_done;
}

void CMiscellaneous::ResethasMoved() {
	m_done = false;
}

// todo abrüsten, es muss das 2D BIld verwendet werden !
CBitmap* CMiscellaneous::GetPicByType(CItem3DPic* p3DPics) {

	CBitmap* bmp;
	if (m_type == CMiscellaneous::ItemType::Apple)
		bmp = p3DPics->GetApple();
	else if (m_type == CMiscellaneous::ItemType::Bread)
		bmp = p3DPics->GetBread();
	else if (m_type == CMiscellaneous::ItemType::IronKey ||
		m_type == CMiscellaneous::ItemType::KeyOfB ||
		m_type == CMiscellaneous::ItemType::SolidKey ||
		m_type == CMiscellaneous::ItemType::SquareKey ||
		m_type == CMiscellaneous::ItemType::TurquoiseKey ||
		m_type == CMiscellaneous::ItemType::CrossKey ||
		m_type == CMiscellaneous::ItemType::SkeletonKey)
		bmp = p3DPics->GetIronKey();
	else if (m_type == CMiscellaneous::ItemType::GoldKey ||
		m_type == CMiscellaneous::ItemType::WingedKey ||
		m_type == CMiscellaneous::ItemType::TopazKey ||
		m_type == CMiscellaneous::ItemType::EmeraldKey ||
		m_type == CMiscellaneous::ItemType::RubyKey ||
		m_type == CMiscellaneous::ItemType::RaKey ||
		m_type == CMiscellaneous::ItemType::MasterKey)
		bmp = p3DPics->GetGoldKey();
	else
		return NULL; // Item noch nicht da
}

int CMiscellaneous::GetOffsetForGroup() {
	ItemGroup group = GetGroup();
	switch (group) {
	case Key:
		return 16 - IronKey + m_type;
	case Consumable:
		return 8 - Apple + m_type;
	case Other:
		assert(false); // todo !!
	}
}

int CMiscellaneous::GetSheetForGroup() {
	ItemGroup group = GetGroup();
	switch (group) {
	case Key:
		return 5;
	case Consumable:
		return 5;
	case Other:
		assert(false); // todo !!
	}
}

bool CheckGroup(int slotId) {
	//if (slotId == 2) return (GetGroup() == ItemGroup.Helmet);
	return true;
}
