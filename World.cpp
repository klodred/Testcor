#include "World.h"
#include <chrono>

void World::iteration_world() {
	vector<int>* live_bots = this->environment.get_accses_to_live_bots();
	vector<int>* die_bots = this->environment.get_accses_to_die_bots();
	int count = live_bots->size();

	std::chrono::system_clock::time_point start;
	if (DEBUG_TIME) {
		start = std::chrono::system_clock::now();

	}

	for (int i = 0; i < count; ++i) {

		std::pair<int, int> coor = environment.get_matrix().two_dimensional_index((*live_bots)[i]);
		int one_dim = environment.get_matrix().one_dimensional_index(coor.first, coor.second);

		if ((environment.get_matrix()(one_dim)->is_bot()) && (!environment.get_access_to_bot({ coor.first, coor.second })->is_die())) {

			if (DEBUG) {
				if (environment.get_matrix()(one_dim)->is_bot())
					cout << "это бот\n";
				else
					cout << "это не бот\n";
				cout << "»ндексы бота \n" << "одномерный : " << one_dim << "\nдвумерный " << coor.first << ", " << coor.second << "\n";
				cout << "√еном\n";
				cout << "Ёнерги€ " << ((Bot*)environment.get_matrix()(one_dim))->get_energy() << "\n";
				vector<int> genome = environment.get_access_to_bot(coor)->get_genome();
				//cout << genome << "\n";
			}

			int index_command = ((Bot*)environment.get_matrix()(one_dim))->get_current_gen();
			Command* command = command_map[get_command_name(index_command)];
			coor = environment.get_matrix().two_dimensional_index((*live_bots)[i]);
			environment.get_access_to_bot({ coor.first, coor.second })->enlarge_minerals(settings.count_minerals(coor.first));
			command->execute(coor.first, coor.second);
			coor = environment.get_matrix().two_dimensional_index((*live_bots)[i]);

			if (environment.get_access_to_bot({ coor.first, coor.second })->is_die()) {
				
				//environment.get_access_to_statistics()->update_bot(environment.get_bot(coor.first, coor.second));

				if (DEBUG) {
					cout << "бот умер\n";
				}
				environment.kill_bot(coor.first, coor.second);
			}
		}
	}

	if (DEBUG_TIME) {


		auto end = std::chrono::system_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		std::cout << "Time for processing world: " << elapsed.count() << " ms" << std::endl;

	}

	sort(live_bots->begin(), live_bots->end());

	if (this->environment.get_count_die_bots() != 0) {

		this->environment.erase_die_bots();
	}

	for (int i = 0; i < live_bots->size(); ++i) {

		auto coor = environment.get_matrix().two_dimensional_index((*live_bots)[i]);
		if (environment.get_access_to_bot({ coor.first, coor.second })->is_die()) {

			if (DEBUG) {
				cout << "бот умер\n";
			}
			environment.kill_bot(coor.first, coor.second);

		}

	}

	if (this->environment.get_count_die_bots() != 0) {

		this->environment.erase_die_bots();
	}

	Statistics* s = environment.get_access_to_statistics();
	s->count_bots = 0;
	s->count_sun_bots = 0;
	s->count_meat_bots = 0;
	s->count_minerals_bots = 0;
	s->count_mixed_bots = 0;
	for (int i = 0; i < live_bots->size(); ++i) {

		auto coor = environment.get_matrix().two_dimensional_index((*live_bots)[i]);
		environment.get_access_to_statistics()->update_bot(environment.get_bot(coor.first, coor.second));

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
	fout << settings.time_iteration << "\n\n";

	fout << live_bots.size() << "\n";
	fout << time << "\n";
	fout << "\n";

	for (int i = 0; i < live_bots.size(); ++i) {

		fout << live_bots[i] << "\n";
		fout << ((Bot*)matr(live_bots[i]))->get_energy() << "\n";
		fout << ((Bot*)matr(live_bots[i]))->get_minerals() << "\n";
		fout << ((Bot*)matr(live_bots[i]))->get_index_step() << "\n";

		vector<int> genome = ((Bot*)matr(live_bots[i]))->get_genome();

		for (int j = 0; j < settings.size_genome; ++j)
			fout << genome[j] << " ";

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
	fcin >> settings.size_environment;
	environment = Environment(settings.size_environment);
	Matrix<Entity*>* matr = environment.get_access_to_matrix();

	fcin >> settings.size_genome;
	fcin >> settings.time_iteration;

	int count;
	fcin >> count;
	environment.get_accses_to_live_bots()->resize(count);

	fcin >> this->time;

	for (int i = 0; i < live_bots->size(); ++i) {

		fcin >> (*live_bots)[i];
		Bot* bot = new Bot;
		int energy;
		fcin >> energy;
		bot->set_energy(energy);

		fcin >> energy;
		bot->set_minerals(energy);

		//((Bot*)(*matr)((*live_bots)[i]))->set_minerals(energy);
		int index;
		fcin >> index;
		bot->set_index_step(index);
		

		vector<int> genome(settings.size_genome);

		for (int j = 0; j < settings.size_genome; ++j)
			fcin >> genome[j];

		bot->set_genome(genome);

		environment.set_entity((*live_bots)[i], bot);
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


Command* World::create_command(int step) {
	if (DEBUG) {
		cout << "команда " << step << "\n";
	}

	if (step < LOOK)
		return new LookCommand(&environment, &settings);

	else {

		if (step < CONVERT_TO_FOOD)
			return new ConvertToFoodCommand(&environment, &settings);

		else {

			if (step < STEAL)
				return new StealCommand(&environment, &settings);

			else {

				if (step < PHOTOSYNTHESIS)
					return new PhotosynthesisCommand(&environment, &settings);

				else {

					if (step < MOVE)
						return new MoveCommand(&environment, &settings);

					else {

						if (step < EAT)
							return new EatCommand(&environment, &settings);

						else {

							if (step < COPY)
								return new CopyCommand(&environment, &settings);

							else {

								if (step < SWAP_MINERALS)
									return new SwapMineralsCommand(&environment, &settings);

								else {

									if (step < EAT_BOT)
										return new EatBotCommand(&environment, &settings);

									else {

										if (step < CHECK_ENERGY)
											return new CheckEnergyCommand(&environment, &settings);

										else {

											if (step < CYCLIC_MOVE)
												return new CyclicMoveCommand(&environment, &settings, step);
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}