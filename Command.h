#pragma once
#include "Environment.h"
#include "Settings.h"

static int LOSSES = 10;
enum commands { LOOK = 6, CONVERT_TO_FOOD = 11, STEAL = 15, PHOTOSYNTHESIS = 19, MOVE = 25, EAT = 29, COPY =  32, 
	SWAP_MINERALS = 35, EAT_BOT = 37, CHECK_ENERGY = 40};
static int MINERALS = 10;

class Command {
private:
	Environment* environment;
	Settings* settings;

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

	std::pair<int, int> process_direction(int i, int j, int direction);
};
