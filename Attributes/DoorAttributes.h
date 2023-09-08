#pragma once
class CDoorAttributes
{
public:
	enum OpeningDir {
		Horizontal,
		Vertical
	};
	enum DoorType {
		Iron = 0,
		Wood = 1
	};

	DoorType type;
	bool button;
	bool force; // todo
	bool fireball; // todo
	bool vertical; // todo
	int ornateId;
	OpeningDir openingDir; // todo
};

