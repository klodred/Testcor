#include "Settings.h"

int Settings::direction_identifier(Entity* entity) {
	if (entity->is_empty())
		return 2;

	else {

		if (entity->is_wall())
			return 3;

		else {

			if (entity->is_bot())
				return 4;

			else {

				if (entity->is_health() or entity->is_poison())
					return 5;
			}
		}
	}
}

int Settings::index_step() {
	switch (this->current_season) {

	case SUMMER:
		return 1;

	case AUTUMN:
		return 2;

	case WINTER:
		return 3;

	case SPRING:
		return 1;
	}
}

int Settings::lost_energy_by_step() {
	switch (this->current_season) {

	case SUMMER:
		return -3;

	case AUTUMN:
		return -5;

	case WINTER:
		return -8;

	case SPRING:
		return -5;
	}
}

int Settings::energy_by_photosynthesis() {
	switch (this->current_season) {

	case SUMMER: 
		return 4;

	case AUTUMN:
		return 2;

	case WINTER:
		return 0;

	case SPRING:
		return 3;
	}
}

int Settings::requariable_count_minerals_for_swap(vector<int> live_bots, Matrix<Entity*> matr) {
	int sum_minerals = 0, count = 0;

	for (int i = 0; i < live_bots.size(); ++i) {

		if (matr(live_bots[i])->is_bot()) {

			sum_minerals += ((Bot*)matr(live_bots[i]))->get_minerals();
			++count;
		}
	}

	sum_minerals /= count;
	return sum_minerals;
}

int Settings::count_minerals(int deep) {

	if (deep > size_environment - 7)
		return 4;

	else {

		if (deep > size_environment - 16)
			return 3;

		else {

			if (deep > size_environment - 30)
				return 1;

			else
				return 0;
		}
	}
}