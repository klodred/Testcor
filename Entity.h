#pragma once
#include <iostream>
#include "Matrix.h"
#include <SFML/Graphics.hpp>
#include <string>
#include "ImageLoader.h"

enum commands {
	LOOK = 6, CONVERT_TO_FOOD = 11, STEAL = 15, PHOTOSYNTHESIS = 19, MOVE = 25, EAT = 29, COPY = 32,
	SWAP_MINERALS = 35, EAT_BOT = 37, CHECK_ENERGY = 40, CYCLIC_MOVE = 63
};

static enum {SUN, MINERALS, MEAT, MIXED};
static const int SIZE_GENOME = 64, MAX_COMMAND = 63;

class Form {
	sf::Image s;
	std::string name;

public:

	Form(const std::string& image_path = "") : name(image_path) {};

	sf::Image get_sprite() {
		
		s = ImageLoader::get_instance().get_image(name);
		return s;
	}
};

class Entity {
protected:
	bool steapble;
	bool eatable;

public:
	virtual Form get_form() = 0;

	bool can_be_step() { return this->steapble; };

	bool is_eatable() { return this->eatable; };

	virtual bool is_bot() const = 0;

	virtual bool is_wall() const = 0;

	virtual bool is_health() const = 0;

	virtual bool is_poison() const = 0;

	virtual bool is_empty() const = 0;

};

class Bot : public Entity {
private:
	int index_step;
	Matrix<int> genome;
	int energy;
	int minerals;
	int type;

public:
	Bot();

	Bot(int step, const Matrix<int>& gen, int ener) : index_step(step), genome(gen), energy(ener) { steapble = false; eatable = true; }; // ?

	virtual Form get_form();

	int get_index_step() { return index_step; };

	void set_index_step(int index) { index_step = index; };

	int get_energy() const { return energy; };

	int get_minerals() const { return minerals; };

	Matrix<int> get_genome() const { return genome; };

	void set_genome(Matrix<int> _genome) { genome = _genome; };

	virtual bool is_bot() const { return true; };

	virtual bool is_wall() const { return false; };

	virtual bool is_health() const { return false; };

	virtual bool is_poison() const { return false; };

	virtual bool is_empty() const { return false; };

	void enlarge_energy(int _energy) { this->energy += _energy; };

	void set_energy(int _energy) { energy = _energy; };

	void enlarge_minerals(int _minerals) { this->minerals += _minerals; };

	void set_minerals(int _minerals) { minerals = _minerals; };

	void enlarge_index_step(int add) { this->index_step  = (index_step + add) % (genome.size_m() * genome.size_n()); };

	bool is_die() { return energy <= 0; };

	int define_the_type();

	void set_type(int _type) { this->type = _type; };
};

class Wall : public Entity {
private:
	int damage;

public:
	Wall() { damage = 0; steapble = false; eatable = true; };
	virtual Form get_form() { return Form("wall.png"); }
    
	virtual bool is_bot() const { return false; };

	virtual bool is_wall() const { return true; };

	virtual bool is_health() const { return false; };

	virtual bool is_poison() const { return false; };

	virtual bool is_empty() const { return false; };

};

class Nutrition : public Entity {
protected:
	int heal;

public:
	Nutrition() { heal = 0; steapble = eatable = true; };

	Nutrition(int h) : heal(h) { steapble = eatable = true; };

	int get_heal() const { return heal; };

	virtual bool is_bot() const { return false; };

	virtual bool is_wall() const { return false; };

	virtual bool is_empty() const { return false; };
};

class Health : public Nutrition {
public:
	Health(int h) : Nutrition(h) {};

	virtual Form get_form() { return Form("health.png"); }

	virtual bool is_health() const { return true; };

	virtual bool is_poison() const { return false; };
};

class Poison : public Nutrition {
public:
	Poison(int h) : Nutrition(h) {};

	virtual Form get_form() {

		return Form("poison.png");
	}

	virtual bool is_health() const { return false; };

	virtual bool is_poison() const { return true; };
};

class EmptyEntity : public Entity {
public:
	EmptyEntity() { steapble = true; eatable = false; };

	virtual Form get_form() { return Form("empty.png"); }

	virtual bool is_bot() const { return false; };

	virtual bool is_wall() const { return false; };

	virtual bool is_health() const { return false; };

	virtual bool is_poison() const { return false; };

	virtual bool is_empty() const { return true; };
};



int index_max(vector<int> vec);