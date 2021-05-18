#pragma once
#include "Entity.h"
static const int ENVIRONMENT_HEIGHT = 60, ENVIRONMENT_WIDTH = 60;
static const int DEBUG = 0;

class Settings {
	public:
	int size_environment = 60;
	int size_genome = 64;
	int time_iteration;
	int count_bots;
	int start_energy;
	enum season { SUMMER = 10, AUTUMN = SUMMER + 10, SPRING = AUTUMN + 10, WINTER = SPRING + 10 };

	int lost_energy_by_steal = -4, lost_energy_by_convert_to_food = -2, lost_energy_by_swap_minerals = -10;
	int lost_energy_by_eat_bot = -5;

	int energy_from_mineral = 3;

	int bias_const = 42;

	int index_step_by_steal = 2, index_step_by_convert_to_food = 4;
	int index_step_greater_than_bias = 4, index_step_lower_than_bias = 2, index_step_by_copy = 5;

	double chance_mutation = 0.25;

	int time_for_generation_resource = 100;

	int set_time_iteration(int time) { time_iteration = time; }

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

	int energy_by_copy(int energy) { return energy / 4; };

	int minerals_by_copy(int energy) { return energy / 4; };

	int energy_by_eat_bot(int energy) const { return energy; };

	int lost_energy_by_step();

	int index_step();

	int index_step_by_look(Entity* entity) { return this->direction_identifier(entity); };

	int index_step_by_move(Entity* entity) { return this->direction_identifier(entity); };

	int index_step_by_eat(Entity* entity) { return this->direction_identifier(entity); };

	int requariable_count_minerals_for_swap(vector<int> live_bots, Matrix<Entity*> matr);

	int index_step_by_swap_minerals(int minerals) { return minerals % 24; };

	int index_step_by_eat_bot(Entity* entity) { return  this->direction_identifier(entity); };

	int count_wall() { return rand() % (size_environment / 40 * size_environment); };

	int count_poison() { return rand() % (size_environment / 40 * size_environment); };

	int count_heal() { return rand() % (size_environment / 40 * size_environment); };

	int index_step_by_photosynthesis(int energy) { return energy % 10; };

};
