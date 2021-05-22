#include "Entity.h"

Bot::Bot(int _energy, int _size) : energy(_energy) {
	steapble = false;
	eatable = true;
	this->genome.resize(_size);
	this->rand_genome(_size, 0, MAX_COMMAND);
	this->index_step = 0;
	this->type = define_the_type();
}

int Bot::define_the_type() {
	int sun = 0, minerals = 0, meat = 0;

	for (int i = 0; i < genome.size(); ++i) {

		if (genome[i] > STEAL and genome[i] < MOVE)
			++sun;

		else {

			if (genome[i] > COPY and genome[i] < EAT_BOT)
				++minerals;

			else {

				if (genome[i] > SWAP_MINERALS and genome[i] < CHECK_ENERGY)
					++meat;
			}

		}
	}

	if (sun == minerals and sun == meat)
		return MIXED;

	int index = index_max({ sun, minerals, meat });

	switch (index) {
	case 0:
		return SUN;

	case 1:
		return MINERALS;

	case 2:
		return MEAT;
	}
}

Form Bot::get_form() {
	switch (type) {

	case SUN:
		return Form("sunBot.png");

	case MINERALS:
		return Form("mineralsBot.png");

	case MEAT:
		return Form("meatBot.png");

	case MIXED:
		return Form("mixedBot.png");
	}
}

int index_max(vector<int> vec) {
	int max = vec[0];
	int index = 0;

	for (int i = 1; i < vec.size(); ++i) {

		if (vec[i] > max) {

			max = vec[i];
			index = i;
		}
	}

	return index;
}

void Bot::rand_genome(int size, int left, int right) {
	for (int i = 0; i < size; ++i)
		genome[i] = rand() % right + left;
}

string get_command_name(int step) {

	if (step < LOOK)
		return "look";

	else {

		if (step < CONVERT_TO_FOOD)
			return "convert";

		else {

			if (step < STEAL)
				return "steal";

			else {

				if (step < PHOTOSYNTHESIS)
					return "photosynthesis";

				else {

					if (step < MOVE)
						return "move";

					else {

						if (step < EAT)
							return "eat_";

						else {

							if (step < COPY)
								return "copy";

							else {

								if (step < SWAP_MINERALS)
									return "swap";

								else {

									if (step < EAT_BOT)
										return "eat_bot";

									else {

										if (step < CHECK_ENERGY)
											return "check";

										else {

											if (step < CYCLIC_MOVE)
												return "cyclic";
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}


}