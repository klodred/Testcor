#pragma once
#include <SFML/Graphics.hpp>
#include "World.h"
#include <map>

static const int WINDOW_WIDTH = 600, WINDOW_HEIGHT = 600;

class Button : public sf::Drawable, sf::Transformable {
private:
	sf::RectangleShape shape;
	sf::Text text;

public:
	Button() {};
	Button(std::string t, sf::Vector2f size, int charSize, sf::Color bgColor, sf::Color textColor) {
		text.setString(t);
		text.setFillColor(textColor);
		text.setCharacterSize(charSize);

		shape.setFillColor(bgColor);
		shape.setSize(size);
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		states.transform *= getTransform();
		target.draw(shape);
		target.draw(text);
	}

	bool isMouseOver(sf::RenderWindow& window) {
		float mouseX = sf::Mouse::getPosition(window).x;
		float mouseY = sf::Mouse::getPosition(window).y;

		float buttonX = shape.getPosition().x;
		float buttonY = shape.getPosition().y;

		float buttonWidth = shape.getPosition().x + shape.getLocalBounds().width;
		float buttonHeight = shape.getPosition().y + shape.getLocalBounds().height;

		if (mouseX < buttonWidth && mouseX > buttonX && mouseY < buttonHeight && mouseY > buttonY)
			return true;

		else
			return false;
	}
};
class GameModel : public sf::Drawable, public sf::Transformable {

public:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

	virtual GameModel* process(sf::Event& event, sf::RenderWindow& window) = 0;

	virtual void run() {};

};

class WorldModel : public GameModel {
private:
	World* world;

public:
	WorldModel(World* w) : world(w) {};

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual GameModel* process(sf::Event& event, sf::RenderWindow& window) { return this; };

	virtual void run();

};

class SettingsModel : public GameModel {
	Settings settings;
	std::map<std::string, Button> buttons;

public:
	SettingsModel(Settings _set);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual GameModel* process(sf::Event& event, sf::RenderWindow& window);
};

class Controller {
private:
	GameModel* game;

public:
	Controller(GameModel* _game) : game(_game) {};

	void run();
};






