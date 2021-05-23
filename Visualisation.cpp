#include "Visualisation.h"
#include <chrono>
#include "ImageLoader.h"
#include "Timer.h"


const int INF = INT_MAX;

void Controller::run() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Life");
	window.setFramerateLimit(60);
	sf::Event event;
	int current_time_iteration = settings.time_iteration;
	Timer timer(current_time_iteration);

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
			settings = game->get_settings();
			if (current_time_iteration != settings.time_iteration) {

				current_time_iteration = settings.time_iteration;
				timer.set_time(current_time_iteration);

			}

		}

		if (timer.is_ready()) {

			game = game->run();
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
	buttons["Save"].setSize({ (WINDOW_WIDTH - WORLD_WIDTH) / 3, WINDOW_HEIGHT / 20 });
	buttons["Save"].setPosition({ (WINDOW_WIDTH - WORLD_WIDTH) / 20, WINDOW_HEIGHT / 20 });
	buttons["Save"].setColor(sf::Color::Black);
	this->buttons["Save"].initText("Save", "calibri.ttf", 20, sf::Color(255, 255, 255));
	buttons["Save"].setOutlineThickness(2.f);
	buttons["Save"].setOutlineColor(sf::Color::White);

	buttons["New"].setSize({ (WINDOW_WIDTH - WORLD_WIDTH) / 3, WINDOW_HEIGHT / 20 });
	buttons["New"].setPosition({ (WINDOW_WIDTH - WORLD_WIDTH) / 2, WINDOW_HEIGHT / 20 });
	buttons["New"].setColor(sf::Color::Black);
	this->buttons["New"].initText("New", "calibri.ttf", 20, sf::Color(255, 255, 255));
	buttons["New"].setOutlineThickness(2.f);
	buttons["New"].setOutlineColor(sf::Color::White);

	sf::Font* font = new sf::Font;
	font->loadFromFile("calibri.ttf");
	labels["FileName"].setFont(*font);
	labels["FileName"].setString("File name: ");
	labels["FileName"].setFillColor(sf::Color::White);
	labels["FileName"].setCharacterSize(17);
	labels["FileName"].setPosition({(WINDOW_WIDTH - WORLD_WIDTH) / 23, WINDOW_HEIGHT / 7.5});

	font->loadFromFile("calibri.ttf");
	labels["Settings"].setFont(*font);
	labels["Settings"].setString("Settings: ");
	labels["Settings"].setFillColor(sf::Color::White);
	labels["Settings"].setCharacterSize(17);
	labels["Settings"].setPosition({ (WINDOW_WIDTH - WORLD_WIDTH) / 2.7, WINDOW_HEIGHT / 5 });

	font->loadFromFile("calibri.ttf");
	labels["SimulateSpeed"].setFont(*font);
	labels["SimulateSpeed"].setString("Simulation Waiting: ");
	labels["SimulateSpeed"].setFillColor(sf::Color::White);
	labels["SimulateSpeed"].setCharacterSize(17);
	labels["SimulateSpeed"].setPosition({ (WINDOW_WIDTH - WORLD_WIDTH) / 23, WINDOW_HEIGHT / 4.2 });

	textField["SimulateSpeed"].setSize({ (WINDOW_WIDTH - WORLD_WIDTH) / 7, WINDOW_HEIGHT / 30 });
	textField["SimulateSpeed"].setString(std::to_string(w->get_settings().time_iteration));
	textField["SimulateSpeed"].setFillColor(sf::Color::White);
	textField["SimulateSpeed"].setPosition({ (WINDOW_WIDTH - WORLD_WIDTH) / 2.4, WINDOW_HEIGHT / 4.2 });
	textField["SimulateSpeed"].setOutlineThickness(5);
	textField["SimulateSpeed"].setOutlineColor(sf::Color(127, 127, 127));
	textField["SimulateSpeed"].initText("calibri.ttf", 17, sf::Color::Black);

	font->loadFromFile("calibri.ttf");
	labels["ResourceSpeed"].setFont(*font);
	labels["ResourceSpeed"].setString("Resource Speed: ");
	labels["ResourceSpeed"].setFillColor(sf::Color::White);
	labels["ResourceSpeed"].setCharacterSize(17);
	labels["ResourceSpeed"].setPosition({ (WINDOW_WIDTH - WORLD_WIDTH) / 23, WINDOW_HEIGHT / 3.2 });

	textField["ResourceSpeed"].setSize({ (WINDOW_WIDTH - WORLD_WIDTH) / 7, WINDOW_HEIGHT / 30 });
	textField["ResourceSpeed"].setString(std::to_string(w->get_settings().time_for_generation_resource));
	textField["ResourceSpeed"].setFillColor(sf::Color::White);
	textField["ResourceSpeed"].setPosition({ (WINDOW_WIDTH - WORLD_WIDTH) / 2.4, WINDOW_HEIGHT / 3.2 });
	textField["ResourceSpeed"].setOutlineThickness(5);
	textField["ResourceSpeed"].setOutlineColor(sf::Color(127, 127, 127));
	textField["ResourceSpeed"].initText("calibri.ttf", 17, sf::Color::Black);

	buttons["Apply2"].setSize({ (WINDOW_WIDTH - WORLD_WIDTH) / 3.2, WINDOW_HEIGHT / 10 });
	buttons["Apply2"].setPosition({ (WINDOW_WIDTH - WORLD_WIDTH) / 1.55, WINDOW_HEIGHT / 4.3 });
	buttons["Apply2"].setColor(sf::Color::Black);
	this->buttons["Apply2"].initText("Apply", "calibri.ttf", 17, sf::Color(255, 255, 255));
	buttons["Apply2"].setOutlineThickness(2.f);
	buttons["Apply2"].setOutlineColor(sf::Color::White);

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

	textField["FileName"].setSize({ (WINDOW_WIDTH - WORLD_WIDTH) / 3, WINDOW_HEIGHT / 25 });
	textField["FileName"].setString("write.txt");
	fileName = textField["FileName"].getText();
	textField["FileName"].setFillColor(sf::Color::White);
	textField["FileName"].setPosition({ (WINDOW_WIDTH - WORLD_WIDTH) / 4, WINDOW_HEIGHT / 7.5 });
	textField["FileName"].setOutlineThickness(5);
	textField["FileName"].setOutlineColor(sf::Color(127, 127, 127));
	textField["FileName"].initText("calibri.ttf", 17, sf::Color::Black);

	buttons["Apply1"].setSize({ (WINDOW_WIDTH - WORLD_WIDTH) / 6, WINDOW_HEIGHT / 25 });
	buttons["Apply1"].setPosition({ (WINDOW_WIDTH - WORLD_WIDTH) / 1.5, WINDOW_HEIGHT / 7.4 });
	buttons["Apply1"].setColor(sf::Color::Black);
	this->buttons["Apply1"].initText("Apply", "calibri.ttf", 17, sf::Color(255, 255, 255));
	buttons["Apply1"].setOutlineThickness(2.f);
	buttons["Apply1"].setOutlineColor(sf::Color::White);

	shapes["Bound1"].setSize({ WINDOW_WIDTH - WORLD_WIDTH, 2 });
	shapes["Bound1"].setPosition({ 0, WINDOW_HEIGHT / 2.7 });
	shapes["Bound1"].setFillColor(sf::Color::Yellow);

	shapes["Bound2"].setSize({ WINDOW_WIDTH - WORLD_WIDTH, 2 });
	shapes["Bound2"].setPosition({ 0, WINDOW_HEIGHT / 1.55 });
	shapes["Bound2"].setFillColor(sf::Color::Yellow);

	font->loadFromFile("calibri.ttf");
	labels["CountBot"].setFont(*font);
	labels["CountBot"].setString("Count bots: ");
	labels["CountBot"].setFillColor(sf::Color::White);
	labels["CountBot"].setCharacterSize(17);
	labels["CountBot"].setPosition({ (WINDOW_WIDTH - WORLD_WIDTH) / 23, WINDOW_HEIGHT / 2.5 });

	font->loadFromFile("calibri.ttf");
	labels["Resource"].setFont(*font);
	labels["Resource"].setString("Resource: ");
	labels["Resource"].setFillColor(sf::Color::White);
	labels["Resource"].setCharacterSize(17);
	labels["Resource"].setPosition({ (WINDOW_WIDTH - WORLD_WIDTH) / 1.8, WINDOW_HEIGHT / 2.5 });

	font->loadFromFile("calibri.ttf");
	labels["Time"].setFont(*font);
	labels["Time"].setString("Time: ");
	labels["Time"].setFillColor(sf::Color::White);
	labels["Time"].setCharacterSize(17);
	labels["Time"].setPosition({ (WINDOW_WIDTH - WORLD_WIDTH) / 23, WINDOW_HEIGHT / 1.65 });

	font->loadFromFile("calibri.ttf");
	labels["TimeDinamic"].setFont(*font);
	labels["TimeDinamic"].setFillColor(sf::Color::White);
	labels["TimeDinamic"].setCharacterSize(17);
	labels["TimeDinamic"].setPosition({ (WINDOW_WIDTH - WORLD_WIDTH) / 6.2, WINDOW_HEIGHT / 1.65 });

	font->loadFromFile("calibri.ttf");
	labels["CountBotDinamic"].setFont(*font);
	labels["CountBotDinamic"].setFillColor(sf::Color::White);
	labels["CountBotDinamic"].setCharacterSize(17);
	labels["CountBotDinamic"].setPosition({ (WINDOW_WIDTH - WORLD_WIDTH) / 3, WINDOW_HEIGHT / 2.5 });

	create_picture("Mixed", "mixedBot.png");
	pictures["Mixed"].setPosition({ (WINDOW_WIDTH - WORLD_WIDTH) / 23, WINDOW_HEIGHT / 2.28 });

	create_picture("Sun", "sunBot.png");
	pictures["Sun"].setPosition({ (WINDOW_WIDTH - WORLD_WIDTH) / 23, WINDOW_HEIGHT / 2.1 });

	create_picture("Mineral", "mineralsBot.png");
	pictures["Mineral"].setPosition({ (WINDOW_WIDTH - WORLD_WIDTH) / 23, WINDOW_HEIGHT / 1.95 });

	create_picture("Meat", "meatBot.png");
	pictures["Meat"].setPosition({ (WINDOW_WIDTH - WORLD_WIDTH) / 23, WINDOW_HEIGHT / 1.83 });

	create_picture("Health", "health.png");
	pictures["Health"].setPosition({ (WINDOW_WIDTH - WORLD_WIDTH) / 1.7, WINDOW_HEIGHT / 2.28 });

	create_picture("Poison", "poison.png");
	pictures["Poison"].setPosition({ (WINDOW_WIDTH - WORLD_WIDTH) / 1.7, WINDOW_HEIGHT / 2.1 });

	create_picture("Wall", "wall.png");
	pictures["Wall"].setPosition({ (WINDOW_WIDTH - WORLD_WIDTH) / 1.7, WINDOW_HEIGHT / 1.95 });

	font->loadFromFile("calibri.ttf");
	labels["CountHealth"].setFont(*font);
	labels["CountHealth"].setFillColor(sf::Color::White);
	labels["CountHealth"].setCharacterSize(17);
	labels["CountHealth"].setPosition({ (WINDOW_WIDTH - WORLD_WIDTH) / 1.4, WINDOW_HEIGHT / 2.28 });

	font->loadFromFile("calibri.ttf");
	labels["CountPoison"].setFont(*font);
	labels["CountPoison"].setFillColor(sf::Color::White);
	labels["CountPoison"].setCharacterSize(17);
	labels["CountPoison"].setPosition({ (WINDOW_WIDTH - WORLD_WIDTH) / 1.4, WINDOW_HEIGHT / 2.1 });

	font->loadFromFile("calibri.ttf");
	labels["CountWall"].setFont(*font);
	labels["CountWall"].setFillColor(sf::Color::White);
	labels["CountWall"].setCharacterSize(17);
	labels["CountWall"].setPosition({ (WINDOW_WIDTH - WORLD_WIDTH) / 1.4, WINDOW_HEIGHT / 1.95 });

	font->loadFromFile("calibri.ttf");
	labels["CountMixed"].setFont(*font);
	labels["CountMixed"].setFillColor(sf::Color::White);
	labels["CountMixed"].setCharacterSize(17);
	labels["CountMixed"].setPosition({ (WINDOW_WIDTH - WORLD_WIDTH) / 5.5, WINDOW_HEIGHT / 2.28 });

	font->loadFromFile("calibri.ttf");
	labels["CountSun"].setFont(*font);
	labels["CountSun"].setFillColor(sf::Color::White);
	labels["CountSun"].setCharacterSize(17);
	labels["CountSun"].setPosition({ (WINDOW_WIDTH - WORLD_WIDTH) / 5.5, WINDOW_HEIGHT / 2.1 });

	font->loadFromFile("calibri.ttf");
	labels["CountMineral"].setFont(*font);
	labels["CountMineral"].setFillColor(sf::Color::White);
	labels["CountMineral"].setCharacterSize(17);
	labels["CountMineral"].setPosition({ (WINDOW_WIDTH - WORLD_WIDTH) / 5.5, WINDOW_HEIGHT / 1.95 });

	font->loadFromFile("calibri.ttf");
	labels["CountMeat"].setFont(*font);
	labels["CountMeat"].setFillColor(sf::Color::White);
	labels["CountMeat"].setCharacterSize(17);
	labels["CountMeat"].setPosition({ (WINDOW_WIDTH - WORLD_WIDTH) / 5.5, WINDOW_HEIGHT / 1.83 });

	labels["CountBotDinamic"].setString(std::to_string( world->get_count_bot()));
	labels["CountMixed"].setString(std::to_string(world->get_count_mixed_bot()));
	labels["CountSun"].setString(std::to_string(world->get_count_sun_bot()));
	labels["CountMineral"].setString(std::to_string(world->get_count_minerals_bot()));
	labels["CountMeat"].setString(std::to_string(world->get_count_meat_bot()));
	labels["CountHealth"].setString(std::to_string(world->get_count_health()));
	labels["CountPoison"].setString(std::to_string(world->get_count_poison()));
	labels["CountWall"].setString(std::to_string(world->get_count_wall()));
	labels["CountMineral"].setString(std::to_string(world->get_time()));

	font->loadFromFile("calibri.ttf");
	labels["Hot Keys"].setFont(*font);
	labels["Hot Keys"].setFillColor(sf::Color::White);
	labels["Hot Keys"].setCharacterSize(17);
	labels["Hot Keys"].setPosition({ (WINDOW_WIDTH - WORLD_WIDTH) / 23,  WINDOW_HEIGHT / 1.50 });
	std::wstring ws = L"Hot Keys:\n\
Esc - exit\n\
N - start new simulation\n\
→ - increase speed\n\
← - decrease speed\n\
P - pause\n";
	labels["Hot Keys"].setString(ws);

}

GameModel* WorldModel::process(sf::Event& event, sf::RenderWindow& window) {

	if (event.type == sf::Event::KeyPressed) {

		Settings* s = world->get_ptr_settings();
		if (event.key.code == sf::Keyboard::Right) {

			s->time_iteration = s->time_iteration / 2;
			textField["SimulateSpeed"].setString(std::to_string(s->time_iteration));

		}

		if (event.key.code == sf::Keyboard::Left) {

			s->time_iteration = (s->time_iteration + 1) * 2;
			textField["SimulateSpeed"].setString(std::to_string(s->time_iteration));

		}

		if (event.key.code == sf::Keyboard::P) {

			s->time_iteration = INF;
			textField["SimulateSpeed"].setString("Pause");

		}

		if (event.key.code == sf::Keyboard::N) {

			World* w = new World(*s);
			return new WorldModel(w);

		}

	}
	if (event.type == sf::Event::MouseButtonPressed) {

		//cout << "Зашли в обработку кнопок\n";
		this->textField["FileName"].setFocus(false);
		this->textField["SimulateSpeed"].setFocus(false);
		this->textField["ResourceSpeed"].setFocus(false);

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

		if (this->textField["ResourceSpeed"].isMouseOver(window)) {
			this->textField["ResourceSpeed"].setFocus(true);
		}

		if (this->buttons["Apply1"].isMouseOver(window)) {
			fileName = this->textField["FileName"].getText();
		}

		if (this->buttons["Apply2"].isMouseOver(window)) {
			int t = std::stoi(this->textField["SimulateSpeed"].getText());
			world->set_time_iteration(t);

			t = std::stoi(this->textField["ResourceSpeed"].getText());
			world->set_time_resource(t);
		}
	}

	else if (textField["FileName"].getFocus()) {
		this->textField["FileName"].handleInput(event);
    }
	
	else if (textField["SimulateSpeed"].getFocus()) {
		this->textField["SimulateSpeed"].handleInput(event);
	}

	else if (textField["ResourceSpeed"].getFocus()) {
		this->textField["ResourceSpeed"].handleInput(event);
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

			World* w = new World(this->settings);
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
	buttons["Run"].setPosition({ WINDOW_WIDTH / 2.9, WINDOW_HEIGHT / 2.7 });
	buttons["Run"].setColor(sf::Color(255, 154, 154));
	//this->buttons["Run"] = { { WINDOW_WIDTH / 2.5, WINDOW_HEIGHT / 10 },  sf::Color::White, {WINDOW_WIDTH / 3.5, WINDOW_HEIGHT / 7}};
	this->buttons["Run"].initText("RUN", "calibri.ttf", 20, sf::Color(255, 255, 255));

	this->buttons["Load"];
	buttons["Load"].setSize({ WINDOW_WIDTH / 3, WINDOW_HEIGHT / 10 });
	buttons["Load"].setPosition({ WINDOW_WIDTH / 2.9, WINDOW_HEIGHT / 2 });
	buttons["Load"].setColor(sf::Color(255, 154, 154));
	this->buttons["Load"].initText("LOAD", "calibri.ttf", 20, sf::Color(255, 255, 255));
	
	/*
	this->buttons["Settings"];
	buttons["Settings"].setSize({ WINDOW_WIDTH / 3, WINDOW_HEIGHT / 10 });
	buttons["Settings"].setPosition({ WINDOW_WIDTH / 2.9, WINDOW_HEIGHT / 2.05 });
	buttons["Settings"].setColor(sf::Color(255, 154, 154));
	this->buttons["Settings"].initText("SETTINGS", "calibri.ttf", 20, sf::Color(255, 255, 255));
	*/
	
	this->buttons["Exit"];
	buttons["Exit"].setSize({ WINDOW_WIDTH / 3, WINDOW_HEIGHT / 10 });
	buttons["Exit"].setPosition({ WINDOW_WIDTH / 2.9, WINDOW_HEIGHT / 1.6 });
	buttons["Exit"].setColor(sf::Color(255, 154, 154));
	this->buttons["Exit"].initText("EXIT", "calibri.ttf", 20, sf::Color(255, 255, 255));
	
}

GameModel* WorldModel::run() {

	int count = world->get_count_bot();
	labels["CountBotDinamic"].setString(std::to_string(count));

	count = world->get_count_mixed_bot();
	labels["CountMixed"].setString(std::to_string(count));

	count = world->get_count_sun_bot();
	labels["CountSun"].setString(std::to_string(count));

	count = world->get_count_minerals_bot();
	labels["CountMineral"].setString(std::to_string(count));

	count = world->get_count_meat_bot();
	labels["CountMeat"].setString(std::to_string(count));

	count = world->get_count_health();
	labels["CountHealth"].setString(std::to_string(count));

	count = world->get_count_poison();
	labels["CountPoison"].setString(std::to_string(count));

	count = world->get_count_wall();
	labels["CountWall"].setString(std::to_string(count));

	labels["TimeDinamic"].setString(std::to_string(world->get_time()));

	try {

		this->world->iteration_world();
		return this;

	}
	catch (...) {

		World* w = new World(this->world->get_settings());
		GameModel* a = new WorldModel(w);
		return a;

	}
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

	for (auto el : pictures) {

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

void WorldModel::create_picture(std::string name, std::string file_name) {
	Form form(file_name);
	sf::Image im = form.get_sprite();
	sf::Texture* t = new sf::Texture;
	t->loadFromImage(im);
	pictures[name].setTexture(*t);
	pictures[name].setScale(0.25, 0.25);
}