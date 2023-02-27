#include <string>

#include <SFML/Graphics.hpp>

class Button {
public:
	sf::RectangleShape rect;
	sf::Text playtext;

	sf::Vector2f position;
	sf::Vector2f size;

	bool pressing = false;

	Button(sf::Vector2f pos, sf::Vector2f insize) {
		position = pos;
		size = insize;

		rect.setFillColor(sf::Color::Black);
		rect.setOutlineColor(sf::Color::White);
		rect.setOutlineThickness(5);
		rect.setPosition(pos);
		rect.setSize(size - sf::Vector2f(5.f, 5.f));
	}

	void collision(sf::Vector2f mousepos) {
		pressing = (mousepos.x >= position.x && mousepos.x <= position.x + size.x) && (mousepos.y >= position.y && mousepos.y <= position.y + size.y);
	}
};