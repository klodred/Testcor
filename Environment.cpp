#include "Environment.h"

void Environment::populate(int count, int energy, int size_genome) {
	int c = 0;

	while (c < count) {

		Bot* bot = new Bot(energy, size_genome);
		statistics.update_bot(*bot);
		int pos = rand() % this->matrix.size();

		if (this->matrix(pos)->can_be_step()) {

			this->matrix(pos) = bot;
			++c;
			this->live_bots.push_back(pos);
		}
	}
}

void Environment::kill_bot(int i, int j) {

	int index = matrix.one_dimensional_index(i, j);
	this->get_access_to_bot({ i, j })->set_energy(0);
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
		try {
			live_bots.erase(live_bots.begin() + pos_for_erase);
		}
		catch (...) {

			// skip

		}
		pos_for_search = pos_for_erase;
	}

	die_bots.clear();
}

void Environment::set_index_in_live_bots(std::pair <int, int> coord, std::pair<int, int> new_coord) {
	int one_dimen_old = matrix.one_dimensional_index(coord.first, coord.second);
	vector<int>::iterator pos = find(live_bots.begin(), live_bots.end(), one_dimen_old);
	live_bots[pos - live_bots.begin()] = matrix.one_dimensional_index(new_coord.first, new_coord.second);;
};

std::pair<int, int> Environment::nearest_empty_cell(int i, int j) {
	bool flag = false;
	int k = 0;
	int m = matrix.size_m();
	int n = matrix.size_n();

	while (k < m) {

		for (int counter_i = 0, i_dir = i - 1; counter_i < 3 + k; ++counter_i, ++i_dir) {

			for (int counter_j = 0, j_dir = j - 1; counter_j < 3 + k; ++counter_j, ++j_dir) {

				if (matrix.cell_is_exist((i_dir + m) % m, (j_dir + n) % n)) {

					if (matrix((i_dir + m) % m, (j_dir + n) % n)->is_empty()) {

						return { (i_dir + m) % m, (j_dir + n) % n };
					}
				}
			}
		}

		++k;
		--i;
		--j;
	}
	throw 2;
}

void Environment::generation_wall(int count) {
	statistics.count_wall += count;

	while (count > 0) {

		int pos = rand() % (matrix.size_m() * matrix.size_n());

		if (matrix(pos)->is_empty()) {

			matrix(pos) = new Wall;
			--count;
		}
	}
}

void Environment::generation_health(int count) {
	statistics.count_health += count;

	while (count > 0) {

		int pos = rand() % (matrix.size_m() * matrix.size_n());

		if (matrix(pos)->is_empty()) {

			Health* h = new Health(generation_health());
			matrix(pos) = h;
			--count;
		}
	}
}

void Environment::generation_poison(int count) {
	statistics.count_poison += count;

	while (count > 0) {

		int pos = rand() % (matrix.size_m() * matrix.size_n());

		if (matrix(pos)->is_empty()) {

			Poison* h = new Poison(generation_poison());
			matrix(pos) = h;
			--count;
		}
	}
}
