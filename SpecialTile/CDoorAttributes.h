#pragma once
class CDoorAttributes
{
public:
	enum OpeningDir {
		Horizontal,
		Vertical
	};
	int type;
	bool button;
	bool force; // todo
	bool fireball; // todo
	bool vertical; // todo
	int ornate; // todo
	OpeningDir openingDir; // todo
};

