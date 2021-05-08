#pragma once
#include "Environment.h"
#include "Command.h"
#include <algorithm>
#include "Settings.h"

class World {
private:
	Settings settings;
	Environment environment;
	Command command;
	int time;

public:

	//World(int size, int count) : settings(size, count), environment(size) { this->environment.populate(count); };

	//World(Settings _settings) : settings(_settings), environment(settings.get_size()), command(&environment) { this->environment.populate(settings.get_count_bots()); };
	World(Settings _settings) {
		cout << &this->environment << "\n";
		settings = _settings; 
		environment = Environment(settings.get_size()); 
		command = Command(&environment, &settings);
		this->environment.populate(settings.get_count_bots());
		time = 0;
		
	}

	void set_size(int size) { settings.set_size(size); };

	void set_count_bots(int count) { settings.set_count_bots(count); };

	void iteration_world();

	Matrix<Entity*> get_matrix() const { return environment.get_matrix(); };

	int size() const { return this->environment.size(); };
};





