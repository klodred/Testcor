#include "World.h"

bool Environment::is_empty_cell(int i, int j) {
	return this->matrix(i, j) == NULL;
}

void Environment::populate(int count) {
	int c = 0; 

	while (c < count) {

		Bot* bot = new Bot;
		int i = rand() % this->matrix.size_m();
		int j = rand() % this->matrix.size_n();

		if (this->is_empty_cell(i, j)) {

			this->matrix(i, j) = bot;
			++c;
		}
	}
}

void World::run() {
	this->environment.populate(this->settings.get_count_bots());
}

/*
void World::draw(sf::RenderTarget& target, sf::RenderStates states) const {

}
*/
