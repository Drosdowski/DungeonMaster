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
	bool force;
	bool fireball;
	bool vertical; // todo
	int ornateId;
	OpeningDir openingDir; // todo
};

