#include "Entity.h"

Bot::Bot() {
	this->genome.random(SIZE_GENOME, 0, MAX_COMMAND);
	this->energy = 2;
	this->index_move = 0;
}