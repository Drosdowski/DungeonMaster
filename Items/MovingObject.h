#pragma once
class CMovingObject
{
public:
	CMovingObject();

	bool HasMovedThisTick();
	void ResethasMoved();
	void ReduceSpeed(); // range energy & damage enery

	bool IsFlying(); 

	VEKTOR m_flyForce;

private:
	bool m_done;
	

};

