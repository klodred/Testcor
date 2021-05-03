#include <locale.h>
#include "World.h"
#include "Matrix.h"
#include "Entity.h"
#include <SFML/Graphics.hpp>


int main() {
	setlocale(LC_ALL, "RUS");
	//srand(time(0));
	World world;
	//world.run();

	Game g(world);
	sf::RenderWindow window(sf::VideoMode(600, 600), "Life");
	window.setFramerateLimit(60);

	sf::Event event;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				// ѕолучаем нажатую клавишу - выполн€ем соответствующее действие
				if (event.key.code == sf::Keyboard::Escape) window.close();
			}
		}

		// ¬ыполн€ем необходимые действи€ по отрисовке
		window.clear(sf::Color(0, 0 , 0, 60));
		//window.clear();
		window.draw(g);
		window.display();
	}

	return 0;
}