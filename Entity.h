#pragma once
#include <iostream>
#include "Matrix.h"
#include <SFML/Graphics.hpp>
#include <string>

static const int SIZE_GENOME = 8, MAX_COMMAND = 64;

class Form {
	sf::Image s;
	std::string name;

public:

	Form(const std::string& image_path = "") : name(image_path) {};

	sf::Image get_sprite() {
		//создаем объект Image (изображение)
		s.loadFromFile(name);//загружаем в него файл
		return s;
	}
};

class Entity {
protected:
	bool steapble;

public:
	//void virtual print(std::ostream& os = cout) = 0;
	virtual Form get_form() = 0;

	bool can_be_step() { return this->steapble; };

	//virtual int get_index_move() const { return -1; };

	//virtual Matrix<int> get_genome() const = 0;
};

class Bot : public Entity {
private:
	int index_move;
	Matrix<int> genome;
	int energy;

public:
	Bot();

	Bot(int move, const Matrix<int>& gen, int ener) : index_move(move), genome(gen), energy(ener) { steapble = false; };

	//void virtual print(std::ostream& os = cout);

	virtual Form get_form() {

		return Form("bot.png");
	}

	int get_index_move() { return index_move; };

	Matrix<int> get_genome() const { return genome; };
};

class Wall : public Entity {
private:
	int damage;

public:
	Wall() { damage = 0; steapble = false; };
	virtual Form get_form() {

		return Form("image.jpg");
	}


	//virtual Matrix<int> get_genome() const {};

};

class Nutrition : public Entity {
protected:
	int heal;

public:
	Nutrition() { heal = 0; steapble = true; };
	Nutrition(int h) : heal(h) {};
};

class Health : public Nutrition {
public:
	virtual Form get_form() {

		return Form("image.jpg");
	}

	//virtual int get_index_move() const {};

	//virtual Matrix<int> get_genome() const {};
};

class Poison : public Nutrition {
public:
	virtual Form get_form() {

		return Form("image.jpg");
	}

	//virtual int get_index_move() const {};

	//virtual Matrix<int> get_genome() const {};
};

class EmptyEntity : public Entity {
public:
	EmptyEntity() { steapble = true; };

	virtual Form get_form() {

		return Form("image.png");
	}

	//virtual int get_index_move() const {};

	//virtual Matrix<int> get_genome() const {};
};


