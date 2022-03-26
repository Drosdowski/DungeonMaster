#include "stdafx.h"
#include "CMiscellaneous.h"
#include "..\Pictures\Items3D\CItem3DPic.h"

CMiscellaneous::CMiscellaneous(int index, int type, int subtype) {
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

CBitmap* CMiscellaneous::GetPicByType(CItem3DPic* p3DPics) {

	CBitmap* bmp;
	if (GetType() == CMiscellaneous::ItemType::Apple)
		bmp = p3DPics->GetApple();
	else if (GetType() == CMiscellaneous::ItemType::Bread)
		bmp = p3DPics->GetBread();
	else if (GetType() == CMiscellaneous::ItemType::IronKey ||
		GetType() == CMiscellaneous::ItemType::KeyOfB ||
		GetType() == CMiscellaneous::ItemType::SolidKey ||
		GetType() == CMiscellaneous::ItemType::SquareKey ||
		GetType() == CMiscellaneous::ItemType::TurquoiseKey ||
		GetType() == CMiscellaneous::ItemType::CrossKey ||
		GetType() == CMiscellaneous::ItemType::SkeletonKey)
		bmp = p3DPics->GetIronKey();
	else if (GetType() == CMiscellaneous::ItemType::GoldKey ||
		GetType() == CMiscellaneous::ItemType::WingedKey ||
		GetType() == CMiscellaneous::ItemType::TopazKey ||
		GetType() == CMiscellaneous::ItemType::EmeraldKey ||
		GetType() == CMiscellaneous::ItemType::RubyKey ||
		GetType() == CMiscellaneous::ItemType::RaKey ||
		GetType() == CMiscellaneous::ItemType::MasterKey)
		bmp = p3DPics->GetGoldKey();
	else
		return NULL; // Item noch nicht da
}
