#include "Visualisation.h"
#include <thread>

void Controller::run() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Life");
	window.setFramerateLimit(60);
	sf::Event event;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed)
			{
				// Получаем нажатую клавишу - выполняем соответствующее действие
				if (event.key.code == sf::Keyboard::Escape) window.close();
			}

			game = game->process(event, window);

		}

		game->run();
		// Выполняем необходимые действия по отрисовке
		window.clear(sf::Color(0, 0, 0, 60));
		//window.clear();
		window.draw(*game);
		window.display();

	}
}

void SettingsModel::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	for (auto el : buttons) {

		target.draw(el.second, states);

	}
	

}
void WorldModel::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	Matrix<Entity*> a = world.get_matrix();
	int size = WINDOW_WIDTH / this->world.size();
	sf::Sprite s;
	Form form;

	for (int i = 0; i < this->world.size(); ++i) {

		for (int j = 0; j < this->world.size(); ++j) {

			form = a(i, j)->get_form();
			sf::Image im = form.get_sprite();
			sf::Texture t;
			t.loadFromImage(im);
			s.setTexture(t);
			s.setPosition(i * size, j * size);
			s.setScale(size / s.getLocalBounds().width, size / s.getLocalBounds().height);
			target.draw(s, states);

		}
	}
}

GameModel* SettingsModel::process(sf::Event& event, sf::RenderWindow& window) {
	if (event.type == sf::Event::MouseButtonPressed) {

		cout << "Зашли в обработку кнопок\n";
		if (this->buttons["Run"].isMouseOver(window)) {

			cout << "Кнопка нажата\n";
			World* w = new World(this->settings);
			GameModel* a = new WorldModel(*w);
			return a;
		}
	}

	return this;
}

SettingsModel::SettingsModel(Settings _set) : settings(_set) {
	this->buttons["Run"] = { "Run", { 200, 50 }, 12, sf::Color::Green, sf::Color::Black };
	Button button("Run", { 200, 50 }, 12, sf::Color::Green, sf::Color::Black);
	buttons.insert(std::pair<std::string, Button>("Run", button));
	
}

void WorldModel::run() {
	this->world.iteration_world();
}