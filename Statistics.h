#pragma once
#include "Entity.h"

class Statistics {
public:
	int count_bots = 0;
	int count_sun_bots = 0;
	int count_meat_bots = 0;
	int count_minerals_bots = 0;
	int count_mixed_bots = 0;
	int count_health = 0;
	int count_poison = 0;
	int count_wall = 0;

	Statistics() {};

	void update_bot(Bot bot);

	void update_wall(int count) { count_wall += count; };

	void update_health(int count) { count_health += count; };

	void update_poison(int count) { count_poison += count; };
};
