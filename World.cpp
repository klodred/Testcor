#include "World.h"

void World::iteration_world() {
	int count = this->environment.get_current_count_bots();
	int i = 0;
	vector<int>* live_bots = this->environment.get_accses_to_live_bots();

	while (i < live_bots->size()) { // ? если сделать a = environment.get_accses_to_live_bots, у а будет доступ на прямую к ним?
	    
		std::pair<int, int> coordinates = environment.get_matrix().two_dimensional_index((*live_bots)[i]);
		this->command.process_command(coordinates.first, coordinates.second);
	}
}


