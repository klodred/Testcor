#include "Visualisation.h"
#include <chrono>
#include "ImageLoader.h"
#include "Timer.h"

void Controller::run() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Life");
	window.setFramerateLimit(60);
	sf::Event event;
	Timer timer(300);

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
		if (timer.is_ready()) {

			game->run();
			timer.on();
			//if (DEBUG) {

				//std::cout << "Timer was ready" << std::endl;

//			}

		}
		// Выполняем необходимые действия по отрисовке
		window.clear(sf::Color(0, 0, 0, 60));
		//window.clear();
		window.draw(*game);
		window.display();

	}
}

void MenuModel::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	sf::Sprite s;
	sf::Image im = ImageLoader::get_instance().get_image("menu.jpg");
	sf::Texture t;
	t.loadFromImage(im);
	s.setTexture(t);
	s.setPosition(0, 0);
	s.setScale(WINDOW_WIDTH / s.getLocalBounds().width, WINDOW_HEIGHT / s.getLocalBounds().height);
	target.draw(s, states);
	
	for (auto el : buttons) {

		target.draw(el.second, states);

	}
}



void WorldModel::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	std::chrono::system_clock::time_point start;
	if (DEBUG) {
		start = std::chrono::system_clock::now();

	}

	states.transform *= getTransform();
	Matrix<Entity*> a = world->get_matrix();
	int size = WINDOW_WIDTH / this->world->size();
	sf::Sprite s;
	Form form;

	Settings settings = world->get_settings();
	int season = settings.current_season;
	string name;

	switch (season) {
	case settings.SUMMER:
		name = "summer.jpg";
		break;

	case settings.AUTUMN:
		name = "autumn.jpg";
		break;

	case settings.SPRING:
		name = "spring.jpg";
		break;

	case settings.WINTER:
		name = "winter.jpg";
	}

	sf::Image im = ImageLoader::get_instance().get_image(name);
	sf::Texture t;
	t.loadFromImage(im);
	s.setTexture(t);
	s.setPosition(0, 0);

	s.setScale(WINDOW_WIDTH / s.getLocalBounds().width, WINDOW_HEIGHT / s.getLocalBounds().height);
	target.draw(s, states);

	// Отрисовка поля всего
	for (int i = 0; i < this->world->size(); ++i) {

		for (int j = 0; j < this->world->size(); ++j) {

			if (!a(i, j)->is_empty()) {

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
	/*
	if (DEBUG) {


		auto end = std::chrono::system_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		std::cout << "Time for drawing world: " << elapsed.count() << " ms" << std::endl;

	}
	*/

}

GameModel* MenuModel::process(sf::Event& event, sf::RenderWindow& window) {
	
	if (event.type == sf::Event::MouseButtonPressed) {

		cout << "Зашли в обработку кнопок\n";
		if (this->buttons["Run"].isMouseOver(window)) {

			World* w = new World(this->settings);
			GameModel* a = new WorldModel(w);
			return a;
		}

		if (this->buttons["Exit"].isMouseOver(window)) {
			
			exit(0);
		}
	}

	return this;
	
}

MenuModel::MenuModel(Settings _set) : settings(_set) {
	this->buttons["Menu"];
	buttons["Menu"].setSize({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 15 });
	buttons["Menu"].setPosition({ WINDOW_WIDTH / 4, WINDOW_HEIGHT / 10 });
	buttons["Menu"].setColor(sf::Color(205, 205, 205));
	this->buttons["Menu"].initText("Life Menu", "calibri.ttf", 20, sf::Color(255, 255, 255));

	this->buttons["Run"];
	buttons["Run"].setSize({ WINDOW_WIDTH / 3, WINDOW_HEIGHT / 10 });
	buttons["Run"].setPosition({ WINDOW_WIDTH / 2.9, WINDOW_HEIGHT / 4 });
	buttons["Run"].setColor(sf::Color(255, 154, 154));
	//this->buttons["Run"] = { { WINDOW_WIDTH / 2.5, WINDOW_HEIGHT / 10 },  sf::Color::White, {WINDOW_WIDTH / 3.5, WINDOW_HEIGHT / 7}};
	this->buttons["Run"].initText("RUN", "calibri.ttf", 20, sf::Color(255, 255, 255));

	this->buttons["Load"];
	buttons["Load"].setSize({ WINDOW_WIDTH / 3, WINDOW_HEIGHT / 10 });
	buttons["Load"].setPosition({ WINDOW_WIDTH / 2.9, WINDOW_HEIGHT / 2.7 });
	buttons["Load"].setColor(sf::Color(255, 154, 154));
	this->buttons["Load"].initText("LOAD", "calibri.ttf", 20, sf::Color(255, 255, 255));

	this->buttons["Settings"];
	buttons["Settings"].setSize({ WINDOW_WIDTH / 3, WINDOW_HEIGHT / 10 });
	buttons["Settings"].setPosition({ WINDOW_WIDTH / 2.9, WINDOW_HEIGHT / 2.05 });
	buttons["Settings"].setColor(sf::Color(255, 154, 154));
	this->buttons["Settings"].initText("SETTINGS", "calibri.ttf", 20, sf::Color(255, 255, 255));
	
	this->buttons["Exit"];
	buttons["Exit"].setSize({ WINDOW_WIDTH / 3, WINDOW_HEIGHT / 10 });
	buttons["Exit"].setPosition({ WINDOW_WIDTH / 2.9, WINDOW_HEIGHT / 1.65 });
	buttons["Exit"].setColor(sf::Color(255, 154, 154));
	this->buttons["Exit"].initText("EXIT", "calibri.ttf", 20, sf::Color(255, 255, 255));
	
}

/*
MenuModel::MenuModel() {
	this->buttons["Run"] = { "Run", { 200, 50 }, 12, sf::Color::Green, sf::Color::Black };
	Button button("Run", { 200, 50 }, 12, sf::Color::Green, sf::Color::Black);
	buttons.insert(std::pair<std::string, Button>("Run", button));
}
*/

/*
GameModel* MenuModel::process(sf::Event& event, sf::RenderWindow& window) {
	if (event.type == sf::Event::MouseButtonPressed) {

		cout << "Зашли в обработку кнопок\n";
		if (this->buttons["Run"].isMouseOver(window)) {

			cout << "Кнопка нажата\n";
			World* w = new World(this->settings);
			GameModel* a = new WorldModel(w);
			return a;
		}
	}

	return this;
}
*/


void WorldModel::run() {

	this->world->iteration_world();

}