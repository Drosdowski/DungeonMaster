#pragma once
class CMovingObject
{
public:
	CMovingObject();
	~CMovingObject();

	bool HasMovedThisTick();
	void ResethasMoved();
	void ReduceSpeed(); // range energy & damage enery
	void SetDone() { m_done = true ; }
	void Stop() { m_flyForce.x = 0; m_flyForce.y = 0; m_done = true; }

	COMPASS_DIRECTION GetDirection();
	void SetDirection(COMPASS_DIRECTION direction);

	bool IsFlying(); 

	VEKTOR m_flyForce;

private:
	bool m_done;
	

};

