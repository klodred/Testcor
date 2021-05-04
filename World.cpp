#include "World.h"

void World::iteration_world() {
	int count = this->environment.get_current_count_bots();
	vector<int>* live_bots = this->environment.get_accses_to_live_bots();

	//while (i < live_bots->size()) { // ? если сделать a = environment.get_accses_to_live_bots, у а будет доступ на прямую к ним?
	    
	for (int i = 0; i < count; ++i) {

		std::pair<int, int> coordinates = environment.get_matrix().two_dimensional_index((*live_bots)[i]);
		int one_dim = environment.get_matrix().one_dimensional_index(coordinates.first, coordinates.second);
		if (!environment.get_access_to_bot({ coordinates.first, coordinates.second })->is_die()) {

			this->command.process_command(coordinates.first, coordinates.second);
		}
	}

	sort(live_bots->begin(), live_bots->end());

	if (this->environment.get_count_die_bots() != 0) {

		this->environment.erase_die_bots();
	}
}


