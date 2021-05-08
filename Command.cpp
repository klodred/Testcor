#include "Command.h"

// разные команды для разного поедания
// и в конструкторе бота
// по содержанию его генома его тип будет записываться в int type

void Command::process_command(int i, int j) {
	Matrix<Entity*>* matr = environment->get_access_to_matrix();
	int index = ((Bot*)(*matr)(i, j))->get_index_step();
	int step = ((Bot*)(*matr)(i, j))->get_genome()(index);
	// if max then copy this
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
						}
					}


				}

			}
		}
	}
}

void Command::steal(int i, int j) {
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

void Command::look(int i, int j) {
	Matrix<Entity*> matrix = environment->get_matrix();
	int n = matrix.size_n(), m = matrix.size_m();
	Matrix<int> genome = ((Bot*)matrix(i, j))->get_genome();
	int direction = genome.value_next_cell(i, j) % 8;
	std::pair<int, int> coordinates_direction = process_direction(i, j, direction);

	int i_dir = coordinates_direction.first, j_dir = coordinates_direction.second;

	//if (i_dir >= n or j_dir >= m)
		//throw std::out_of_range("Direction_Error");

	if (matrix(i_dir, j_dir)->is_health()) {

		((Bot*)matrix(i, j))->enlarge_energy(((Nutrition*)matrix(i_dir, j_dir))->get_heal());
		environment->set_entity({ i_dir, j_dir }, (Bot*)matrix(i, j));
		environment->clear(i, j);
	}

	((Bot*)matrix(i, j))->enlarge_index_step(settings->index_step_by_look(matrix(i_dir, j_dir)));
	environment->get_access_to_bot({ i, j })->enlarge_energy(settings->lost_energy_by_step());
}

void Command::convert_to_food(int i, int j) {
	int n = environment->size(), m = environment->size();
	Matrix<Entity*> matrix = environment->get_matrix();

	for (int counter_i = 0, i_dir = i - 1; counter_i < 3; ++counter_i, ++i_dir) {

		for (int counter_j = 0, j_dir = j - 1; counter_j < 3; ++counter_j, ++j_dir) {

			if (matrix.cell_is_exist(i_dir, j_dir)) {

				if (matrix(i_dir, j_dir)->is_poison()) {

					environment->get_access_to_bot({ i, j })->enlarge_energy(abs(((Poison*)matrix(i_dir, j_dir))->get_heal()));
					environment->get_access_to_bot({ i, j })->enlarge_energy(settings->lost_energy_by_convert_to_food);
					environment->clear(i, j);
					environment->get_access_to_bot({ i, j })->enlarge_index_step(settings->index_step_by_convert_to_food);
				}
			}
		}
	}

	environment->get_access_to_bot({ i, j })->enlarge_index_step(settings->index_step());
	environment->get_access_to_bot({ i, j })->enlarge_energy(settings->lost_energy_by_step());
}

void Command::photosynthesis(int i, int j) {
	environment->get_access_to_bot({ i, j })->enlarge_energy(settings->energy_by_photosynthesis());
	environment->get_access_to_bot({ i, j })->enlarge_index_step(settings->index_step_by_photosynthesis);
	environment->get_access_to_bot({ i, j })->enlarge_index_step(settings->index_step());
	environment->get_access_to_bot({ i, j })->enlarge_energy(settings->lost_energy_by_step());
}

void Command::move(int i, int j) {
	Matrix<Entity*> matrix = environment->get_matrix();
	int n = matrix.size_n(), m = matrix.size_m();
	Bot* bot = environment->get_access_to_bot({ i, j });
	int direction = bot->get_genome().value_next_cell(i, j) % 8;
	std::pair<int, int> coordinates_direction = process_direction(i, j, direction);

	int i_dir = coordinates_direction.first, j_dir = coordinates_direction.second;
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

void Command::eat(int i, int j) {
	Matrix<Entity*> matrix = environment->get_matrix();
	int n = matrix.size_n(), m = matrix.size_m();
	Bot* bot = environment->get_access_to_bot({ i, j });
	int direction = bot->get_genome().value_next_cell(i, j) % 8;
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

// перепроверить, сохранится ли бот
// подумать, оставить тот же запас энергии или другой
void Command::copy(int i, int j) {
	// получить 
	//*a = environment->get_bot(i, j)
	// ошибка в геном
	// создание бота
		Bot * a = new Bot;
	Matrix<Entity*>* matr = environment->get_access_to_matrix();
	int size = matr->size_m() * matr->size_n();
	bool flag = false;

	while (!flag) {

		int index = rand() % size;

		if ((*matr)(index)->can_be_step()) {

			flag = true;
			(*matr)(index) = a;
			environment->get_accses_to_live_bots()->push_back(index);
		}
	}

	environment->get_access_to_bot({ i, j })->enlarge_energy(-3);
	environment->get_access_to_bot({ i, j })->enlarge_index_step(5);
}

// Обмен всех минералов или какого то определенного кол-ва
// Перенести константу (константа, атрибут настроек или атрибут мира)
void Command::swap_minerals(int i, int j) {
	Bot* a = environment->get_access_to_bot({ i, j });
	int minerals = a->get_minerals();

	if (minerals >= settings->requariable_count_minerals_for_swap(environment->get_live_bots(), environment->get_matrix())) {

		for (int i = 0; i < minerals; ++i)
			a->enlarge_energy(settings->energy_from_mineral);
	}

	environment->get_access_to_bot({ i, j })->enlarge_energy(settings->lost_energy_by_swap_minerals);
	environment->get_access_to_bot({ i, j })->enlarge_index_step(settings->index_step_by_swap_minerals(minerals));
}

void Command::eat_bot(int i, int j) {
	Matrix<Entity*> matrix = environment->get_matrix();
	int n = matrix.size_n(), m = matrix.size_m();
	Bot* bot = environment->get_access_to_bot({ i, j });
	int direction = bot->get_genome().value_next_cell(i, j) % 8;
	std::pair<int, int> coordinates_direction = process_direction(i, j, direction);

	int i_dir = coordinates_direction.first, j_dir = coordinates_direction.second;

	if (matrix(i_dir, j_dir)->is_bot()) {

		if (((Bot*)matrix(i, j))->get_energy() > ((Bot*)matrix(i_dir, j_dir))->get_energy()) {

			((Bot*)matrix(i, j))->enlarge_energy(((Bot*)matrix(i_dir, j_dir))->get_energy());
			environment->kill_bot(i_dir, j_dir);
		}
	}

	environment->get_access_to_bot({ i, j })->enlarge_energy(-1);
	environment->get_access_to_bot({ i, j })->enlarge_index_step(settings->direction_identifier(matrix(i_dir, j_dir)));
}

/*
void Command::check_energy(int i, int j) {
	Matrix<Entity*> matrix = environment->get_matrix();
	int energy = ((Bot*)matrix(i, j))->get_energy();

	if (energy > ...) 
		environment->get_access_to_bot({ i, j })->enlarge_index_step(...);

	else
		environment->get_access_to_bot({ i, j })->enlarge_index_step(...);

	environment->get_access_to_bot({ i, j })->enlarge_energy(-1);
}
*/

std::pair<int, int> Command::process_direction(int i, int j, int direction) {
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
		return j - 1 < 0 ? std::pair<int, int> {(i + 1) % m, n - 1} : std::pair<int, int>{ (i + 1) % m, j - 1 };

	case 5:
		return j - 1 < 0 ? std::pair<int, int> {i, n - 1} : std::pair<int, int>{ i, j - 1 };

	case 6: // возможно ли упростить ?
		if (j - 1 < 0) {

			if (i - 1 < 0)
				return { m - 1, n - 1 };
			else
				return { i - 1, n - 1 };
		}

		else
			return { i - 1, j - 1 };

	case 7:
		return i - 1 < 0 ? std::pair<int, int> {m - 1, j} : std::pair<int, int>{ i - 1, j };

	case 0:
		return i - 1 < 0 ? std::pair<int, int> {m - 1, (j + 1) % n} : std::pair<int, int>{ i - 1, (j + 1) % n };
	}
}
