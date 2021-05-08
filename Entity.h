#pragma once
#include <iostream>
#include "Matrix.h"
#include <SFML/Graphics.hpp>
#include <string>

static const int SIZE_GENOME = 8, MAX_COMMAND = 24;

class Form {
	sf::Image s;
	std::string name;

public:

	Form(const std::string& image_path = "") : name(image_path) {};

	sf::Image get_sprite() {
		
		s.loadFromFile(name);
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

public:
	Bot();

	Bot(int step, const Matrix<int>& gen, int ener) : index_step(step), genome(gen), energy(ener) { steapble = false; eatable = true; }; // ?

	virtual Form get_form() { return Form("bot.png"); };

	int get_index_step() { return index_step; };

	int get_energy() const { return energy; };

	int get_minerals() const { return minerals; };

	Matrix<int> get_genome() const { return genome; };

	virtual bool is_bot() const { return true; };

	virtual bool is_wall() const { return false; };

	virtual bool is_health() const { return false; };

	virtual bool is_poison() const { return false; };

	virtual bool is_empty() const { return false; };

	void enlarge_energy(int _energy) { this->energy += _energy; };

	void enlarge_index_step(int add) { this->index_step  = (index_step + add) % (genome.size_m() * genome.size_n()); };

	bool is_die() { return energy <= 0; };
};

class Wall : public Entity {
private:
	int damage;

public:
	Wall() { damage = 0; steapble = false; eatable = true; };
	virtual Form get_form() { return Form("image.jpg"); }
    
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
	virtual Form get_form() { return Form("image.jpg"); }

	virtual bool is_health() const { return true; };

	virtual bool is_poison() const { return false; };
};

class Poison : public Nutrition {
public:
	virtual Form get_form() {

		return Form("image.jpg");
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


