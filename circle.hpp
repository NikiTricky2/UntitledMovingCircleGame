#include <SFML/Graphics.hpp>

class Circle {
public:
	float radius;
	sf::Color color;
	sf::Vector2f position;
	sf::CircleShape circle;

	sf::Vector2f getPos() {
		return circle.getPosition() +sf::Vector2f(radius / 2.f, radius / 2.f); // For some reasong getPosition() returns the top right corner now
	}

	//Circle(float radius, sf::Vector2f position, sf::Color color = sf::Color::White) {
	//	circle.setRadius(radius);
	//	circle.setPosition(position);
	//	circle.setFillColor(color);
	//}
};

class Player : public Circle {
public:
	sf::Vector2f velocity = sf::Vector2f(0.f, 0.f);

	Player(float radius, sf::Vector2f position, sf::Color color = sf::Color::White) {
		circle.setRadius(radius);
		circle.setPosition(position);
		circle.setFillColor(color);
	}

	void update(float drag, int w, int h) {
		velocity.x *= drag;
		velocity.y *= drag;

		circle.move(velocity);

		if (circle.getPosition().x > w || circle.getPosition().x < 0) {
			velocity.x = -velocity.x;
		}
		if (circle.getPosition().y > h || circle.getPosition().y < 0) {
			velocity.y = -velocity.y;
		}
	}

	void center(int w, int h) {
		circle.setPosition(sf::Vector2f(w / 2.f, h / 2.f));
	}
};