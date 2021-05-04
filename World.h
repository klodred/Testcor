#pragma once
#include "Environment.h"
#include "Command.h"
#include <algorithm>

static const int ENVIRONMENT_HEIGHT = 60, ENVIRONMENT_WIDTH = 60;

class Settings {
private:
	int size_environment;
	int count_bots;
	int start_energy;

public:
	Settings() { size_environment = ENVIRONMENT_HEIGHT; count_bots = 8; start_energy = 10; };

	Settings(int size, int count) : size_environment(size), count_bots(count) {};

	int get_size() { return size_environment; };

	void set_size(int size) { size_environment = size; };

	int get_count_bots() { return count_bots; };

	void set_count_bots(int count) { count_bots = count; };
};


class World {
private:
	Settings settings;
	Environment environment;
	Command command;
	//int time;

public:

	//World(int size, int count) : settings(size, count), environment(size) { this->environment.populate(count); };

	//World(Settings _settings) : settings(_settings), environment(settings.get_size()), command(&environment) { this->environment.populate(settings.get_count_bots()); };
	World(Settings _settings) {
		settings = _settings; 
		environment = Environment(settings.get_size()); 
		command = Command(&environment);
		this->environment.populate(settings.get_count_bots());
	};

	void set_size(int size) { settings.set_size(size); };

	void set_count_bots(int count) { settings.set_count_bots(count); };

	void iteration_world();

	Matrix<Entity*> get_matrix() const { return environment.get_matrix(); };

	int size() const { return this->environment.size(); };
};





