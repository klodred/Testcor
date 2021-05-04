#pragma once
#include "Entity.h"

class Environment {
private:
	Matrix<Entity*> matrix;
	vector<int> live_bots;
	vector<int> die_bots;

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

	int get_count_die_bots() const { return this->die_bots.size(); };

	Entity*& get_entity(int i, int j) { return matrix(i, j); };

	void set_index_in_live_bots(vector<int>::iterator pos, int index) { live_bots[pos - live_bots.begin()] = index; };

	vector<int> get_live_bots() const { return live_bots; };

	vector<int> get_die_bots() const { return die_bots; };

	vector<int>::iterator find_index_in_live_bots(int index) { return find(live_bots.begin(), live_bots.end(), index); };

	int size() const { return matrix.size_n(); };

	void set_entity(std::pair<int, int> coordinates, Entity* entity);

	Matrix<Entity*>* get_access_to_matrix() { return &matrix; };

	Bot* get_access_to_bot(std::pair<int, int> coordinatis);

	vector<int>* get_accses_to_live_bots() { return &live_bots; };

	void kill_bot(int i, int j);

	void erase_die_bots();

	void clear(int i, int j) { matrix(i, j) = new EmptyEntity; };
};
