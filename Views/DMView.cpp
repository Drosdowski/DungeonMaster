// DMView.cpp : implementation of the CDMView class
//
#include "stdafx.h"
#include "DM.h"

#include <winuser.rh>

#include "..\DMDoc.h"
#include "DMView.h"
#include "RaumView.h"
#include "ZauberView.h"
#include "CGroupView.h"
#include "..\CalculationHelper/CScreenCoords.h"
#include "..\CalculationHelper/CHelpfulValues.h"
#include "..\CalculationHelper/ZoomBlt.h"
#include "..\XMLParser\CDungeonMap.h"
#include "..\Rucksack.h"
#include "..\Pictures\CPictures.h"
#include "..\Pictures/Items3D/CItem3DPic.h"
#include "..\Mobs\MobGroups\GrpHeld.h"
#include "..\Mobs\MobGroups\GrpMonster.h"
#include "..\Mobs\Held.h"
#include "..\ColorCursor/ColorCursor.h"
#include "..\SpecialTile/CDoor.h"
#include "..\SpecialTile\CPit.h"
#include "..\SpecialTile\TrickWall.h"
#include "..\SpecialTile\CTeleporter.h"
#include "..\Items/Item.h"
#include "..\Items/Potion.h"
#include "..\Items/CMiscellaneous.h"
#include "..\Items/Container.h"
#include "..\Items/WallDecoration.h"
#include "..\Items\MagicMissile.h"
#include "..\Items\Text.h"
#include <cassert>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDMView

IMPLEMENT_DYNCREATE(CDMView, CView)

BEGIN_MESSAGE_MAP(CDMView, CView)
	//{{AFX_MSG_MAP(CDMView)
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_TIMER()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDMView construction/destruction

CDMView::CDMView()
{
	m_pPictures = NULL;
	m_pRaumView = new CRaumView();
	m_pZauberView = new CZauberView();
	m_pGroupView = new CGroupView();
	m_bSleep = false;
	m_bPause = false;
	m_iModus = MOD_LAUFEN;
	lastModus = MOD_LAUFEN;
	m_iDir = 0;
	((CDMApp*)AfxGetApp())->SetView(this);

	/*CFont* pFont;

	pFont->CreateFont(8,0,0,0,FW_NORMAL,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_MODERN, NULL);
	SetFont(pFont);*/
}

CDMView::~CDMView()
{
	delete m_pRaumView;
	delete m_pZauberView;
	delete m_pGroupView;
	delete m_pPictures;
	//	KillTimer(this, idTimer ); 
	((CDMApp*)AfxGetApp())->SetView(NULL);
}

BOOL CDMView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDMView drawing

void CDMView::OnDraw(CDC* pRealDC)
{
	CDMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}


/////////////////////////////////////////////////////////////////////////////
// CDMView diagnostics

#ifdef _DEBUG
void CDMView::AssertValid() const
{
	CView::AssertValid();
}

void CDMView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDMDoc* CDMView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDMDoc)));
	return (CDMDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDMView message handlers

void CDMView::ParseClickArrows(CPoint point) {
	CDMDoc* pDoc = (CDMDoc*)GetDocument();
	int newDir = CScreenCoords::CheckHitArrows(point);
	if (newDir > 0) {
		m_iDir = newDir;
		if ((m_iModus == MOD_LAUFEN) && (m_iDir > 0))
		{
			UpdateGrafik();
			pDoc->SetzeRichtung(m_iDir);
		}
	}
}

void CDMView::ParseClickMagic(CPoint point) {
	CGrpHeld* grpHelden = m_pRaumView->GetHeroes();
	ParseClickWizardChoice(point, grpHelden);
	ParseClickRunes(point, grpHelden);
	ParseClickSpell(point, grpHelden);
}


void CDMView::ParseClickWizardChoice(CPoint point, CGrpHeld* grpHelden) {
	int heroId = grpHelden->GetActiveWizard();
	int newWizardId = CScreenCoords::CheckHitActiveWizard(point, heroId);
	if (newWizardId > 0)
	{
		if (grpHelden->SetActiveCaster(newWizardId))
		{
			CHeld* newWizard = grpHelden->GetHero(newWizardId);
			CDC* pDC = GetDC(); 
			ZauberReiterZeichnen(pDC, newWizardId, newWizard->getRuneTableId(), newWizard->getSpell());
			UpdateGrafik();
		}
	}
}

void CDMView::ParseClickRunes(CPoint point, CGrpHeld* grpHelden) {
	int runeId = CScreenCoords::CheckHitRunes(point);
	if (runeId > 0) {
		const int heroId = grpHelden->GetActiveWizard();
		CHeld* caster = grpHelden->GetHero(heroId);
		
		int manaNeeded = CHelpfulValues::ManaCost(caster->getRuneTableId(), runeId, caster->GetPower());
		if (caster->UseMana(manaNeeded)) {
			caster->storeRune(runeId);
		}
	}
}
void CastPotion(CPotion* potion, int power, CPotionAttributes::PotionType type) {
	CPotionAttributes attribute;
	attribute.power = power;
	attribute.type = type;
	potion->MakePotion(attribute);
}

void CDMView::ParseClickSpell(CPoint point, CGrpHeld* grpHelden) {
	if (CScreenCoords::CheckHitSpell(point)) {
		const int heroId = grpHelden->GetActiveWizard();
		CHeld* pHeld = grpHelden->GetHero(heroId);
		if (!pHeld->isAlive())
			return;
		int* spell = pHeld->getSpell();

		CItem* itemInHand = pHeld->GetItemCarrying(1);
		bool emptyFlaskInHand = itemInHand && itemInHand->GetType() == CPotionAttributes::PotionType::Empty;

		// Magic Missiles
		if (spell[2, heroId] == 4 && spell[3] == 4 && spell[4] == 0) {
			CastMagicMissile(CMagicMissile::MagicMissileType::Fireball, spell[1]);
		}
		else if (spell[2] == 3 && spell[3] == 1 && spell[4] == 0) {
			CastMagicMissile(CMagicMissile::MagicMissileType::Poison, spell[1]);
		}
		else if (spell[2] == 6 && spell[3] == 0) {
			CastMagicMissile(CMagicMissile::MagicMissileType::OpenDoor, spell[1]);
		}
		// Potions
		else if (spell[2] == 2 && emptyFlaskInHand) {
			CastPotion((CPotion*)itemInHand, spell[1], CPotionAttributes::PotionType::Vi);
		}
		pHeld->resetRuneTable();
	}
}


void CDMView::CastMagicMissile(CMagicMissile::MagicMissileType missileType, int size) {
	CGrpHeld* grpHelden = m_pRaumView->GetHeroes();
	COMPASS_DIRECTION grpDir = grpHelden->GetDirection();
	SUBPOS_ABSOLUTE absPos = grpHelden->GetHero(grpHelden->GetActiveWizard())->HoleSubPosition();
	SUBPOS relPos = CHelpfulValues::GetRelativeSubPosPassive(absPos, grpDir);
	CMagicMissile* magicMissile = new CMagicMissile(missileType, size);
	SUBPOS_ABSOLUTE itemRegionReal = CHelpfulValues::GetRelativeSubPosActive(relPos, grpDir);
	VEKTOR force = CHelpfulValues::MakeVektor(grpDir, size);
	magicMissile->m_flyForce = force;

	m_pRaumView->GetMap()->GetField(grpHelden->GetVector())->CastMissile(magicMissile, itemRegionReal);
	// todo: EXP =rand(7)+((spell difficulty+spell power)*16)+(8*((spell power - 1)*spell difficulty))+((spell difficulty+spell power)*(spell difficulty + spell power))
}


void CDMView::ParseClickAction(CPoint point) {
	CGrpHeld* grpHelden = m_pRaumView->GetHeroes();

	Phase actionPhase = grpHelden->GetActionPhase();
	int actionNumber = CScreenCoords::CheckHitAction(point, actionPhase);
	if (actionNumber > 0 && actionPhase == CHOOSE_HERO)
	{
		grpHelden->ChooseHeroForAction(actionNumber);
	}
	else if (actionNumber != 0 && actionPhase == CHOOSE_ACTION) {
		if (actionNumber == PASS) 
		{
			grpHelden->PassAction();
		}
		else {
			// action auch setzen !
			m_pRaumView->DoActionForChosenHero(grpHelden, actionNumber);
		}
		UpdateGrafik();
	}

}

void CDMView::ParseClickDoorButton(CPoint point, CField* FeldVorHeld) {

	CDoor* door = FeldVorHeld->HoleDoor();
	if (door && door->hasButton()) {
		if (CScreenCoords::CheckHitDoorButton(point)) {
			door->Toggle();
		}
	}
}

void CDMView::ParseClickFountain(CPoint point, CField* FeldVorHeld, COMPASS_DIRECTION dir) {

	CWallDecoration* deco = FeldVorHeld->GetWallDeco(dir);
	if (deco && deco->GetDecoType() == Fountain) {
		CSize size = m_pRaumView->GetSizeOfFrontDeco(FeldVorHeld, dir);
		if (CScreenCoords::CheckHitDeco(point, size)) {
			CGrpHeld* grpHelden = m_pRaumView->GetHeroes();
			if (grpHelden == NULL) return;
			CHeld* activeHero = grpHelden->GetActiveHero();
			CItem* itemInHand = grpHelden->GetItemInHand();
			if (itemInHand == NULL) {
				// Hand leer = trinken
				activeHero->Trinken(50); // todo amount drink?
			}
			else {
				// item in hand füllen
				if (itemInHand->getItemType() == CItem::MiscItem) {
					CMiscellaneous* container = (CMiscellaneous*)itemInHand;
					if (container->GetIndex() == 11 && container->GetSubtype() < 3) {
						// Waterskin todo empty flask
						container->SetSubtype(3); // change to full
					}
				}
				else if (itemInHand->getItemType() == CItem::PotionItem) {
					CPotion* potion = (CPotion*)itemInHand;
					CPotionAttributes att = potion->GetAttributes();
					if (att.type == CPotionAttributes::Empty)
					{
						att.type = CPotionAttributes::Water;
						potion->MakePotion(att);
					}
				}
			}
		}
	}
}


void CDMView::ParseClickPortrait(CPoint point) {
	int heroID = CScreenCoords::CheckHitHeroes(point);
	if (heroID > 0)
	{
		CGrpHeld* grpHelden = m_pRaumView->GetHeroes();
		grpHelden->Aktiviere(heroID);
	}
}

bool CDMView::ParseClickPortraitHands(CPoint point, bool backpackMode) {
	int handId = CScreenCoords::CheckHitPortraitHands(point);
	if (handId > 0) {
		// 1 2 3 4 5 6 7 8	HandId
		// 1 1 2 2 3 3 4 4  HeroId
		// 0 1 0 1 0 1 0 1  HandOfHeroId
		int heroId = (int)((handId + 1) / 2);
		int handOfHeroId = (handId - 1) % 2;					// TODO auslagern, und dann auch in Backpack nutzen!

		CGrpHeld* grpHelden = m_pRaumView->GetHeroes();
		CHeld* clickedHero = grpHelden->GetHero(heroId);
		if ((clickedHero == NULL) || (clickedHero->isActive() && backpackMode))
			return false; // Hände durch Portrait überdeckt.

		grpHelden->PutGetItem(handOfHeroId, heroId);

		return true;
	}
	else
		return false;
}

/// <summary>
/// Werfen
/// </summary>
/// <param name="point"></param>
void CDMView::ParseClickAir(CPoint point) {
	CGrpHeld* grpHelden = m_pRaumView->GetHeroes();
	CItem* pItemInHand = grpHelden->GetItemInHand();

	if (pItemInHand != NULL) {
		SUBPOS airRegionClicked = CScreenCoords::CheckHitAir(point);
		if (airRegionClicked != NONE) {
			CField* FeldVorHeld = m_pRaumView->GetMap()->GetField(grpHelden->HoleZielFeld(VORWAERTS));
			if (FeldVorHeld) {
				if (FeldVorHeld->BlockedToWalk()) {
					// skip, nix.
				}
				else
				{
					COMPASS_DIRECTION grpDir = grpHelden->GetDirection();
					SUBPOS_ABSOLUTE itemRegionReal = CHelpfulValues::GetRelativeSubPosActive(airRegionClicked, grpDir);
					VEKTOR force = CHelpfulValues::MakeVektor(grpDir, 6);
					m_pRaumView->GetMap()->GetField(grpHelden->GetVector())->ThrowItem(pItemInHand, itemRegionReal, force);
					grpHelden->EmptyHand();
				}
			}

		}
	}
}

bool CDMView::ParseClickActuator(CPoint point, std::deque<CActuator*>& actuators, COMPASS_DIRECTION dir, CSize size) {
	CGrpHeld* grpHelden = m_pRaumView->GetHeroes();
	
	std::deque<CActuator*> actuatorsAtPosition;
	COMPASS_DIRECTION pos;
	for (CActuator* actuator : actuators) {
		// Alle Aktuatoren sammeln, die an der angeschauten Position sind.
		pos = actuator->GetPosition();
		if (pos == dir) {
			actuatorsAtPosition.push_back(actuator);
		}

	}
	if (actuatorsAtPosition.size() > 0)
		if (CScreenCoords::CheckHitDeco(point, size))
		{
			CActuator::ActuatorType type = actuatorsAtPosition.back()->GetType();
			CActuator* currentActuator = actuatorsAtPosition.back();
			CActuator* nextActuator = actuatorsAtPosition.front();
			CActuator::ActionTarget actionTarget = currentActuator->GetActionTarget();
			CItem* itemInHand = grpHelden->GetItemInHand();
			CField* FeldVorHeld = m_pRaumView->GetMap()->GetField(grpHelden->HoleZielFeld(VORWAERTS));
			SUBPOS_ABSOLUTE posActuator = (SUBPOS_ABSOLUTE)dir;
			std::deque<CItem*> itemsInWall = FeldVorHeld->GetItem(posActuator);
			int data = currentActuator->GetData();

			if (!currentActuator->IsActive()) return false;

			if (type == CActuator::PressurePadTPCI) {
				// Schalter 
				//VEKTOR target;
				InvokeRemoteActuator(currentActuator, nextActuator);
				return true; // RotateActuators
			}
			else if (type == CActuator::Slot /* || type == 3 */) {
				// Item Receiver - Lock / ... ?
				CGrpHeld* grpHelden = m_pRaumView->GetHeroes();
				CItem* itemInHand = grpHelden->GetItemInHand();
				if (itemInHand) {
					int neededItemId;
					if (data > 120 && data < 130) {
						neededItemId = data - 119;
					} else if (data > 129 && data < 167) {
						neededItemId = data - 90;
					} else if (data > 167) {
						neededItemId = data - 167;
					}
					else assert(false); // todo formel verstehen. - coin = 125  <> index 6 / type 4				- 119
										//								   127 => 	Key: 184 => Gold Key=17		
										//								   134 => Mirror => 44					- 90
										//								   186 => topaz	=19						- 167
										//								   176 => 9 Iron Key					- 167
										//								   177 => 10							- 167
					if (neededItemId == itemInHand->GetType()) {
						// Match !
						if (currentActuator->GetActionTarget() == CActuator::Remote) {
							InvokeRemoteActuator(currentActuator, nextActuator);
						}
						else assert(false); // todo ...

						if (type == 4)
						{
							grpHelden->EmptyHand();
							delete (itemInHand);
							::SystemParametersInfo(SPI_SETCURSORS, 0, 0, SPIF_SENDCHANGE);
						}
						if (currentActuator->IsOnceOnly()) {
							currentActuator->Deactivate();
						}
						return true; // RotateActuators
					}
				}
			}
			else if (type == CActuator::Storage || type == CActuator::Inactive)
			{
				int neededItemId = currentActuator->GetData() + 2; // todo formel verstehen.
				if (itemInHand == NULL) {
					grpHelden->TakeItemInHand(FeldVorHeld->TakeItem(posActuator));
					if (!type == CActuator::Inactive) {
						// Torch Holder => Empty holder = Item gone
						//InvokeRemoteActuator(currentActuator, nextActuator);
						FeldVorHeld->RotateActuators(dir);
					}
					return false;
				}
				else if (currentActuator->GetData() == 0) {
					FeldVorHeld->PutItem(itemInHand, posActuator);
					grpHelden->EmptyHand();
					//if (!type == CActuator::Inactive) {
					// Torch Holder => Empty holder = Item gone
					FeldVorHeld->RotateActuators(dir);
					//}
					return false;
				} else if (itemInHand->GetType() == neededItemId) {
					//if (!type == CActuator::Inactive) {
					//	// Torch Holder => Empty holder = Item gone
					//	//InvokeRemoteActuator(currentActuator, nextActuator);					
					//	FeldVorHeld->RotateActuators(dir);
					//}
					FeldVorHeld->PutItem(itemInHand, posActuator);
					grpHelden->EmptyHand();
					return false;
				}

			}
			else if (type == CActuator::ChampionMirror) {
				CField* field = m_pRaumView->GetMap()->GetField(grpHelden->GetVector());
				CString text = field->GetFirstText(0)->GetText();
				CBitmap* pic = m_pRaumView->GetHeroPic(data);			

				grpHelden->RessurectHero(text);
				currentActuator->Deactivate();
			}
			else {
				// Alkoven & co
				if (itemInHand == NULL) {
					if (itemsInWall.size() > 0) {
						grpHelden->TakeItemInHand(FeldVorHeld->TakeItem(posActuator)); 
					}
				}
				else {
					FeldVorHeld->PutItem(itemInHand, posActuator);
					grpHelden->EmptyHand();
				}
			}
		}
	return false;
}

void CDMView::InvokeRemoteActuator(CActuator* activeActuator, CActuator* nextActuator) {
	VEKTOR target = activeActuator->GetActionTarget() == CActuator::ActionTarget::Remote ? activeActuator->GetTarget() : nextActuator->GetTarget();
	CField* pTargetField = m_pRaumView->GetMap()->GetField(target);
	std::deque<CActuator*> pTargetActuators;
	CDoor* door;
	CPit* pit;
	CTrickWall* trickwall;
	CTeleporter* port;

	switch (pTargetField->HoleTyp()) {
	case FeldTyp::DOOR:
		door = pTargetField->HoleDoor();
		if (activeActuator->GetActionType() == CActuator::Toggle) door->Toggle();
		if (activeActuator->GetActionType() == CActuator::Set) door->Open();
		if (activeActuator->GetActionType() == CActuator::Hold) door->Open();
		if (activeActuator->GetActionType() == CActuator::Clear) door->Close();
		break;
	case FeldTyp::PIT:
		pit = pTargetField->HolePit();
		if (activeActuator->GetActionType() == CActuator::Toggle) pit->Toggle();
		if (activeActuator->GetActionType() == CActuator::Set) {
			pit->Close(0);
		}
		if (activeActuator->GetActionType() == CActuator::Hold) pit->Open(0);
		if (activeActuator->GetActionType() == CActuator::Clear) {
			pit->Close(0);
			if (activeActuator->Action() == -1 && nextActuator->Action() == -1)
			{
				// reactivate with delay
				pit->Open(nextActuator->GetDelay());
			}
		}
		break;
	case FeldTyp::TELEPORT:
		port = pTargetField->HoleTeleporter();
		if (port->getScope() == TeleporterAttributes::None) {
			port->setOpen(CTeleporter::Active, 0);
			port->Trigger(GetDocument(), m_pRaumView->GetMap(), target, true);
			if (activeActuator->Action() == -1 && nextActuator->Action() == -1)
			{
				// reactivate with delay
				port->setOpen(CTeleporter::Inactive, nextActuator->GetDelay());
			}
		}
		else {
			port->setOpen(CTeleporter::Inactive, 0);
		}
		break;
	case FeldTyp::TRICKWALL:
		trickwall = pTargetField->HoleTrickWall();
		if (activeActuator->GetActionType() == CActuator::Toggle) trickwall->Toggle();
		if (activeActuator->GetActionType() == CActuator::Set) {
			trickwall->Open(0);
			if (activeActuator->Action() == -1 && nextActuator->Action() == -1)
			{
				trickwall->Close(nextActuator->GetDelay());
			}
		}
		if (activeActuator->GetActionType() == CActuator::Hold) trickwall->Open(0);
		if (activeActuator->GetActionType() == CActuator::Clear) {
			trickwall->Close(0);
			if (activeActuator->Action() == -1 && nextActuator->Action() == -1)
			{ 
				trickwall->Open(nextActuator->GetDelay());
			}
		}
		break;
	case FeldTyp::WALL: 
		if (activeActuator->GetActionTarget() == CActuator::ActionTarget::Remote) {
			// switch 1: <actuator index="274" position="1">
			// switch 2: <actuator index="275" position="3">
			for (int dir = 0; dir < 4; dir++) {
				pTargetActuators = pTargetField->GetActuator(COMPASS_DIRECTION(dir));
				if (pTargetActuators.size() > 0) {
					CActuator* gateActuator = pTargetActuators.back();
					if (gateActuator->GetType() == CActuator::Gate) {
						if (activeActuator->GetActionType() == CActuator::Toggle) gateActuator->IncreaseGate();
						if (gateActuator->GateFull())
							InvokeRemoteActuator(gateActuator, NULL);
					}
					else {
						assert(false);
					}
				}
			}
		}
		else if (activeActuator->GetActionTarget() == CActuator::ActionTarget::Local) {
			for (int dir = 0; dir < 4; dir++) {
				pTargetActuators = pTargetField->GetActuator(COMPASS_DIRECTION(dir));
				if (pTargetActuators.size() > 0) {
					CActuator* gateActuator = pTargetActuators.back();
					if (gateActuator->GetType() == CActuator::Gate) {
						if (activeActuator->GetActionType() == CActuator::Set) gateActuator->DecreaseGate();
						if (gateActuator->GateFull())
							InvokeRemoteActuator(gateActuator, NULL);
					}
					else {
						// assert(false);
						// pTargetField->RotateActuators();
					}
				}
			}
		}
		break;

	default:
		break;
	}
}

void CDMView::ParseClickFloor(CPoint point) {
	CGrpHeld* grpHelden = m_pRaumView->GetHeroes();
	CItem* pItemInHand = grpHelden->GetItemInHand();

	SUBPOS itemRegionClicked = CScreenCoords::CheckHitFloor(point);
	COMPASS_DIRECTION groupDirection = grpHelden->GetDirection();
	SUBPOS_ABSOLUTE itemRegionReal = CHelpfulValues::GetRelativeSubPosActive(itemRegionClicked, groupDirection);
	CItem* topItem = NULL;
	if (itemRegionClicked == LINKSBACK || itemRegionClicked == RECHTSBACK)
	{
		CField* FeldVorHeld = m_pRaumView->GetMap()->GetField(grpHelden->HoleZielFeld(VORWAERTS));
		if (FeldVorHeld && !FeldVorHeld->BlockedToPut())
		{
			if (pItemInHand == NULL)
				topItem = FeldVorHeld->TakeItem(itemRegionReal);
			else {
				FeldVorHeld = m_pRaumView->ChangeFieldWithTeleporter(FeldVorHeld, itemRegionReal, groupDirection);
				grpHelden->SetDirection(groupDirection);
				FeldVorHeld = m_pRaumView->ChangeFieldWithStairs(FeldVorHeld, pItemInHand, itemRegionReal);

				FeldVorHeld->PutItem(pItemInHand, itemRegionReal);
				grpHelden->EmptyHand();
			}

		}
	}
	else if (itemRegionClicked == LINKSFRONT || itemRegionClicked == RECHTSFRONT) {
		CField* FeldUnterHeld = m_pRaumView->GetMap()->GetField(grpHelden->GetVector());
		if (FeldUnterHeld)
		{
			if (pItemInHand == NULL)
				topItem = FeldUnterHeld->TakeItem(itemRegionReal);
			else {
				FeldUnterHeld->PutItem(pItemInHand, itemRegionReal);
				grpHelden->EmptyHand();
			}
		}
	}
	if (itemRegionClicked != NONE && topItem) {
		grpHelden->TakeItemInHand(topItem);
		ChangeMouseCursor();
	}

}


void CDMView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_bSleep) {
		Awake();
	} else {

		CDMDoc* pDoc = (CDMDoc*)GetDocument();
		CGrpHeld* grpHelden = m_pRaumView->GetHeroes();
		if (m_iModus == MOD_LAUFEN)
		{
			ParseClickArrows(point);
			ParseClickFloor(point);
			ParseClickMagic(point);
			ParseClickAction(point);
			if (!ParseClickPortraitHands(point, false))
				ParseClickPortrait(point);


			// Unterscheiden: Anklicken oder werfen?
			CField* FeldVorHeld = m_pRaumView->GetMap()->GetField(grpHelden->HoleZielFeld(VORWAERTS));
			if (FeldVorHeld) {
				ParseClickDoorButton(point, FeldVorHeld);
				if (FeldVorHeld->BlockedToPut()) {
					COMPASS_DIRECTION dir = CHelpfulValues::OppositeDirection(grpHelden->GetDirection());
					std::deque<CActuator*> actuators = (FeldVorHeld->GetActuator(dir));
					if (!actuators.empty()) {
						CSize size = m_pRaumView->GetSizeOfFrontDeco(FeldVorHeld, dir);

						if (ParseClickActuator(point, actuators, dir, size))
							FeldVorHeld->RotateActuators(dir);
					}
					ParseClickFountain(point, FeldVorHeld, dir);

				}
				else {
					ParseClickAir(point);
				}
			}

		}
		else if (m_iModus == MOD_RUCKSACK)
		{
			if (CScreenCoords::CheckHitMainScr(point)) {
				ParseClickBackpack(point);
				ChangeMouseCursor();
			}
			else {
				if (!ParseClickPortraitHands(point, true))
					ParseClickPortrait(point);
				ParseClickMagic(point);
			}
		}
	}
	CView::OnLButtonDown(nFlags, point);
}

void CDMView::ParseClickBackpack(CPoint point) {
	CGrpHeld* grpHelden = m_pRaumView->GetHeroes();
	CHeld* pHeld = grpHelden->GetActiveHero();
	CItem* itemInMainHand = grpHelden->GetItemInHand();
	if (CScreenCoords::CheckHitEye(point))
		pHeld->GetRucksack()->SetzeModusExtend(MOD_EXT_AUGE);
	else if (itemInMainHand && CScreenCoords::CheckHitMouth(point))
	{
		CWeapon* weapon = NULL;
		if (itemInMainHand->getItemType() == CItem::ItemType::MiscItem) {
			CMiscellaneous* misc = (CMiscellaneous*)itemInMainHand;
			if (misc && misc->GetGroup() == CMiscellaneous::ItemGroup::Consumable) {
				if (misc->GetType() == CMiscellaneousAttributes::MiscItemType::Water) {
					if (misc->GetSubtype() > 0) {
						pHeld->Trinken(50);
						misc->SetSubtype(misc->GetSubtype() - 1);
					}
				}
				else {
					pHeld->Essen(50);
					grpHelden->EmptyHand();
					delete itemInMainHand; // destroy permanently!
				}
			}
		}
		else if (itemInMainHand->getItemType() == CItem::ItemType::PotionItem) {
			// drink potions
			CPotion* potion = (CPotion*)itemInMainHand;
			CPotionAttributes att = potion->GetAttributes();
			if (potion->GetType() == CPotionAttributes::Vi) {
				pHeld->WerteTemporaerAendern(att.power*10, 0, 0);
				att.power = 0;
				att.type = CPotionAttributes::PotionType::Empty;
				potion->MakePotion(att);
			}
			else if (potion->GetType() == CPotionAttributes::Water)
			{
				pHeld->Trinken(50);
				att.type = CPotionAttributes::PotionType::Empty;
				potion->MakePotion(att);
			}
		}
	}
	else if (CScreenCoords::CheckHitSleep(point)) {
		m_bSleep = true;
		SetTimer(7, 20, NULL);
	}
	else if (CScreenCoords::CheckHitSave(point)) {
		m_pRaumView->GetMap()->SaveGame(grpHelden);
	}
	else {
		// todo refaktorieren mit PutGetItem()
		int slot = CScreenCoords::CheckHitBackpackSlots(point);
		if (slot >= 0) {
			SwitchBackpackItem(itemInMainHand, slot, grpHelden);
		}
		else {
			CItem* pItem = pHeld->GetItemCarrying(1);
			if (pItem && pItem->getItemType() == CItem::ContainerItem) {
				slot = CScreenCoords::CheckHitContainerSlots(point);
				if (slot >= 0) {
					SwitchContainerItem(itemInMainHand, slot, grpHelden, (CContainer*)pItem);
				}
			}
		}
	}
	if (itemInMainHand && itemInMainHand->getItemType() == CItem::ContainerItem) {
		int slot = CScreenCoords::CheckHitContainerSlots(point);
		if (slot >= 0) {
			SwitchBackpackItem(itemInMainHand, slot, grpHelden);
		}
	}
}

void CDMView::SwitchBackpackItem(CItem* itemInMainHand, int slot, CGrpHeld* grpHelden) {
	CHeld* pHeld = grpHelden->GetActiveHero();
	CItem* newItemInHandToGet = NULL;

	if (itemInMainHand && itemInMainHand->CheckGroup(slot, itemInMainHand->GetGroup()))
	{
		newItemInHandToGet = pHeld->SwitchItemAt(slot, itemInMainHand);
	}
	else if (!itemInMainHand) {
		newItemInHandToGet = pHeld->GetItemCarrying(slot);
	}
	else {
		// not allowed
		return;
	}
	grpHelden->EmptyHand();
	if (newItemInHandToGet == NULL) {
		// ablegen - passt.
	}
	else {
		// tauschen		
		grpHelden->TakeItemInHand(newItemInHandToGet);
		if (!itemInMainHand)
			pHeld->RemoveItemCarrying(slot);

	}
}

void CDMView::SwitchContainerItem(CItem* itemInMainHand, int slot, CGrpHeld* grpHelden, CContainer* pContainer) {
	CItem* newItemInHandToGet = NULL;

	if (itemInMainHand)
	{
		newItemInHandToGet = pContainer->SwitchItemAt(slot, itemInMainHand);
	}
	else  {
		newItemInHandToGet = pContainer->GetItemCarrying(slot);
	}
	grpHelden->EmptyHand();
	if (newItemInHandToGet == NULL) {
		// ablegen - passt.
	}
	else {
		// tauschen		
		grpHelden->TakeItemInHand(newItemInHandToGet);
		if (!itemInMainHand)
			pContainer->RemoveItemCarrying(slot);

	}
}


void CDMView::OnRButtonDown(UINT nFlags, CPoint point)
{
	if (m_bSleep) {
		Awake();
	}
	else {
		CDMDoc* pDoc = (CDMDoc*)GetDocument();
		CDC* pDC = GetDC();
		CGrpHeld* grpHelden = m_pRaumView->GetHeroes();
		if (grpHelden->GetActiveHero() == NULL) return;

		switch (m_iModus)
		{
		case MOD_LAUFEN:
			if (grpHelden->SetzeModus(pDC, RUCKSACK)) {
				m_iModus = MOD_RUCKSACK;
			}
			break;
			//	}
		case MOD_RUCKSACK:
			if (grpHelden->SetzeModus(pDC, LAUFEN))
			{
				m_iModus = MOD_LAUFEN;
				UpdateGrafik();
			}
			break;
		}
	}
	CView::OnRButtonDown(nFlags, point);
}


void CDMView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (m_bSleep) {
		Awake();
	}
	else {
		CDMDoc* pDoc = GetDocument();
		if (m_iDir == 0)
		{
			switch (nChar)
			{
			case 27:
				if (m_bPause) {
					m_bPause = false;
					m_iModus = lastModus;
				}
				else {
					m_bPause = true;
					lastModus = m_iModus;
					m_iModus = MOD_PAUSE;
				}
				break;
			case 32:
				if (cheatAktiv)
					m_pRaumView->OnTrigger();
				break;
			case 38:
			case 101:
				m_iDir = VORWAERTS;
				break;
			case 40:
			case 98:
				m_iDir = RUECKWAERTS;
				break;
			case 37:
			case 97:
				m_iDir = LINKS_STRAFE;
				break;
			case 39:
			case 99:
				m_iDir = RECHTS_STRAFE;
				break;
			case 100:
				m_iDir = LINKS_DREHEN;
				break;
			case 102:
				m_iDir = RECHTS_DREHEN;
				break;
			case 49:
			case 50:
			case 51:
			case 52:
				pDoc->InitGruppe(nChar - 48);
				break;
			default:
			{
				CString str;
				str.Format("%i ", nChar);
				TRACE(str);
				break;
			}
			}

			if (m_iModus == MOD_LAUFEN)
			{
				if (m_iDir > 0)
				{
					UpdateGrafik();
					pDoc->SetzeRichtung(m_iDir); // noch nicht laufen, nur anmelden
				}
			}
			else if (m_iModus == MOD_RUCKSACK)
			{
				UpdateGrafik();
			}
		}
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CDMView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}

//////////////////////////////////////////////////////////////////////
// Zeichenmethoden



void CDMView::HeldenGrafikZeichnen(CGrpHeld* pGrpHelden, CDC* pDC, CPictures* pPictures)
{
	m_pGroupView->GroupZeichnen(pDC, pPictures, m_iModus, pGrpHelden);
}

void CDMView::ZauberReiterZeichnen(CDC* pDC, int iActiveWizard, int runeTableId, int* runeIds)
{
	m_pZauberView->Zeichnen(m_pPictures, pDC, iActiveWizard, runeTableId, runeIds);
}

void CDMView::ActionAreaZeichnen(CDC* pDC, int weaponIndex) {
	m_pRaumView->DrawActionAreaChoice(pDC, weaponIndex);
}

void CDMView::ActionDamageZeichnen(CDC* pDC, int dmg) {
	m_pRaumView->DrawActionAreaDamage(pDC, dmg);
}

void CDMView::WaffenZeichnen(CDC* pDC, CGrpHeld* pGrpHeroes) {
	CDC tmpdc;
	tmpdc.CreateCompatibleDC(pDC);

	for (int id = 1; id < 5; id++) {
		CHeld* held = pGrpHeroes->GetHero(id);
		if (held && held->isAlive())
		{
			m_pPictures->DrawActiveWeapon(pDC, held, id);
			// todo: cooldown -> schattieren / sperren
		}
	}

	tmpdc.DeleteDC();
}


void CDMView::FrameZeichnen(CDC* pDC) {
	ChangeMouseCursor();

	CGrpHeld* pGrpHeroes = m_pRaumView->GetHeroes();

	if (pGrpHeroes != NULL)
	{
		HeldenGrafikZeichnen(pGrpHeroes, pDC, m_pPictures);
		

		int phase = pGrpHeroes->GetActionPhase();
		if (phase == 1) {
			WaffenZeichnen(pDC, pGrpHeroes);
		}
		else if (phase == 2) {
			CHeld* pHeld = pGrpHeroes->GetHeroForAction();
			if (pHeld) {
				int index;
				CItem* pItem = pHeld->GetItemCarrying(1);
				if (pItem && pItem->getItemType() == CItem::ItemType::WeaponItem) {
					index = pItem->GetType();
				}
				else {
					index = HANDINDEX;
				}
				ActionAreaZeichnen(pDC, index);
			}
		}
		else if (phase == 3) {
			CHeld* pHeld = pGrpHeroes->GetAttackingHero(); 
			if (pHeld)
			{
				ActionDamageZeichnen(pDC, pHeld->GetDealingDamage());
			}
		}

		int iActiveWizard = pGrpHeroes->GetActiveWizard();
		if (iActiveWizard > 0)
		{
			CHeld* pWizard= pGrpHeroes->GetHero(iActiveWizard);

			ZauberReiterZeichnen(pDC, iActiveWizard, pWizard->getRuneTableId(), pWizard->getSpell());
		}
	}

	m_pPictures->PfeilZeichnen(pDC, m_iDir);

}

void CDMView::UpdateGrafik()
{
	RECT r = CZoomBlt::ScreenRect();
	CDC* pDC = GetDC();
	CBitmap tmpbmp;
	//tmpbmp.CreateCompatibleBitmap(pDC, r.right - r.left, r.bottom - r.top);
	tmpbmp.CreateCompatibleBitmap(pDC, 640, 400);
	
	CDC* pDC_ = new CDC();
	pDC_->CreateCompatibleDC(pDC);
	pDC_->SelectObject(tmpbmp);

	FrameZeichnen(pDC_);

	if (!m_bPause)
		if (!m_bSleep)
		{
			if (m_iModus == MOD_LAUFEN)
				m_pRaumView->RaumZeichnen(pDC_);
			else if (m_iModus == MOD_RUCKSACK)
			{
				CGrpHeld* grpHelden = m_pRaumView->GetHeroes();
				m_pPictures->RucksackZeichnen(pDC_, grpHelden);
			}

		}
		else
			// You are asleep
			;
	else
		// Game frozen
		;

	CZoomBlt::DrawFullStretch(pDC, pDC_, 0, 0, 640, 400, 0, 0, 640, 400);
	delete pDC_;
	DeleteObject(tmpbmp);
}

void CDMView::OnTimer(UINT nIDEvent)
{
	CDMDoc* pDoc = GetDocument();

	if (!m_bPause) {
		CGrpHeld* pGrpHeld = m_pRaumView->GetHeroes();
		CField* pField = m_pRaumView->GetMap()->GetField(pGrpHeld->GetVector());
		if (!pGrpHeld->Altern(pField)) {
			// todo: alle tot
		}
		for (int i = 1; i < 5; i++)
		{
			CHeld* pHeld = pGrpHeld->GetHero(i);
			if (pHeld && !pHeld->isAlive() && pHeld->GetItemCarrying(30))
			{
				for (int id = 0; id < 31; id++) {
					CItem* item = pHeld->GetItemCarrying(id);
					if (item) {
						pHeld->RemoveItemCarrying(id);
						pField->PutItem(item, pHeld->HoleSubPosition());
					}
				}
			}
		}

		if (m_pRaumView->GetHeroes()->GetNumberOfHeroes() > 0) {
			m_pRaumView->MoveAnythingNearby();
			m_pRaumView->TriggerActuatorsNearby();
		}

		if (m_iDir > 0)
		{
			pDoc->Laufen();
			m_iDir = 0;
		}
		UpdateGrafik();
	}
	else {
		UpdateGrafik();
	}

	CView::OnTimer(nIDEvent);
}

void CDMView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_iModus == MOD_RUCKSACK)
	{
		m_pRaumView->GetHeroes()->GetActiveHero()->GetRucksack()->SetzeModusExtend(MOD_EXT_NORMAL);
	}

	CView::OnLButtonUp(nFlags, point);
}

void CDMView::InitDungeon(CDMDoc* pDoc)
{
	CDC* pDC = GetDC();
	m_pPictures = new CPictures(pDC);
	m_pRaumView->InitDungeon(pDoc, pDC, m_pPictures);
	pDoc->SetRaumView(m_pRaumView);
}

void CDMView::ChangeMouseCursor() {
	// todo: hier zu oft drin !!
	CGrpHeld* heroes = m_pRaumView->GetHeroes();
	if (heroes) {
		CItem* item = heroes->GetItemInHand();
		if (item) {
			CDC* pDC = GetDC();
			CBitmap* bmp = m_pPictures->GetIconBitmap(pDC, item); //heroes->GetItemInHand()->GetPicByType(m_pRaumView->Get3DPics());
			if (bmp) {
				HBITMAP hBmp = (HBITMAP)bmp->GetSafeHandle();
				HCURSOR hCursor = CColorCursor::CreateCursorFromBitmap(hBmp, TRANS_GRA, 16, 16);
				SetSystemCursor(hCursor, OCR_NORMAL);
				delete bmp;
				return;
			}
		}
	}
	::SystemParametersInfo(SPI_SETCURSORS, 0, 0, SPIF_SENDCHANGE);
}

void CDMView::Awake() {
	m_bSleep = false;
	m_iModus = MOD_LAUFEN;
	SetTimer(7, 166, NULL);
}