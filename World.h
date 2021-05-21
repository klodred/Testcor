#pragma once
#include "Environment.h"
#include "Command.h"
#include <algorithm>
#include "Settings.h"
#include <iostream>
#include <fstream>
#include <ios>

class World {
private:
	Settings settings;
	Environment environment;
	int time;

public:
	World() { settings = Settings(); environment = Environment(); };

	World(Settings _settings) {
		cout << &this->environment << "\n";
		settings = _settings; 
		environment = Environment(settings.get_size()); 

		environment.populate(settings.get_count_bots());
		environment.generation_health(settings.count_heal());
		environment.generation_poison(settings.count_poison());
		environment.generation_wall(settings.count_wall());
		time = 0;
	}

	virtual Command* create_command(int index);

	void set_size(int size) { settings.set_size(size); };

	void set_count_bots(int count) { settings.set_count_bots(count); };

	void iteration_world();

	Matrix<Entity*> get_matrix() const { return environment.get_matrix(); };

	int size() const { return this->environment.size(); };

	Settings get_settings() const { return settings; }; // ?

	void change_season();

	void save(std::ofstream& fout) const;

	void load(std::istream& fcin);
};





