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

	int index = matrix.one_dimensional_index(i, j);
	vector<int>::iterator pos = upper_bound(die_bots.begin(), die_bots.end(), index);
	die_bots.insert(pos, index);
	this->clear(i, j);
}

void Environment::set_entity(std::pair<int, int> coordinates, Entity* entity) {
	this->matrix(coordinates.first, coordinates.second) = entity;
}

Bot* Environment::get_access_to_bot(std::pair<int, int> coordinatis) {
	return (Bot*)(*this->get_access_to_matrix())(coordinatis.first, coordinatis.second);
}

void Environment::erase_die_bots() {
	int pos_for_search = 0;

	for (int i = 0; i < die_bots.size(); ++i) {

        int pos_for_erase = find(live_bots.begin() + pos_for_search, live_bots.end(), die_bots[i]) - live_bots.begin();
			//vector<int>::iterator pos_for_erase = find(pos_for_search, live_bots.end(), die_bots[i]);
	    live_bots.erase(live_bots.begin() + pos_for_erase);
		pos_for_search = pos_for_erase;
	}

	die_bots.clear();
}

void Environment::set_index_in_live_bots(std::pair <int, int> coord, std::pair<int, int> new_coord) {
	int one_dimen_old = matrix.one_dimensional_index(coord.first, coord.second);
	vector<int>::iterator pos = find(live_bots.begin(), live_bots.end(), one_dimen_old);
	live_bots[pos - live_bots.begin()] = matrix.one_dimensional_index(new_coord.first, new_coord.second);;
};
