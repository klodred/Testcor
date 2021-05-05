#include "Command.h"

void Command::process_command(int i, int j) {
	Matrix<Entity*>* matr = environment->get_access_to_matrix();
	int index = ((Bot*)(*matr)(i, j))->get_index_move();
	int step = ((Bot*)(*matr)(i, j))->get_genome()(index);

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
						environment->get_access_to_bot({ i, j })->enlarge_energy(energy_victim / 4 - LOSSES);
						environment->get_access_to_bot({ i_dir, j_dir })->enlarge_energy(-(energy_victim / 4));
						
						if (((Bot*)matrix(i_dir, j_dir))->is_die())
							environment->kill_bot(i_dir, j_dir);

						environment->get_access_to_bot({ i, j })->enlarge_index_move(2);

						break;
					}
				}
			}
		}
	}

	int one = (environment->get_matrix()).one_dimensional_index(i, j);
	environment->get_access_to_bot({ i, j })->enlarge_index_move(1);
	environment->get_access_to_bot({ i, j })->enlarge_energy(-1); // совместить в одну у всех
}

void Command::look(int i, int j) {
	Matrix<Entity*> matrix = environment->get_matrix();
	int n = matrix.size_n(), m = matrix.size_m();
	Matrix<int> genome = ((Bot*)matrix(i, j))->get_genome();
	int direction = genome.value_next_cell(i, j) % 8;
	std::pair<int, int> coordinates_direction = process_direction(i, j, direction);

	int i_dir = coordinates_direction.first, j_dir = coordinates_direction.second;

	if (i_dir >= n or j_dir >= m)
		throw std::out_of_range("Direction_Error");

	if (matrix(i_dir, j_dir)->is_health()) {

		((Bot*)matrix(i, j))->enlarge_energy(((Nutrition*)matrix(i_dir, j_dir))->get_heal() - 1);
		environment->set_entity({ i_dir, j_dir }, (Bot*)matrix(i, j));
		environment->set_entity({ i, j }, new EmptyEntity());
	}

	((Bot*)matrix(i, j))->enlarge_index_move(this->direction_identifier(matrix(i_dir, j_dir)));
	environment->get_access_to_bot({ i, j })->enlarge_energy(-1);
}

void Command::convert_to_food(int i, int j) {
	int n = environment->size(), m = environment->size();
	Matrix<Entity*> matrix = environment->get_matrix();

	for (int counter_i = 0, i_dir = i - 1; counter_i < 3; ++counter_i, ++i_dir) {

		for (int counter_j = 0, j_dir = j - 1; counter_j < 3; ++counter_j, ++j_dir) {

			if (matrix.cell_is_exist(i_dir, j_dir)) {

				if (matrix(i_dir, j_dir)->is_poison()) {

					environment->get_access_to_bot({ i, j })->enlarge_energy(abs(((Poison*)matrix(i_dir, j_dir))->get_heal()));
					environment->clear(i, j);
					environment->get_access_to_bot({ i, j })->enlarge_index_move(4);
				}
			}
		}
	}

	environment->get_access_to_bot({ i, j })->enlarge_index_move(1);
	environment->get_access_to_bot({ i, j })->enlarge_energy(-1);
}

void Command::photosynthesis(int i, int j) {
	environment->get_access_to_bot({ i, j })->enlarge_energy(4);
	environment->get_access_to_bot({ i, j })->enlarge_index_move(2);
	environment->get_access_to_bot({ i, j })->enlarge_energy(-1);
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

	((Bot*)matrix(i, j))->enlarge_index_move(this->direction_identifier(matrix(i_dir, j_dir)));
}

void Command::eat(int i, int j) {
	Matrix<Entity*> matrix = environment->get_matrix();
	int n = matrix.size_n(), m = matrix.size_m();
	Bot* bot = environment->get_access_to_bot({ i, j });
	int direction = bot->get_genome().value_next_cell(i, j) % 8;
	std::pair<int, int> coordinates_direction = process_direction(i, j, direction);

	int i_dir = coordinates_direction.first, j_dir = coordinates_direction.second;

	if (matrix(i_dir, j_dir)->is_eatable()) {

		if (matrix(i_dir, j_dir)->is_bot()) {

			if (((Bot*)matrix(i, j))->get_energy() > ((Bot*)matrix(i_dir, j_dir))->get_energy()) {

				((Bot*)matrix(i, j))->enlarge_energy(((Bot*)matrix(i_dir, j_dir))->get_energy());
				environment->kill_bot(i_dir, j_dir);
			}
		}

		else {

			if (matrix(i_dir, j_dir)->is_wall())
				environment->clear(i_dir, j_dir);

			else {

				if (matrix(i_dir, j_dir)->is_health() or matrix(i_dir, j_dir)->is_poison()) {

					((Bot*)matrix(i, j))->enlarge_energy(((Nutrition*)matrix(i_dir, j_dir))->get_heal());
					environment->clear(i_dir, j_dir);
				}
			}
		}
	}

	environment->get_access_to_bot({ i, j })->enlarge_energy(-1);
	environment->get_access_to_bot({ i, j })->enlarge_index_move(this->direction_identifier(matrix(i_dir, j_dir)));
}

// перепроверить, сохранится ли бот
// подумать, оставить тот же запас энергии или другой
void Command::copy(int i, int j) {
	Bot* a = new Bot;
	*a = environment->get_bot(i, j);
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
	environment->get_access_to_bot({ i, j })->enlarge_index_move(5);
}

// Обмен всех минералов или какого то определенного кол-ва
// Перенести константу (константа, атрибут настроек или атрибут мира)
void Command::swap_minerals(int i, int j) {
	Bot* a = environment->get_access_to_bot({ i, j });

	if (a->get_minerals() >= MINERALS) {

		for (int i = 0; i < a->get_minerals(); ++i)
			a->enlarge_energy(4);
	}

	environment->get_access_to_bot({ i, j })->enlarge_energy(-3);
}

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

int Command::direction_identifier(Entity* entity) {
	if (entity->is_empty())
		return 2;

	else {

		if (entity->is_wall())
			return 3;

		else {

			if (entity->is_bot())
				return 4;

			else {

				if (entity->is_health() or entity->is_poison())
					return 5;
			}
		}
	}
}