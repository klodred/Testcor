#pragma once
#include "Environment.h"
#include "Command.h"
#include <algorithm>
#include "Settings.h"
#include <iostream>
#include <fstream>
#include <ios>
#include <map>

class World {
private:
	Settings settings;
	Environment environment;
	int time;
	map<string, Command*> command_map;

public:
	World() { settings = Settings(); environment = Environment(); };

	World(Settings _settings) {
		//cout << &this->environment << "\n";
		settings = _settings; 
		environment = Environment(settings.get_size()); 

		environment.populate(settings.count_bots, settings.start_energy, settings.size_genome);
		environment.generation_health(settings.count_heal());
		environment.generation_poison(settings.count_poison());
		environment.generation_wall(settings.count_wall());
		time = 0;

		command_map[get_command_name(LOOK - 1)] = create_command(LOOK - 1);
		command_map[get_command_name(CONVERT_TO_FOOD - 1)] = create_command(CONVERT_TO_FOOD - 1);
		command_map[get_command_name(STEAL - 1)] = create_command(STEAL - 1);
		command_map[get_command_name(PHOTOSYNTHESIS - 1)] = create_command(PHOTOSYNTHESIS - 1);
		command_map[get_command_name(MOVE - 1)] = create_command(MOVE - 1);
		command_map[get_command_name(EAT - 1)] = create_command(EAT - 1);
		command_map[get_command_name(COPY - 1)] = create_command(COPY - 1);
		command_map[get_command_name(SWAP_MINERALS - 1)] = create_command(SWAP_MINERALS - 1);
		command_map[get_command_name(EAT_BOT - 1)] = create_command(EAT_BOT - 1);
		command_map[get_command_name(CHECK_ENERGY - 1)] = create_command(CHECK_ENERGY - 1);
		command_map[get_command_name(CYCLIC_MOVE - 1)] = create_command(CYCLIC_MOVE - 1);
	}

	virtual Command* create_command(int index);

	void set_size(int size) { settings.set_size(size); };

	void set_count_bots(int count) { settings.set_count_bots(count); };

	void iteration_world();

	Matrix<Entity*> get_matrix() const { return environment.get_matrix(); };

	int size() const { return this->environment.size(); };

	Settings get_settings() const { return settings; }; // ?

	Settings* get_ptr_settings() { return &settings; };

	void change_season();

	void save(std::ofstream& fout) const;

	void load(std::istream& fcin);

	//int get_count_live_bots() { return environment.get_count_live_bots() - environment.get_count_die_bots(); };

	int get_count_sun_bot() { return environment.get_access_to_statistics()->count_sun_bots; };

	int get_count_meat_bot() { return environment.get_access_to_statistics()->count_meat_bots; };

	int get_count_minerals_bot() { return environment.get_access_to_statistics()->count_minerals_bots; };

	int get_count_mixed_bot() { return environment.get_access_to_statistics()->count_mixed_bots; };

	int get_count_health() { return environment.get_access_to_statistics()->count_health; };

	int get_count_poison() { return environment.get_access_to_statistics()->count_poison; };

	int get_count_wall() { return environment.get_access_to_statistics()->count_wall; };

	int get_count_bot() { return environment.get_access_to_statistics()->count_bots; };

	void set_time_iteration(int _time) { settings.time_iteration = _time; };

	void set_time_resource(int _time) { settings.time_for_generation_resource = _time; };

	int get_time() const { return time; };
};





