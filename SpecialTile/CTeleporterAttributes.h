#pragma once
class TeleporterAttributes
{
public:
	enum RotationType {
		Absolute,
		Relative
	};
	enum Scope {
		Items,
		Creatures,
		Items_Party,
		All,
		None
	};

	int sound;
	VEKTOR target;
	int rotation;
	RotationType rotationType;
	Scope scope;
};

