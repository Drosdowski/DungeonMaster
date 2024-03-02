#pragma once
class CPotionAttributes
{
public:
	enum PotionType {
		Des = 2,
		Ven = 3,
		Ros = 6,
		Ku = 7,
		Dane = 8,
		Neta = 9,
		Ma = 9,
		Bro = 10,
		Ya = 12,
		Vi = 14,
		Water = 15,
		Ful = 19,
		Empty = 20
	};

	PotionType type;
	int power;
};

