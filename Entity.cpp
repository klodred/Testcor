#include "Entity.h"

Bot::Bot() {
	this->genome.random(SIZE_GENOME, 0, MAX_COMMAND);
	this->energy = 5;
	this->index_step = 0;
}