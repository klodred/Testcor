#include "World.h"

void World::iteration_world() {

	int current_bot = environment.get_index_current_bot_from_live_bots();
	int count = this->environment.get_count_live_bots();
	vector<int>* live_bots = this->environment.get_accses_to_live_bots();
	int i;

	for (i = current_bot; i < count; ++i) {

		std::pair<int, int> coordinates = environment.get_matrix().two_dimensional_index((*live_bots)[i]);
		int one_dim = environment.get_matrix().one_dimensional_index(coordinates.first, coordinates.second);

		if (!environment.get_access_to_bot({ coordinates.first, coordinates.second })->is_die()) {

			if (DEBUG) {
				if (environment.get_matrix()(one_dim)->is_bot())
					cout << "это бот\n";
				else
					cout << "это не бот\n";
				cout << "»ндексы бота \n" << "одномерный : " << one_dim << "\nдвумерный " << coordinates.first << ", " << coordinates.second << "\n";
				cout << "√еном\n";
				cout << "Ёнерги€ " << ((Bot*)environment.get_matrix()(one_dim))->get_energy() << "\n";
				Matrix<int> genome = environment.get_access_to_bot(coordinates)->get_genome();
				cout << genome << "\n";
			}

			this->command.process_command(coordinates.first, coordinates.second);
			coordinates = environment.get_matrix().two_dimensional_index((*live_bots)[i]);

			if (environment.get_access_to_bot({ coordinates.first, coordinates.second })->is_die()) {
				
				if (DEBUG) {
					cout << "бот умер\n";
				}
				environment.kill_bot(coordinates.first, coordinates.second);
			}
		}
	}

	environment.set_index_current_bot_from_live_bots(i % count);
	//std::string file_name = "write.txt";
	//std::ofstream fout;
	//fout.open(file_name);
	//this->save(fout);
	//exit(0);
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

	this->change_season();
}

void World::change_season() {
	int ost = this->time % settings.WINTER;

	if (ost / settings.SUMMER == 0)
		settings.current_season = settings.SUMMER;

	else {

		if (ost / settings.AUTUMN == 0)
			settings.current_season = settings.AUTUMN;

		else {

			if (ost / settings.SPRING == 0)
				settings.current_season = settings.SPRING;

			else {

				if (ost / settings.WINTER == 0)
					settings.current_season = settings.WINTER;
			}
		}
	}
}

void World::save(std::ofstream& fout) const {
	vector<int> live_bots = environment.get_live_bots();
	Matrix<Entity*> matr = environment.get_matrix();
	fout << settings.size_environment << "\n";
	fout << settings.size_genome << "\n";
	fout << settings.time_iteration << "\n";
	fout << live_bots.size() << "\n";
	fout << time << "\n";
	fout << environment.get_index_current_bot_from_live_bots() << "\n\n";

	for (int i = 0; i < live_bots.size(); ++i) {

		fout << live_bots[i] << "\n";
		fout << ((Bot*)matr(live_bots[i]))->get_energy() << "\n";
		fout << ((Bot*)matr(live_bots[i]))->get_minerals() << "\n";
		fout << ((Bot*)matr(live_bots[i]))->get_index_step() << "\n";

		Matrix<int> genome = ((Bot*)matr(live_bots[i]))->get_genome();

		for (int j = 0; j < settings.size_genome; ++j)
			fout << genome(j) << " ";

		fout << "\n\n";
	}

	std::ios::pos_type pos = fout.tellp();
	fout << "\n\n\n";
	int count = 0;

	for (int i = 0; i < settings.size_environment * settings.size_environment; ++i) {

		if (!matr(i)->is_empty()) {

			if (matr(i)->is_health() or matr(i)->is_poison()) {

				fout << i << "\n" << ((Nutrition*)matr(i))->get_heal() << "\n\n";
				++count;
			}

			else {

				if (matr(i)->is_wall()) {

					fout << i << "\n" << 0 << "\n\n";
					++count;
				}
			}
		}
	}

	fout.seekp(pos);
	fout << count;
}

void World::load(std::istream& fcin) {
	vector<int>* live_bots = environment.get_accses_to_live_bots();
	Matrix<Entity*>* matr = environment.get_access_to_matrix();
	fcin >> settings.size_environment;
	matr->resize(settings.size_environment, settings.size_environment);

	fcin >> settings.size_genome;
	fcin >> settings.time_iteration;

	int count;
	fcin >> count;

	live_bots->resize(count);

	fcin >> time;

	int index;
	fcin >> index;
	environment.set_index_current_bot_from_live_bots(index);

	for (int i = 0; i < live_bots->size(); ++i) {

		fcin >> (*live_bots)[i];

		int energy;
		fcin >> energy;
		((Bot*)(*matr)((*live_bots)[i]))->set_energy(energy);

		fcin >> energy;
		((Bot*)(*matr)((*live_bots)[i]))->set_minerals(energy);

		fcin >> index;
		((Bot*)(*matr)((*live_bots)[i]))->set_index_step(index);

		vector<int> genome(settings.size_genome);

		for (int j = 0; j < settings.size_genome; ++j)
			fcin >> genome[j];
	}

	int count_resource, pos, damage;
	fcin >> count_resource;

	for (int i = 0; i < count_resource; ++i) {

		fcin >> pos;
		fcin >> damage;

		if (damage > 0)
			environment.set_entity(pos, new Health(damage));

		else {

			if (damage < 0)
				environment.set_entity(pos, new Poison(damage));

			else
				environment.set_entity(pos, new Wall());
		}
	}
}


