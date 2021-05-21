#include "Entity.h"

Bot::Bot() {
	this->genome.resize(SIZE_GENOME);
	this->rand_genome(SIZE_GENOME, 0, MAX_COMMAND);
	this->energy = 100;
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

		if (sun and minerals or sun and meat or minerals and meat)
			return MIXED;
	}

	//int index = index_max({ sun, minerals, meat });

	/*
	switch (index) {
	case 0:
		return SUN;

	case 1:
		return MINERALS;

	case 2:
		return MEAT;
	}
	*/
	if (minerals)
		return MINERALS;

	else if (meat)
		return MEAT;

	else
		return SUN;
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