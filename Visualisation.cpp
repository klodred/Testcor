#include "Visualisation.h"
#include <chrono>
#include "ImageLoader.h"
#include "Timer.h"

void Controller::run() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Life");
	window.setFramerateLimit(60);
	sf::Event event;
	//Timer timer((MenuModel*)game.)
	Timer timer(settings.time_iteration);

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

				if (event.key.code == sf::Keyboard::Right) {

					settings.time_iteration = settings.time_iteration / 2;
					timer = Timer(settings.time_iteration);

				}

				if (event.key.code == sf::Keyboard::Left) {

					settings.time_iteration = (settings.time_iteration + 1) * 2;
					timer = Timer(settings.time_iteration);

				} 

				if (event.key.code == sf::Keyboard::N) {

					World* w = new World(settings);
					game = new WorldModel(w);

				}

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

WorldModel::WorldModel(World* w) : world(w) {
	this->buttons["Save"];
	buttons["Save"].setSize({ (WINDOW_WIDTH - WORLD_WIDTH) / 3, WINDOW_HEIGHT / 20 });
	buttons["Save"].setPosition({ (WINDOW_WIDTH - WORLD_WIDTH) / 20, WINDOW_HEIGHT / 20 });
	buttons["Save"].setColor(sf::Color::Black);
	this->buttons["Save"].initText("Save", "calibri.ttf", 20, sf::Color(255, 255, 255));
	buttons["Save"].setOutlineThickness(2.f);
	buttons["Save"].setOutlineColor(sf::Color::White);

	this->buttons["New"];
	buttons["New"].setSize({ (WINDOW_WIDTH - WORLD_WIDTH) / 3, WINDOW_HEIGHT / 20 });
	buttons["New"].setPosition({ (WINDOW_WIDTH - WORLD_WIDTH) / 2, WINDOW_HEIGHT / 20 });
	buttons["New"].setColor(sf::Color::Black);
	this->buttons["New"].initText("New", "calibri.ttf", 20, sf::Color(255, 255, 255));
	buttons["New"].setOutlineThickness(2.f);
	buttons["New"].setOutlineColor(sf::Color::White);

	labels["FileName"];
	sf::Font* font = new sf::Font;
	font->loadFromFile("calibri.ttf");
	labels["FileName"].setFont(*font);
	labels["FileName"].setString("File name: ");
	labels["FileName"].setFillColor(sf::Color::White);
	labels["FileName"].setCharacterSize(17);
	labels["FileName"].setPosition({(WINDOW_WIDTH - WORLD_WIDTH) / 23, WINDOW_HEIGHT / 7.5});

	labels["Settings"];
	font->loadFromFile("calibri.ttf");
	labels["Settings"].setFont(*font);
	labels["Settings"].setString("Settings: ");
	labels["Settings"].setFillColor(sf::Color::White);
	labels["Settings"].setCharacterSize(17);
	labels["Settings"].setPosition({ (WINDOW_WIDTH - WORLD_WIDTH) / 2.7, WINDOW_HEIGHT / 5 });

	labels["SimulateSpeed"];
	font->loadFromFile("calibri.ttf");
	labels["SimulateSpeed"].setFont(*font);
	labels["SimulateSpeed"].setString("Simulation Speed: ");
	labels["SimulateSpeed"].setFillColor(sf::Color::White);
	labels["SimulateSpeed"].setCharacterSize(17);
	labels["SimulateSpeed"].setPosition({ (WINDOW_WIDTH - WORLD_WIDTH) / 23, WINDOW_HEIGHT / 4.2 });

	textField["SimulateSpeed"];
	textField["SimulateSpeed"].setSize({ (WINDOW_WIDTH - WORLD_WIDTH) / 7, WINDOW_HEIGHT / 30 });
	textField["SimulateSpeed"].setFillColor(sf::Color::White);
	textField["SimulateSpeed"].setPosition({ (WINDOW_WIDTH - WORLD_WIDTH) / 2.4, WINDOW_HEIGHT / 4.2 });
	textField["SimulateSpeed"].setOutlineThickness(5);
	textField["SimulateSpeed"].setOutlineColor(sf::Color(127, 127, 127));
	textField["SimulateSpeed"].initText("calibri.ttf", 17, sf::Color::Black);

	labels["ResourceSpeed"];
	font->loadFromFile("calibri.ttf");
	labels["ResourceSpeed"].setFont(*font);
	labels["ResourceSpeed"].setString("Resource Speed: ");
	labels["ResourceSpeed"].setFillColor(sf::Color::White);
	labels["ResourceSpeed"].setCharacterSize(17);
	labels["ResourceSpeed"].setPosition({ (WINDOW_WIDTH - WORLD_WIDTH) / 23, WINDOW_HEIGHT / 3.2 });

	textField["ResourceSpeed"];
	textField["ResourceSpeed"].setSize({ (WINDOW_WIDTH - WORLD_WIDTH) / 7, WINDOW_HEIGHT / 30 });
	textField["ResourceSpeed"].setFillColor(sf::Color::White);
	textField["ResourceSpeed"].setPosition({ (WINDOW_WIDTH - WORLD_WIDTH) / 2.4, WINDOW_HEIGHT / 3.2 });
	textField["ResourceSpeed"].setOutlineThickness(5);
	textField["ResourceSpeed"].setOutlineColor(sf::Color(127, 127, 127));
	textField["ResourceSpeed"].initText("calibri.ttf", 17, sf::Color::Black);

	this->buttons["Apply2"];
	buttons["Apply2"].setSize({ (WINDOW_WIDTH - WORLD_WIDTH) / 3.2, WINDOW_HEIGHT / 10 });
	buttons["Apply2"].setPosition({ (WINDOW_WIDTH - WORLD_WIDTH) / 1.55, WINDOW_HEIGHT / 4.3 });
	buttons["Apply2"].setColor(sf::Color::Black);
	this->buttons["Apply2"].initText("Apply", "calibri.ttf", 17, sf::Color(255, 255, 255));
	buttons["Apply2"].setOutlineThickness(2.f);
	buttons["Apply2"].setOutlineColor(sf::Color::White);

	labels["Info"];
	font->loadFromFile("calibri.ttf");
	labels["Info"].setFont(*font);
	labels["Info"].setString("Info: ");
	labels["Info"].setFillColor(sf::Color::White);
	labels["Info"].setCharacterSize(17);
	labels["Info"].setPosition({ (WINDOW_WIDTH - WORLD_WIDTH) / 2.5, WINDOW_HEIGHT / 2.65 });

	/*
	this->buttons["Apply2"];
	buttons["Apply2"].setSize({ (WINDOW_WIDTH - WORLD_WIDTH) / 6, WINDOW_HEIGHT / 25 });
	buttons["Apply2"].setPosition({ (WINDOW_WIDTH - WORLD_WIDTH) / 1.5, WINDOW_HEIGHT / 5.4 });
	buttons["Apply2"].setColor(sf::Color::Black);
	this->buttons["Apply2"].initText("Apply", "calibri.ttf", 17, sf::Color(255, 255, 255));
	buttons["Apply2"].setOutlineThickness(2.f);
	buttons["Apply2"].setOutlineColor(sf::Color::White);
	*/

	textField["FileName"];
	textField["FileName"].setSize({ (WINDOW_WIDTH - WORLD_WIDTH) / 3, WINDOW_HEIGHT / 25 });
	textField["FileName"].setFillColor(sf::Color::White);
	textField["FileName"].setPosition({ (WINDOW_WIDTH - WORLD_WIDTH) / 4, WINDOW_HEIGHT / 7.5 });
	textField["FileName"].setOutlineThickness(5);
	textField["FileName"].setOutlineColor(sf::Color(127, 127, 127));
	textField["FileName"].initText("calibri.ttf", 17, sf::Color::Black);

	this->buttons["Apply1"];
	buttons["Apply1"].setSize({ (WINDOW_WIDTH - WORLD_WIDTH) / 6, WINDOW_HEIGHT / 25 });
	buttons["Apply1"].setPosition({ (WINDOW_WIDTH - WORLD_WIDTH) / 1.5, WINDOW_HEIGHT / 7.4 });
	buttons["Apply1"].setColor(sf::Color::Black);
	this->buttons["Apply1"].initText("Apply", "calibri.ttf", 17, sf::Color(255, 255, 255));
	buttons["Apply1"].setOutlineThickness(2.f);
	buttons["Apply1"].setOutlineColor(sf::Color::White);

	this->shapes["Bound1"];
	shapes["Bound1"].setSize({ WINDOW_WIDTH - WORLD_WIDTH, 2 });
	shapes["Bound1"].setPosition({ 0, WINDOW_HEIGHT / 2.7 });
	shapes["Bound1"].setFillColor(sf::Color::Yellow);

	labels["CountBot"];
	font->loadFromFile("calibri.ttf");
	labels["CountBot"].setFont(*font);
	labels["CountBot"].setString("Count bots: ");
	labels["CountBot"].setFillColor(sf::Color::White);
	labels["CountBot"].setCharacterSize(17);
	labels["CountBot"].setPosition({ (WINDOW_WIDTH - WORLD_WIDTH) / 23, WINDOW_HEIGHT / 2.5 });
}



GameModel* WorldModel::process(sf::Event& event, sf::RenderWindow& window) {

	if (event.type == sf::Event::MouseButtonPressed) {

		//cout << "Зашли в обработку кнопок\n";
		this->textField["FileName"].setFocus(false);
		this->textField["SimulateSpeed"].setFocus(false);

		if (this->buttons["New"].isMouseOver(window)) {
			World* w = new World(this->world->get_settings());
			GameModel* a = new WorldModel(w);
			return a;
		}

		if (this->buttons["Save"].isMouseOver(window)) {

			std::ofstream fcin;
			fcin.open(fileName);
			world->save(fcin);
		}
		
		if (this->textField["FileName"].isMouseOver(window)) {
			this->textField["FileName"].setFocus(true);
		}

		if (this->textField["SimulateSpeed"].isMouseOver(window)) {
			this->textField["SimulateSpeed"].setFocus(true);
		}

		if (this->buttons["Apply1"].isMouseOver(window)) {
			fileName = this->textField["FileName"].getText();
		}
	}

	else if (textField["FileName"].getFocus()) {
		this->textField["FileName"].handleInput(event);
    }
	
	else if (textField["SimulateSpeed"].getFocus()) {
		this->textField["SimulateSpeed"].handleInput(event);
	}

	return this;
}

GameModel* MenuModel::process(sf::Event& event, sf::RenderWindow& window) {
	
	if (event.type == sf::Event::MouseButtonPressed) {

		if (this->buttons["Run"].isMouseOver(window)) {

			World* w = new World(this->settings);
			GameModel* a = new WorldModel(w);
			return a;
		}

		if (this->buttons["Load"].isMouseOver(window)) {

			World* w = new World();
			std::string file_name = "write.txt";
			std::ifstream fcin;
			fcin.open(file_name);
			w->load(fcin);
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



void GameModel::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	std::chrono::system_clock::time_point start;
	if (DEBUG_TIME) {
		start = std::chrono::system_clock::now();

	}
	states.transform *= getTransform();
	draw_main(target, states);
	draw_ui(target, states);
	if (DEBUG_TIME) {


		auto end = std::chrono::system_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		std::cout << "Time for drawing world: " << elapsed.count() << " ms" << std::endl;

	}

}

void WorldModel::draw_main(sf::RenderTarget& target, sf::RenderStates states) const {

	Matrix<Entity*> a = world->get_matrix();
	int size = WORLD_WIDTH / this->world->size();
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
	s.setPosition(WINDOW_WIDTH - WORLD_WIDTH, 0);

	s.setScale(WORLD_WIDTH / s.getLocalBounds().width, WORLD_HEIGHT / s.getLocalBounds().height);
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
				s.setPosition(i * size + WINDOW_WIDTH - WORLD_WIDTH, j * size);
				s.setScale(size / s.getLocalBounds().width, size / s.getLocalBounds().height);
				target.draw(s, states);
			}
		}
	}

};

void WorldModel::draw_ui(sf::RenderTarget& target, sf::RenderStates states) const { 

	for (auto el : buttons) {

		target.draw(el.second, states);
	}

	for (auto el : labels) {

		target.draw(el.second, states);
	}

	for (auto el : textField) {

		target.draw(el.second, states);
	}

	for (auto el : shapes) {

		target.draw(el.second, states);
	}

};


void MenuModel::draw_main(sf::RenderTarget& target, sf::RenderStates states) const { 

	sf::Sprite s;
	sf::Image im = ImageLoader::get_instance().get_image("menu.jpg");
	sf::Texture t;
	t.loadFromImage(im);
	s.setTexture(t);
	s.setPosition(0, 0);
	s.setScale(WINDOW_WIDTH / s.getLocalBounds().width, WINDOW_HEIGHT / s.getLocalBounds().height);
	target.draw(s, states);

};

void MenuModel::draw_ui(sf::RenderTarget& target, sf::RenderStates states) const { 

	for (auto el : buttons) {

		target.draw(el.second, states);

	}

};