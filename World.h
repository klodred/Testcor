#pragma once
#include "Entity.h"
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

class Environment {
private:
	Matrix<Entity*> matrix;
	vector<int> live_bots;

public:
	Environment() { matrix.resize(SIZE_MAX, SIZE_MAX); };

	Environment(int size) { 
		matrix.resize(size, size); 
    
	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j)
			matrix(i, j) = new EmptyEntity();
	};

	void populate(int count);

	Matrix<Entity*> get_matrix() const { return matrix; };

	int get_current_count_bots() { return this->live_bots.size(); };

	Entity*& get_entity(int i, int j) { return matrix(i, j); };

	vector<int> get_live_bots() const { return live_bots; };

	int size() const { return matrix.size_n(); };
	
	void step(int i, int j);

	void set_entity(std::pair<int, int> coordinates, Entity* entity);

	Matrix<Entity*>& get_access_to_matrix() { return matrix; };

	Bot* get_access_to_bot(std::pair<int, int> coordinatis);

	void kill_bot(int i, int j);

	void clear(int i, int j) { matrix(i, j) = new EmptyEntity; };
};


class World {
private:
	Settings settings;
	Environment environment;
	//int time;

public:

	World(int size, int count) : settings(size, count), environment(size) { this->environment.populate(count); };

	World(Settings _settings) : settings(_settings), environment(settings.get_size()) { this->environment.populate(settings.get_count_bots()); };

	void set_size(int size) { settings.set_size(size); };

	void set_count_bots(int count) { settings.set_count_bots(count); };

	void iteration_world();

	Matrix<Entity*> get_matrix() const { return environment.get_matrix(); };

	int size() const { return this->environment.size(); };
};





