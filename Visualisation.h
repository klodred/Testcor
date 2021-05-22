#pragma once
#include <SFML/Graphics.hpp>
#include "World.h"
#include <map>

static const int WINDOW_WIDTH = 1200, WINDOW_HEIGHT = 800;
static const int WORLD_WIDTH = 800, WORLD_HEIGHT = 800;

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
		shape.setFillColor(bgColor);
		shape.setSize(size);
		shape.setPosition(pos);
	}

	void setSize(sf::Vector2f _size) { size = _size; shape.setSize(size); };

	void setPosition(sf::Vector2f _pos) { pos = _pos; shape.setPosition(pos); };

	void setColor(sf::Color _color) { color = _color; shape.setFillColor(color); };

	void setOutlineThickness(float _size) { shape.setOutlineThickness(_size); };

	void setOutlineColor(sf::Color _color) { shape.setOutlineColor(_color); };

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

class TextEdit : public sf::Transformable, public sf::Drawable {
private:
	int maxChars;
	sf::Vector2f size;
	sf::Vector2f pos;
	sf::Font *font;
	std::string text;
	sf::Text* _text;
	sf::RectangleShape shape;
	sf::Color color;
	bool hasFocus = false;

public:
	TextEdit() { maxChars = 30; _text = new sf::Text; };

	void setString(std::string name) {
		text = name;
	}

	TextEdit(sf::Vector2f _size, sf::Color bgColor, sf::Vector2f _pos, int max) : size(_size), pos(_pos), maxChars(max) {
		shape.setFillColor(bgColor);
		shape.setSize(size);
		shape.setPosition(pos);
		shape.setOutlineThickness(5);
		shape.setOutlineColor(sf::Color(127, 127, 127));
		hasFocus = false;
	}

	void setOutlineThickness(float _size) { shape.setOutlineThickness(_size); };

	void setOutlineColor(sf::Color _color) { shape.setOutlineColor(_color); };

	void initText(string name, int sizeChars, sf::Color _color) {
		font = new sf::Font;
		font->loadFromFile(name);
		_text->setFont(*font);
		_text->setCharacterSize(sizeChars);
		_text->setPosition(pos.x, pos.y + 3);
		_text->setFillColor(_color);
	}

	const std::string getText() const {
		return text;
	}

	void setPosition(float x, float y) {
		sf::Transformable::setPosition(x, y);
		shape.setPosition(x, y);
	}

	bool getFocus() { return hasFocus; };

	void draw(sf::RenderTarget& target, sf::RenderStates states) const {

		states.transform *= getTransform();
		target.draw(shape);
		_text->setString(text);
		target.draw(*_text);
	}

	bool contains(sf::Vector2f point) const {
		return shape.getGlobalBounds().contains(point);
	}

	void setFocus(bool focus) {
		hasFocus = focus;

		if (focus) {
			shape.setOutlineColor(sf::Color::Blue);
		}

		else {
			shape.setOutlineColor(sf::Color(127, 127, 127)); 
		}
	}

	bool isMouseOver(sf::RenderWindow& window) {
		auto pos = sf::Mouse::getPosition(window);
		return this->contains(sf::Vector2f(pos));
	}

	
	void handleInput(sf::Event e) {
		if (!hasFocus || e.type != sf::Event::TextEntered) {
			return;
		}
			
		if (e.text.unicode == 8) {   // Delete key
			text = text.substr(0, text.size() - 1);
		}

		else if (text.size() < maxChars) {
			text += e.text.unicode;
		}
	}
	
	void setSize(sf::Vector2f _size) { size = _size; shape.setSize(size); };

	void setPosition(sf::Vector2f _pos) { pos = _pos; shape.setPosition(pos); };

	void setFillColor(sf::Color _color) { color = _color; };
	
	
};

class GameModel : public sf::Drawable, public sf::Transformable {

public:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const final;
	virtual void draw_main(sf::RenderTarget& target, sf::RenderStates states) const { };
	virtual void draw_ui(sf::RenderTarget& target, sf::RenderStates states) const { };

	
	
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
	std::string fileName;
	std::map<std::string, Button> buttons;
	std::map<std::string, sf::Text> labels;
	std::map<std::string, TextEdit> textField;
	std::map<std::string, sf::RectangleShape> shapes;
	std::map<std::string, sf::Sprite> pictures;

public:
	WorldModel(World* w);

	//virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void draw_main(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void draw_ui(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual GameModel* process(sf::Event& event, sf::RenderWindow& window);

	void create_picture(std::string name, std::string file_name);

	virtual void run();
};

class MenuModel : public GameModel {
	Settings settings;
	std::map<std::string, Button> buttons;

public:
	MenuModel(Settings _set);

	//virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void draw_main(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void draw_ui(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual GameModel* process(sf::Event& event, sf::RenderWindow& window);
};

class Controller {
private:
	GameModel* game;
	Settings settings;

public:
	Controller(GameModel* _game, Settings _set) : game(_game), settings(_set) {};

	void run();
};






