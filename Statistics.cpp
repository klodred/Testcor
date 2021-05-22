#include "Statistics.h"

void Statistics::update_bot(Bot bot) {
	count_bots = bot.get_energy() > 0 ? count_bots + 1 : count_bots - 1;

	switch (bot.get_type()) {

	case MINERALS:
		count_minerals_bots = bot.get_energy() > 0 ? count_minerals_bots + 1 : count_minerals_bots - 1;
		break;

	case SUN:
		count_sun_bots = bot.get_energy() > 0 ? count_sun_bots + 1 : count_sun_bots - 1;
		break;

	case MEAT:
		count_meat_bots = bot.get_energy() > 0 ? count_meat_bots + 1 : count_meat_bots - 1;
		break;

	case MIXED:
		count_mixed_bots = bot.get_energy() > 0 ? count_mixed_bots + 1 : count_mixed_bots - 1;
		break;
	}
}
