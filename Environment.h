#pragma once
#include "Entity.h"

class Environment {
private:
	Matrix<Entity*> matrix;
	vector<int> live_bots;
	vector<int> die_bots;
	int current_bot;

public:
	Environment() { };

	Environment(int m) {
		matrix.resize(m, m);

		for (int i = 0; i < m; ++i)
			for (int j = 0; j < m; ++j)
				matrix(i, j) = new EmptyEntity();
	};

	void populate(int count);

	Matrix<Entity*> get_matrix() const { return matrix; };

	Bot get_bot(int i, int j) { return *((Bot*)matrix(i, j)); };

	int get_count_live_bots() { return this->live_bots.size(); };

	int get_count_die_bots() const { return this->die_bots.size(); };

	Entity*& get_entity(int i, int j) { return matrix(i, j); };

	void set_index_in_live_bots(std::pair <int, int>, std::pair<int, int>);

	void set_index_in_live_bots(vector<int>::iterator pos, int index) { live_bots[pos - live_bots.begin()] = index; };

	vector<int> get_live_bots() const { return live_bots; };

	vector<int> get_die_bots() const { return die_bots; };

	vector<int>::iterator find_index_in_live_bots(int index) { return find(live_bots.begin(), live_bots.end(), index); };

	int size() const { return matrix.size_n(); };

	void set_entity(std::pair<int, int> coordinates, Entity* entity);

	void set_entity(int pos, Entity* entity) { matrix(pos) = entity; };

	Matrix<Entity*>* get_access_to_matrix() { return &matrix; };

	Bot* get_access_to_bot(std::pair<int, int> coordinatis);

	vector<int>* get_accses_to_live_bots() { return &live_bots; };

	vector<int>* get_accses_to_die_bots() { return &die_bots; };

	void kill_bot(int i, int j);

	void erase_die_bots();

	void clear(int i, int j) { matrix(i, j) = new EmptyEntity; };

	std::pair<int, int> nearest_empty_cell(int i, int j);

	int generation_health() { return 1 + rand() % 5; };

	int generation_poison() { return -(1 + rand() % 5); };

	void generation_wall(int count);

	void generation_health(int count);

	void generation_poison(int count);

	bool is_bot_die(int index) { return find(die_bots.begin(), die_bots.end(), index) != die_bots.end(); };

	int get_current_bot() { return current_bot; };
};
