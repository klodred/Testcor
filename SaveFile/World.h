#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>



class Settings {
private:
	int size_environment;
	int count_bots;

public:
	Settings() { size_environment = 8; count_bots = 8; };

	Settings(int size, int count) : size_environment(size), count_bots(count) {};

	int get_size() { return size_environment; };

	void set_size(int size) { size_environment = size; };

	int get_count_bots() { return count_bots; };

	void set_count_bots(int count) { count_bots = count; };
};

class Environment {
private:
	Matrix<Entity*> matrix;

public:
	Environment() { matrix.resize(SIZE_MAX, SIZE_MAX); };

	Environment(int size) { matrix.resize(size, size); 
    
	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j)
			matrix(i, j) = new EmptyEntity();
	};

	void populate(int count);

	bool is_empty_cell(int i, int j);

	Matrix<Entity*> get_matrix() const { return matrix; };
};


class World {
private:
	Settings settings;
	Environment environment;

public:

	World(int size, int count) : settings(size, count), environment(size) {};

	World() : settings(), environment(settings.get_size()) {};

	void set_size(int size) { settings.set_size(size); };

	void set_count_bots(int count) { settings.set_count_bots(count); };

	void run();

	Matrix<Entity*> get_matrix() const { return environment.get_matrix(); };
};




class Game : public sf::Drawable, public sf::Transformable
{
	World world;
public:
	Game(World w) : world(w) {};
	void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		Matrix<Entity*> a = world.get_matrix();
		int size = 600 / 8;
		sf::Sprite s;
		Form form;

		for (int i = 0; i < 8; ++i) {

			for (int j = 0; j < 8; ++j) {

				form = a(i, j)->get_form();
				sf::Image im = form.get_sprite();
				sf::Texture t;
				t.loadFromImage(im);
				s.setTexture(t);
				s.setPosition(i * size, j * size);
				target.draw(s, states);

			}
		}

	}
};


