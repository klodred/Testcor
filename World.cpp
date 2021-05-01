#include "World.h"

void Environment::populate(int count) {
	int c = 0; 

	while (c < count) {

		Bot* bot = new Bot;
		int i = rand() % this->matrix.size_m();
		int j = rand() % this->matrix.size_n();

		if (this->matrix(i, j)->can_be_step()) {

			this->matrix(i, j) = bot;
			++c;
			this->live_bots.push_back({ i, j });
		}
	}
}

void World::iteration_world() {
	int count = this->environment.get_current_count_bots();

	//for (int i = 0; i < count; ++i) {

		//this->environment.get_entity(this->environment.get_live_bots()[i].i, this->environment.get_live_bots()[i].j);
		//todo bots do method
	//}
}

void Environment::step(int i, int j) {
	int index_move = ((Bot*)matrix(i, j))->get_index_move();
	int current_move = ((Bot*)matrix(i, j))->get_genome()(index_move);

	if (current_move < 6) {

	
	}
}

void Environment::look(int i, int j) {
	Matrix<int> genome = ((Bot*)matrix(i, j))->get_genome();
	int direction = genome.value_next_cell(i, j);
}

std::pair<int, int> Environment::process_direction(int i, int j, int direction) {
	
	switch (direction) {

	case 1: 
		return { i, (j + 1) % matrix.size_n() };

	case 2:

	case 3:
		return { (i + 1) % matrix.size_m(), j };

	case 4:

	case 5:
		return { i, (j - 1) };


	}
}


