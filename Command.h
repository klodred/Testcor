#pragma once
#include "Environment.h"

static int LOSSES = 10;
enum commands { LOOK = 6, CONVERT_TO_FOOD = 11, STEAL = 15, PHOTOSYNTHESIS = 19, MOVE = 25 };

class Command {
private:
	Environment* environment;

public:

	Command(Environment* envir) : environment(envir) {};

	Command() {};

	void process_command(int i, int j);

	void look(int i, int j);

	void convert_to_food(int i, int j);

	void steal(int i, int j);

	void photosynthesis(int i, int j); // доделать

	void move(int i, int j);

	std::pair<int, int> process_direction(int i, int j, int direction);

	int direction_identifier(Entity* entity);
};
