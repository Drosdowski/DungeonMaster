#pragma once
class CScreenCoords
{
public:
	CScreenCoords();

	enum ArrowArea {
		None = 0,
		LeftTurn = 1,
		Vorward = 2,
		RightTurn = 3,
		LeftStrafe = 4,
		Backwards = 5,
		RightStrafe = 6		
	};

	static int CheckHitArrows(CPoint point);
	static int CheckHitActiveWizard(CPoint point, int activeWizardID);
	static int CheckHitAction(CPoint point, int phase);
	static int CheckHitHeroes(CPoint point);
	static bool CheckHitDeco(CPoint point);
	static bool CheckHitMainScr(CPoint);
	static bool CheckHitEye(CPoint);
	static bool CheckHitMouth(CPoint);
	static SUBPOS CheckHitFloor(CPoint point);
	static SUBPOS CheckHitAir(CPoint point); // throwing
};

