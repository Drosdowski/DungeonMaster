#pragma once
class CScreenCoords
{
public:
	CScreenCoords();

	static int CheckHitArrows(CPoint point);
	static int CheckHitActiveWizard(CPoint point, int activeWizardID);
	static int CheckHitRunes(CPoint point);
	static bool CheckHitSpell(CPoint point);
	static bool CheckHitUndoRune(CPoint point);
	static int CheckHitAction(CPoint point, int phase);
	static int CheckHitHeroes(CPoint point);
	static int CheckHitPortraitHands(CPoint point);
	static int CheckHitBackpackSlots(CPoint point);
	static int CheckHitContainerSlots(CPoint point);
	static bool CheckHitDeco(CPoint point, CSize size);
	static bool CheckHitMainScr(CPoint);
	static bool CheckHitEye(CPoint);
	static bool CheckHitMouth(CPoint);
	static bool CheckHitSleep(CPoint);
	static bool CheckHitSave(CPoint);
	static bool CheckHitDoorButton(CPoint);
	static SUBPOS CheckHitFloor(CPoint point);
	static SUBPOS CheckHitAir(CPoint point); // throwing

	static CPoint GetBackPackSlotKoords(int index);
	static CPoint GetContainerSlotKoords(int index);


private:
	static bool CheckHitSlot(CPoint clickPoint, CPoint topLeftCorner);

};

