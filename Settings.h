#pragma once
#include "Entity.h"
static const int ENVIRONMENT_HEIGHT = 60, ENVIRONMENT_WIDTH = 60;

class Settings {
	public:
	int size_environment;
	int count_bots;
	int start_energy;
	enum season { SUMMER = 100, AUTUMN = SUMMER + 100, SPRING = AUTUMN + 100, WINTER = SPRING + 100 };
	int lost_energy_by_steal = -4, lost_energy_by_convert_to_food = -2, lost_energy_by_swap_minerals = -10;;
	int energy_from_mineral = 3;
	int index_step_by_steal = 2, index_step_by_convert_to_food = 4, index_step_by_photosynthesis = 3;
	int index_step_by_swap_minerals = 2;
	int current_season = SUMMER;

	Settings() { size_environment = ENVIRONMENT_HEIGHT; count_bots = 8; start_energy = 10; };

	Settings(int size, int count) : size_environment(size), count_bots(count) {};

	int get_size() { return size_environment; };

	void set_size(int size) { size_environment = size; };

	int get_count_bots() { return count_bots; };

	void set_count_bots(int count) { count_bots = count; };


	int direction_identifier(Entity* entity);


	int stolen_energy(int energy_victim) { return energy_victim / 4; };

	int energy_by_photosynthesis();

	int lost_energy_by_step();

	int index_step();

	int index_step_by_look(Entity* entity) { return this->direction_identifier(entity); };

	int index_step_by_move(Entity* entity) { return this->direction_identifier(entity); };

	int index_step_by_eat(Entity* entity) { return this->direction_identifier(entity); };

	int count_minerals_for_swap(vector<int> live_bots, Matrix<Entity*> matr);

	int index_step_by_swap_minerals(int minerals) { return minerals % 24; };
};
