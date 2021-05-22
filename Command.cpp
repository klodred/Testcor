#include "Command.h"

// разные команды для разного поедания
// и в конструкторе бота
// по содержанию его генома его тип будет записываться в int type

/*
void Command::process_command(int i, int j) {
	Matrix<Entity*>* matr = environment->get_access_to_matrix();
	int index = ((Bot*)(*matr)(i, j))->get_index_step();
	int step = ((Bot*)(*matr)(i, j))->get_genome()[index];
	// if max then copy this
	if (DEBUG) {
		cout << "команда " << step << "\n";
		cout << "индекс команды " << index << "\n";
	}

	if (step < LOOK)
		this->look(i, j);

	else {

		if (step < CONVERT_TO_FOOD)
			this->convert_to_food(i, j);

		else {

			if (step < STEAL)
				this->steal(i, j);

			else {

				if (step < PHOTOSYNTHESIS)
					this->photosynthesis(i, j);

				else {

					if (step < MOVE)
						this->move(i, j);

					else {

						if (step < EAT)
							this->eat(i, j);

						else {

							if (step < COPY)
								this->copy(i, j);

							else {

								if (step < SWAP_MINERALS)
									this->swap_minerals(i, j);

								else {

									if (step < EAT_BOT)
										this->eat_bot(i, j);

									else {

										if (step < CHECK_ENERGY)
											this->check_energy(i, j);

										else {

											if (step < CYCLIC_MOVE)
												this->cyclic_move(i, j, step);
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

void Command::look(int i, int j) {
	Matrix<Entity*> matrix = environment->get_matrix();
	int n = matrix.size_n(), m = matrix.size_m();
	vector<int> genome = ((Bot*)matrix(i, j))->get_genome();
	//int direction = .value_next_cell(i, j) % 8;
	int index = ((Bot*)matrix(i, j))->get_index_step();
	int direction = genome[(index + 1) % genome.size()] % 8;
	std::pair<int, int> coordinates_direction = process_direction(i, j, direction);

	int i_dir = coordinates_direction.first, j_dir = coordinates_direction.second;

	//if (i_dir >= n or j_dir >= m)
		//throw std::out_of_range("Direction_Error");

	if (matrix(i_dir, j_dir)->is_health()) {

		((Bot*)matrix(i, j))->enlarge_energy(((Nutrition*)matrix(i_dir, j_dir))->get_heal());
		environment->set_entity({ i_dir, j_dir }, (Bot*)matrix(i, j));
		environment->set_index_in_live_bots({ i, j }, { i_dir, j_dir });
		environment->clear(i, j);
	}

	((Bot*)matrix(i, j))->enlarge_index_step(settings->index_step_by_look(matrix(i_dir, j_dir)));
	environment->get_access_to_bot({ i, j })->enlarge_energy(settings->lost_energy_by_step());
}
*/
void StealCommand::execute(int i, int j) {
	int n = environment->size(), m = environment->size();
	Matrix<Entity*> matrix = environment->get_matrix();
	bool flag = true;

	for (int counter_i = 0, i_dir = i - 1; counter_i < 3 && flag; ++counter_i, ++i_dir) {

		for (int counter_j = 0, j_dir = j - 1; counter_j < 3; ++counter_j, ++j_dir) {

			if (matrix.cell_is_exist(i_dir, j_dir)) {

				if (matrix(i_dir, j_dir)->is_bot()) {

					if (not(i_dir == i and j_dir == j)) {

						flag = false;
						int energy_victim = ((Bot*)matrix(i_dir, j_dir))->get_energy();
						environment->get_access_to_bot({ i, j })->enlarge_energy(settings->stolen_energy(energy_victim));
						environment->get_access_to_bot({ i, j })->enlarge_energy(settings->lost_energy_by_steal);
						environment->get_access_to_bot({ i_dir, j_dir })->enlarge_energy(-settings->stolen_energy(energy_victim));
						
						if (((Bot*)matrix(i_dir, j_dir))->is_die())
							environment->kill_bot(i_dir, j_dir);

						environment->get_access_to_bot({ i, j })->enlarge_index_step(settings->index_step_by_steal);
						break;
					}
				}
			}
		}
	}

	Bot* a = environment->get_access_to_bot({ i, j });
	environment->get_access_to_bot({ i, j })->enlarge_index_step(settings->index_step());
	environment->get_access_to_bot({ i, j })->enlarge_energy(settings->lost_energy_by_step()); 
}

void ConvertToFoodCommand::execute(int i, int j) {
	int n = environment->size(), m = environment->size();
	Matrix<Entity*> matrix = environment->get_matrix();

	for (int counter_i = 0, i_dir = i - 1; counter_i < 3; ++counter_i, ++i_dir) {

		for (int counter_j = 0, j_dir = j - 1; counter_j < 3; ++counter_j, ++j_dir) {

			if (matrix.cell_is_exist(i_dir, j_dir)) {

				if (matrix(i_dir, j_dir)->is_poison()) {

					environment->get_access_to_bot({ i, j })->enlarge_energy(abs(((Poison*)matrix(i_dir, j_dir))->get_heal()));
					environment->clear(i_dir, j_dir);
					environment->get_access_to_bot({ i, j })->enlarge_index_step(settings->index_step_by_convert_to_food);
				}
			}
		}
	}

	environment->get_access_to_bot({ i, j })->enlarge_index_step(settings->index_step());
	environment->get_access_to_bot({ i, j })->enlarge_energy(settings->lost_energy_by_step());
}

void PhotosynthesisCommand::execute(int i, int j) {
	
	environment->get_access_to_bot({ i, j })->enlarge_energy(settings->energy_by_photosynthesis());
	environment->get_access_to_bot({ i, j })->enlarge_index_step(settings->index_step_by_photosynthesis((environment->get_bot(i, j)).get_energy()));
	environment->get_access_to_bot({ i, j })->enlarge_index_step(settings->index_step());
	environment->get_access_to_bot({ i, j })->enlarge_energy(settings->lost_energy_by_step());
}

void MoveCommand::execute(int i, int j) {
	Matrix<Entity*> matrix = environment->get_matrix();
	int n = matrix.size_n(), m = matrix.size_m();
	Bot* bot = environment->get_access_to_bot({ i, j });
	vector<int> genome = bot->get_genome();
	//int direction = bot->get_genome().value_next_cell(i, j) % 8;
	int index = ((Bot*)matrix(i, j))->get_index_step();
	int direction = genome[(index + 1) % genome.size()] % 8;
	
	std::pair<int, int> coordinates_direction = process_direction(i, j, direction);

	int i_dir = coordinates_direction.first, j_dir = coordinates_direction.second;

	if (DEBUG) {
		cout << "направление " << i_dir << ", " << j_dir << "\n";
	}

	environment->get_access_to_bot({ i, j })->enlarge_energy(-1);

	if (matrix(i_dir, j_dir)->can_be_step()) {

		if (matrix(i_dir, j_dir)->is_health() or matrix(i_dir, j_dir)->is_poison())
			bot->enlarge_energy(((Nutrition*)matrix(i_dir, j_dir))->get_heal());
        
		environment->set_entity({ i_dir, j_dir }, bot);
		environment->set_index_in_live_bots({ i, j }, { i_dir, j_dir });
		environment->clear(i, j);
	}

	((Bot*)matrix(i, j))->enlarge_index_step(settings->direction_identifier(matrix(i_dir, j_dir)));
}

void EatCommand::execute(int i, int j) {
	Matrix<Entity*> matrix = environment->get_matrix();
	int n = matrix.size_n(), m = matrix.size_m();
	Bot* bot = environment->get_access_to_bot({ i, j });
	//int direction = bot->get_genome().value_next_cell(i, j) % 8;
	vector<int> genome = bot->get_genome();
	int index = ((Bot*)matrix(i, j))->get_index_step();
	int direction = genome[(index + 1) % genome.size()] % 8;
	std::pair<int, int> coordinates_direction = process_direction(i, j, direction);

	int i_dir = coordinates_direction.first, j_dir = coordinates_direction.second;

	if (matrix(i_dir, j_dir)->is_eatable()) {

		if (matrix(i_dir, j_dir)->is_wall())
			environment->clear(i_dir, j_dir);

		else {

			if (matrix(i_dir, j_dir)->is_health() or matrix(i_dir, j_dir)->is_poison()) {

				((Bot*)matrix(i, j))->enlarge_energy(((Nutrition*)matrix(i_dir, j_dir))->get_heal());
				environment->clear(i_dir, j_dir);
			}
		}
	}

	environment->get_access_to_bot({ i, j })->enlarge_energy(settings->lost_energy_by_step());
	environment->get_access_to_bot({ i, j })->enlarge_index_step(settings->direction_identifier(matrix(i_dir, j_dir)));
}

void CopyCommand::execute(int i, int j) {
	Bot * a = new Bot;
	Matrix<Entity*>* matr = environment->get_access_to_matrix();
	int size = matr->size_m() * matr->size_n();
	double chance_mutation = (rand() % 100) / (double)100;
	vector<int> genome = ((Bot*)((*matr)(i, j)))->get_genome();

	for (int i = 0; i < genome.size(); ++i) {

		double chance_mutation = (rand() % 100) / (double)100;

		if (chance_mutation <= settings->chance_mutation) {

			int command = rand() % MAX_COMMAND;
			genome[i] = command;
		}
	}

	a->set_genome(genome);
	a->set_type(a->define_the_type());
	int energy = settings->energy_by_copy(((Bot*)((*matr)(i, j)))->get_energy());
	a->set_energy(energy + settings->start_energy / 4);
	((Bot*)((*matr)(i, j)))->enlarge_energy(-energy);

	int minerals = settings->minerals_by_copy(((Bot*)((*matr)(i, j)))->get_minerals());
	a->set_minerals(minerals);
	((Bot*)((*matr)(i, j)))->enlarge_minerals(-minerals);

	std::pair<int, int> position_in_environment = environment->nearest_empty_cell(i, j);
	environment->set_entity(position_in_environment, a);
	
	//
	int test = matr->one_dimensional_index(position_in_environment);
	if (test < 0) {

		cout << "Copy";
			throw 1;

	}
	//

	environment->get_accses_to_live_bots()->push_back(test);
	environment->get_access_to_bot({ i, j })->enlarge_index_step(settings->index_step_by_copy);
}

// Обмен всех минералов или какого то определенного кол-ва
// Перенести константу (константа, атрибут настроек или атрибут мира)
void SwapMineralsCommand::execute(int i, int j) {
	Bot* a = environment->get_access_to_bot({ i, j });
	int minerals = a->get_minerals();

	if (minerals >= settings->requariable_count_minerals_for_swap(environment->get_live_bots(), environment->get_matrix())) {

		for (int i = 0; i < minerals; ++i)
			a->enlarge_energy(settings->energy_from_mineral);
	}

	environment->get_access_to_bot({ i, j })->enlarge_energy(settings->lost_energy_by_swap_minerals);
	environment->get_access_to_bot({ i, j })->enlarge_index_step(settings->index_step_by_swap_minerals(minerals));
}

void EatBotCommand::execute(int i, int j) {
	Matrix<Entity*> matrix = environment->get_matrix();
	int n = matrix.size_n(), m = matrix.size_m();
	Bot* bot = environment->get_access_to_bot({ i, j });
	//int direction = bot->get_genome().value_next_cell(i, j) % 8;
	vector<int> genome = bot->get_genome();
	int index = ((Bot*)matrix(i, j))->get_index_step();
	int direction = genome[(index + 1) % genome.size()] % 8;
	std::pair<int, int> coordinates_direction = process_direction(i, j, direction);

	int i_dir = coordinates_direction.first, j_dir = coordinates_direction.second;

	if (DEBUG) {
		cout << "направление " << i_dir << ", " << j_dir << "\n";
	}

	if (matrix(i_dir, j_dir)->is_bot()) {

		if (((Bot*)matrix(i, j))->get_energy() > ((Bot*)matrix(i_dir, j_dir))->get_energy()) {

			((Bot*)matrix(i, j))->enlarge_energy(settings->energy_by_eat_bot(((Bot*)matrix(i_dir, j_dir))->get_energy()));
			environment->kill_bot(i_dir, j_dir);
			((Bot*)matrix(i, j))->enlarge_energy(settings->lost_energy_by_eat_bot);
		}
	}

	environment->get_access_to_bot({ i, j })->enlarge_energy(settings->lost_energy_by_step());
	environment->get_access_to_bot({ i, j })->enlarge_index_step(settings->index_step_by_eat_bot(matrix(i_dir, j_dir)));
}


void CheckEnergyCommand::execute(int i, int j) {
	Matrix<Entity*> matrix = environment->get_matrix();
	int energy = ((Bot*)matrix(i, j))->get_energy();

	if (energy > settings->bias_const) 
		environment->get_access_to_bot({ i, j })->enlarge_index_step(settings->index_step_greater_than_bias);

	else
		environment->get_access_to_bot({ i, j })->enlarge_index_step(settings->index_step_lower_than_bias);

	environment->get_access_to_bot({ i, j })->enlarge_energy(settings->lost_energy_by_step());
}

void CyclicMoveCommand::execute(int i, int j) {
	environment->get_access_to_bot({ i, j })->enlarge_index_step(step);
	environment->get_access_to_bot({ i, j })->enlarge_energy(settings->lost_energy_by_step());
}

std::pair<int, int> Command::process_direction(int i, int j, int direction) const {
	Matrix<Entity*> matrix = environment->get_matrix();
	int n = matrix.size_n(), m = matrix.size_m();

	switch (direction) {

	case 1:
		return { i, (j + 1) % n };

	case 2:
		return { (i + 1) % m, (j + 1) % n };

	case 3:
		return { (i + 1) % m, j };

	case 4:
		return std::pair<int, int> {(i + 1) % m, (j - 1 + n) % n};

	case 5:
		return { i, (j - 1 + n) % n };

	case 6: 
		return { (i - 1 + m) % m, (j - 1 + n) % n };

	case 7:
		return { (i - 1 + m) % m, j};

	case 0:
		return { (i - 1 + m) % m, (j + 1 + n) % n };
	}
}

void LookCommand::execute(int i, int j) {
	Matrix<Entity*> matrix = environment->get_matrix();
	int n = matrix.size_n(), m = matrix.size_m();
	vector<int> genome = ((Bot*)matrix(i, j))->get_genome();
	int index = ((Bot*)matrix(i, j))->get_index_step();
	int direction = genome[(index + 1) % genome.size()] % 8;
	std::pair<int, int> coordinates_direction = process_direction(i, j, direction);
	int i_dir = coordinates_direction.first, j_dir = coordinates_direction.second;

	if (matrix(i_dir, j_dir)->is_health()) {

		((Bot*)matrix(i, j))->enlarge_energy(((Nutrition*)matrix(i_dir, j_dir))->get_heal());
		environment->set_entity({ i_dir, j_dir }, (Bot*)matrix(i, j));
		environment->set_index_in_live_bots({ i, j }, { i_dir, j_dir });
		environment->clear(i, j);
	}

	((Bot*)matrix(i, j))->enlarge_index_step(settings->index_step_by_look(matrix(i_dir, j_dir)));
	environment->get_access_to_bot({ i, j })->enlarge_energy(settings->lost_energy_by_step());
}

