#include "Environment.h"

void Environment::populate(int count) {
	int c = 0;

	while (c < count) {

		Bot* bot = new Bot;
		int i = rand() % this->matrix.size_m();
		int j = rand() % this->matrix.size_n();

		if (this->matrix(i, j)->can_be_step()) {

			this->matrix(i, j) = bot;
			++c;

			int index = matrix.one_dimensional_index(i, j);
			vector<int>::iterator pos = upper_bound(live_bots.begin(), live_bots.end(), index);
			this->live_bots.insert(pos, index);
		}
	}
}

void Environment::kill_bot(int i, int j) {
	//int index = matrix.one_dimensional_index(i, j);
	//vector<int>::iterator pos = find(live_bots.begin(), live_bots.end(), index);
	//live_bots.erase(pos);
	matrix(i, j) = new EmptyEntity();
}

void Environment::set_entity(std::pair<int, int> coordinates, Entity* entity) {
	this->matrix(coordinates.first, coordinates.second) = entity;
}

Bot* Environment::get_access_to_bot(std::pair<int, int> coordinatis) {
	return (Bot*)(*this->get_access_to_matrix())(coordinatis.first, coordinatis.second);
}

void Environment::erase_die_bots() {
	vector<int>::iterator pos_for_search = live_bots.begin();

	for (int i = 0; i < die_bots.size(); ++i) {

			vector<int>::iterator pos_for_erase = find(pos_for_search, live_bots.end(), die_bots[i]);
			live_bots.erase(pos_for_erase);
			pos_for_search = pos_for_erase;
	}

	die_bots.clear();
}
