#pragma once
class CMonsterConst
{
public:
	int type;
	int size;
	bool levitate;
	bool non_material;
	int height;
	bool mirror_front;
	int mirror_front_dist;
	int move_dur; // 1/6 Sekunde je Tick
	int attack_dur;
	int armor;
	int attack_power;
	int poison;
	int defense;
	int fire_res;
	int poison_res;
};

