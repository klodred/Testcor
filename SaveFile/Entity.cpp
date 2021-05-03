#include "Entity.h"

Bot::Bot() {
	this->genome.random(SIZE_GENOME, 0, MAX_COMMAND);
	this->energy = 0;
	this->current_move = 0;
}

/*
void Bot::print(std::ostream& os) {
	os << this->genome << "\n";
	os << "Энергия = " << this->energy << "\n";
	os << "Текущая команда = " << this->current_move << "\n";
}
*/