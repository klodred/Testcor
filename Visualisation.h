#pragma once
#include <SFML/Graphics.hpp>
#include "World.h"
#include <map>

static const int WINDOW_WIDTH = 600, WINDOW_HEIGHT = 600;

class Button : public sf::Drawable, sf::Transformable {
private:
	sf::RectangleShape shape;
	sf::Vector2f size;
	sf::Vector2f pos;
	sf::Color color;
	sf::Text* text;
	sf::Font* font;

public:
	Button() {};

	Button(sf::Vector2f _size, sf::Color bgColor, sf::Vector2f _pos) : size(_size), pos(_pos) {
		/*
		text = new sf::Text;
		font = new sf::Font;
		font->loadFromFile(nameFont);
		text->setString(t);
		text->setFont(*font);
		text->setFillColor(textColor);
		text->setCharacterSize(charSize);
		*/
		shape.setFillColor(bgColor);
		//text->setFillColor(textColor);
		shape.setSize(size);
		shape.setPosition(pos);
	}

	void setSize(sf::Vector2f _size) { size = _size; shape.setSize(size); };

	void setPosition(sf::Vector2f _pos) { pos = _pos; shape.setPosition(pos); };

	void setColor(sf::Color _color) { color = _color; shape.setFillColor(color); };

	void initText(std::string t, std::string nameFont, int charSize, sf::Color color) {
		text = new sf::Text;
		font = new sf::Font;
		font->loadFromFile(nameFont);
		text->setString(t);
		text->setFont(*font);
		text->setFillColor(color);
		text->setCharacterSize(charSize);

		text->setPosition(pos.x + size.x / 2.6 - t.size(), pos.y + size.y / 3);
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const {

		states.transform *= getTransform();
		target.draw(shape);
		target.draw(*text);
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

/*
class MenuModel : public GameModel {
public:
	Wor
};
*/
class WorldModel : public GameModel {
private:
	World* world;

public:
	WorldModel(World* w) : world(w) {};

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual GameModel* process(sf::Event& event, sf::RenderWindow& window) { return this; };

	virtual void run();
};

class MenuModel : public GameModel {
	Settings settings;
	std::map<std::string, Button> buttons;

public:
	MenuModel(Settings _set);

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






