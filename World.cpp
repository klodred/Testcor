#include "World.h"

void World::iteration_world() {

	int count = this->environment.get_count_live_bots();
	vector<int>* live_bots = this->environment.get_accses_to_live_bots();

	for (int i = 0; i < count; ++i) {

		std::pair<int, int> coordinates = environment.get_matrix().two_dimensional_index((*live_bots)[i]);
		int one_dim = environment.get_matrix().one_dimensional_index(coordinates.first, coordinates.second);

		if (!environment.get_access_to_bot({ coordinates.first, coordinates.second })->is_die()) {

			if (DEBUG) {
				if (environment.get_matrix()(one_dim)->is_bot())
					cout << "��� ���\n";
				else
					cout << "��� �� ���\n";
				cout << "������� ���� \n" << "���������� : " << one_dim << "\n��������� " << coordinates.first << ", " << coordinates.second << "\n";
				cout << "�����\n";
				Matrix<int> genome = environment.get_access_to_bot(coordinates)->get_genome();
				cout << genome << "\n";
			}

			this->command.process_command(coordinates.first, coordinates.second);
			coordinates = environment.get_matrix().two_dimensional_index((*live_bots)[i]);

			if (environment.get_access_to_bot({ coordinates.first, coordinates.second })->is_die()) {
				
				if (DEBUG) {
					cout << "��� ����\n";
				}
				environment.kill_bot(coordinates.first, coordinates.second);
			}
		}
	}

	sort(live_bots->begin(), live_bots->end());

	if (this->environment.get_count_die_bots() != 0) {

		this->environment.erase_die_bots();
	}

	time++;

	
	if (this->time % settings.time_for_generation_resource == 0) {

		environment.generation_health(settings.count_heal());
		environment.generation_poison(settings.count_poison());
		environment.generation_wall(settings.count_wall());
	}
}


