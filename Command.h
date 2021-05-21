#pragma once
#include "Environment.h"
#include "Settings.h"

class Command {
private:
	Environment* environment;
	SettingsS* settings;

public:

	Command(Environment* envir, Settings* _settings) : environment(envir), settings(_settings) {};

	Command() {};

	void process_command(int i, int j);

	void look(int i, int j);

	void convert_to_food(int i, int j);

	void steal(int i, int j);

	void photosynthesis(int i, int j); // доделать

	void move(int i, int j);

	void eat(int i, int j);

	void copy(int i, int j);

	void swap_minerals(int i, int j);

	void eat_bot(int i, int j);

	void check_energy(int i, int j);

	void cyclic_move(int i, int j, int step);

	std::pair<int, int> process_direction(int i, int j, int direction);
};
