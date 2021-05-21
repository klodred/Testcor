#pragma once
#include "Environment.h"
#include "Settings.h"

/*
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

	void cyclic_move(int i, int j, int step);

	std::pair<int, int> process_direction(int i, int j, int direction);
};
*/

class Command {
protected:
	Environment* environment;
	Settings* settings;
	std::pair<int, int> process_direction(int i, int j, int direction) const;

public:
	Command(Environment* envir, Settings* _settings) : environment(envir), settings(_settings) {};

	Command() {};

	virtual void execute(int i, int j) = 0;
};

class LookCommand : public Command {
public:
	LookCommand(Environment* envir, Settings* _settings) : Command(envir, _settings) {};

	virtual void execute(int i, int j);
};

class ConvertToFoodCommand : public Command {
public:
	ConvertToFoodCommand(Environment* envir, Settings* _settings) : Command(envir, _settings) {};

	virtual void execute(int i, int j);
};

class StealCommand : public Command {
public:
	StealCommand(Environment* envir, Settings* _settings) : Command(envir, _settings) {};

	virtual void execute(int i, int j);
};

class PhotosynthesisCommand : public Command {
public:
	PhotosynthesisCommand(Environment* envir, Settings* _settings) : Command(envir, _settings) {};

	virtual void execute(int i, int j);
};

class MoveCommand : public Command {
public:
	MoveCommand(Environment* envir, Settings* _settings) : Command(envir, _settings) {};

	virtual void execute(int i, int j);
};

class EatCommand : public Command {
public:
	EatCommand(Environment* envir, Settings* _settings) : Command(envir, _settings) {};

	virtual void execute(int i, int j);
};

class CopyCommand : public Command {
public:
	CopyCommand(Environment* envir, Settings* _settings) : Command(envir, _settings) {};

	virtual void execute(int i, int j);
};

class SwapMineralsCommand : public Command {
public:
	SwapMineralsCommand(Environment* envir, Settings* _settings) : Command(envir, _settings) {};

	virtual void execute(int i, int j);
};

class EatBotCommand : public Command {
public:
	EatBotCommand(Environment* envir, Settings* _settings) : Command(envir, _settings) {};

	virtual void execute(int i, int j);
};

class CheckEnergyCommand : public Command {
public:
	CheckEnergyCommand(Environment* envir, Settings* _settings) : Command(envir, _settings) {};

	virtual void execute(int i, int j);
};

class CyclicMoveCommand : public Command {
private:
	int step;

public:
	CyclicMoveCommand(Environment* envir, Settings* _settings, int s) : Command(envir, _settings), step(s) {};

	virtual void execute(int i, int j);
};


